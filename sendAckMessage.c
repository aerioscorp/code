#include "reg24le1.h"
#include "stdlib.h"
#include "string.h"
#include "MyMessage.h"
#include "rf.h"
#include "gpio.h"
#include "timer0.h"
#include "interrupt.h"
#include "watchdog.h"
#include "memory.h"
#include "adc.h"


#define CHILD_ID_APOLLON 0
#define CHILD_ID_APOLLON_DESCRIPTION_CONNECT "apollonConnect"
#define CHILD_ID_APOLLON_DESCRIPTION_DISCONNECT "apollonDisconnect"
#define CHILD_ID_ATHENA 1
#define CHILD_ID_ATHENA_DESCRIPTION "athena"
#define NODE_ID AUTO

#define DHTPIN GPIO_PIN_ID_P1_4

#define ACTIVATE      		0x50
#define MAX_RESEND 			5
#define RF24_CHANNEL	   	78
#define RF24_DATARATE 	   	RF_RF_SETUP_RF_DR_250_KBPS
#define RF24_PA_LEVEL 	   	RF_RF_SETUP_RF_PWR_0_DBM

// LSB first
uint8_t base_addr[5] = {0xFF,0xFC,0xE1,0xA8,0xA8};

#define GATEWAY_ADDRESS ((uint8_t)0x00)
#define BROADCAST_ADDRESS ((uint8_t)0xFF)
#define AUTO ((uint8_t)0xFF)
#define CE_PULSE_LENGTH	10

#define TEMP_MEM_BUFFER_SIZE MEMORY_FLASH_NV_EXT_END_PAGE_SIZE
#define NODE_CONFIGURATION_ADDRESS MEMORY_FLASH_NV_EXT_END_START_ADDRESS

#define digitalRead gpio_pin_val_read
#define digitalWrite gpio_pin_val_write
#define pinMode gpio_pin_configure
#define OUTPUT			GPIO_PIN_CONFIG_OPTION_DIR_OUTPUT
#define INPUT			GPIO_PIN_CONFIG_OPTION_DIR_INPUT
#define LOW				0
#define HIGH			1

#define reboot() watchdog_cause_software_reset()
#define RF24available() rf_irq_rx_dr_active()

#define ISR(p1) void isr##p1() __interrupt(p1)

// millis() implementation
#define TLSTART 256-16000000/1000/12/6
unsigned long ml = 0;
uint8_t mcs = 0;

struct NodeConfig
{
	uint8_t nodeId; // Current node id
	uint8_t parentNodeId; // Where this node sends its messages
	uint8_t distance; // This nodes distance to sensor net gateway (number of hops)
};

MyMessage outMsg;
MyMessage inMsg;
struct NodeConfig nc;
bool configuredParentFound = false;
uint8_t configuredParentID = AUTO;


#define millis() ml
#define micros() ml*1000

ISR(INTERRUPT_VECTOR_T0){
	TL0 = TLSTART;
	if (mcs>=6) {
		ml++;
		mcs=0;
	}
	mcs++;
}

inline void millisBegin() {
	interrupt_control_global_enable();
	interrupt_control_t0_enable();
	timer0_configure(TIMER0_CONFIG_OPTION_MODE_3_TWO_8_BIT_CTRS_TMRS,TLSTART);
	timer0_run();
}

void BuildMessage(uint8_t destination, uint8_t sensor, uint8_t command, uint8_t type, uint8_t payload_type, uint8_t len, bool enableAck) {
	outMsg.sender = nc.nodeId;
	outMsg.last = nc.nodeId;
	outMsg.destination = destination;
	outMsg.sensor = sensor;
	outMsg.type = type;
	mSetPayloadType(outMsg, payload_type);
	mSetLength(outMsg, len);
	mSetCommand(outMsg,command);
	mSetRequestAck(outMsg,enableAck);
	mSetAck(outMsg,false);
	mSetVersion(outMsg, PROTOCOL_VERSION);
}

inline bool write_buf(uint8_t* buf, uint8_t len, bool broadcast ) {
	// write payload to FIFO, broadcasts do not require ACK
	uint8_t FIFO_STATUS;
	uint8_t status = rf_spi_execute_command(broadcast ? RF_W_TX_PAYLOAD_NOACK : RF_W_TX_PAYLOAD, buf, len, false);
	// CE pulse to start transmission
	rf_set_ce();
	// minimum CE pulse width 10us, see nRF24L01 specs
	delay_us(CE_PULSE_LENGTH);
	// start transmitting
	rf_clear_ce();
	// wait until sent or max retries
	do {
		// get status byte
		FIFO_STATUS = rf_get_status();
	} while( !(FIFO_STATUS & RF_STATUS_TX_DS) && !(FIFO_STATUS & RF_STATUS_MAX_RT) );

	return (FIFO_STATUS & RF_STATUS_TX_DS);
}

void flush_fifo_irq() {
	rf_flush_tx();
	rf_flush_rx();
	rf_irq_clear_all();
}

bool RF24write(uint8_t nextnode, uint8_t* buf, uint8_t len, bool broadcast) {

	uint8_t config;
	bool result;
	//stop listening
	rf_clear_ce();
	// switch to TX mode (done automatically, if ACK flag set; for broadcasts, switch necessary)
	config = RF_CONFIG_PWR_UP | RF_CONFIG_CRCO | RF_CONFIG_EN_CRC;
	rf_write_register(RF_CONFIG,&config,1);
	// flush FIFO and interrupts
	flush_fifo_irq();
	// set pipe0 TX address
	base_addr[0] = nextnode;
	rf_set_tx_addr(base_addr, 5);
	// set RX address for ACK
	base_addr[0] = nextnode;
	rf_set_rx_addr(base_addr, 5, 0);

	// write payload
	result = write_buf(buf, len, broadcast);
	// start listening
	config = RF_CONFIG_PWR_UP | RF_CONFIG_CRCO | RF_CONFIG_EN_CRC | RF_CONFIG_PRIM_RX;
	rf_write_register(RF_CONFIG,&config,1);
	// set RX address
	base_addr[0] = nc.nodeId;
	rf_set_rx_addr(base_addr, 5, 0);

	// flush FIFO and interrupts
	flush_fifo_irq();
	// go!
	rf_set_ce();
	// wait for radio to come up
	delay_us(130);

	return result;
}



inline uint8_t getDynamicPayloadSize(void) {
	uint8_t result;
	rf_read_rx_payload_width(&result);

	// payloads > 32 are not allowed
	if(result > 32) {
		// flush RX FIFO
		rf_flush_rx();
		result = 0;
	}
	return result;
}

uint8_t RF24readMessage(uint8_t* buf) {
	// read payload length
	uint8_t payload_length = getDynamicPayloadSize();
	// read payload
	rf_read_rx_payload(buf,payload_length);
	// reset interrupts
	rf_irq_clear_all();
	return payload_length;
}


uint8_t process_rx() {
	uint8_t result = 0xFF;
	uint8_t temp_buf[TEMP_MEM_BUFFER_SIZE];
	if ( RF24available() ) {
		RF24readMessage(inMsg.array);
		if (inMsg.destination == nc.nodeId) {
			result = inMsg.type;
			// internal command: find parent
			if (mGetCommand(inMsg) == C_INTERNAL) {
				if (inMsg.type == I_FIND_PARENT_RESPONSE) {

					// static parent found?
					if (configuredParentID == inMsg.sender) {
						configuredParentFound = true;
					}
					if ( ((inMsg.bValue < nc.distance - 1) && ( !configuredParentFound) ) || (configuredParentID == inMsg.sender)) {
						// got new routing info, update settings
						nc.distance = inMsg.bValue + 1;
						nc.parentNodeId = inMsg.sender;
					}
				}
				if (inMsg.type == I_ID_RESPONSE) {
					nc.nodeId = atoi(inMsg.data);
					// save settings to flash
					memory_flash_write_bytes_smart(NODE_CONFIGURATION_ADDRESS,3,(uint8_t*)nc,temp_buf);
				}
				if (inMsg.type == I_REBOOT) {
					reboot();
				}
				if (inMsg.type == I_CHILDREN) {
					nc.nodeId = AUTO;
					// save settings to flash
					memory_flash_write_bytes_smart(NODE_CONFIGURATION_ADDRESS,3,(uint8_t*)nc,temp_buf);
					reboot();
				}
			}

		}
	}
	return result;
}

// process incoming messages during "wait_time" ms
void process_time(uint16_t wait_time) {
	unsigned long entry = millis();
	while ( (ml < entry+wait_time) ) {
		process_rx();
	}
}
// process until specific response received, timeout after 8s
bool process_type(uint8_t response) {
	uint8_t res_type = 0xFF;
	unsigned long entry = millis();
	do {
		watchdog_calc_timeout_from_sec(8);
		res_type = process_rx();
	} while ( (ml < entry+8000) && (res_type!=response) );

	return (res_type==response);
}

bool SendMessage() {
	return RF24write(nc.parentNodeId, outMsg.array, HEADER_SIZE + mGetLength(outMsg), (outMsg.destination == BROADCAST_ADDRESS) );
}


inline bool readDHT22() {
	uint8_t inByte = 0, inBit = 0, CRC = 0;
	uint8_t DHTdata[5];

	digitalWrite(DHTPIN,LOW);
	pinMode(DHTPIN,OUTPUT);
	// DHT22 specific timings
	delay_us(800);
	pinMode(DHTPIN,INPUT);
	digitalWrite(DHTPIN,HIGH);
	delay_us(51);
	if (digitalRead(DHTPIN)) return false;
	delay_us(81);
	if (!digitalRead(DHTPIN)) return false;

	while (digitalRead(DHTPIN));

	for (inByte=0; inByte<5; inByte++) {
		DHTdata[inByte]=0;
		for(inBit=0; inBit<8; inBit++) {
			while (!digitalRead(DHTPIN));
			delay_us(30);
			if (digitalRead(DHTPIN)) DHTdata[inByte] |= 1 << (7 - inBit);
			while (digitalRead(DHTPIN));
        }

    }

	CRC = DHTdata[0]+DHTdata[1]+DHTdata[2]+DHTdata[3];
	if(CRC==DHTdata[4])
	{
		// crc correct, do the math
		humidity = DHTdata[0] << 8 | DHTdata[1];
		temperature = DHTdata[2] << 8 | DHTdata[3];
	}

	return true;

}

inline void RF24init() {
	uint8_t config;
	rf_spi_configure_enable();
	config = RF_EN_AA_ENAA_P0;
	rf_write_register(RF_EN_AA, &config, 1);
	config = RF_EN_RXADDR_ERX_P0;
	rf_write_register(RF_EN_RXADDR, &config, 1);
	config = RF_SETUP_AW_5BYTES;
	rf_write_register(RF_SETUP_AW, &config, 1);
	config = RF_SETUP_RETR_ARD_1500 | RF_SETUP_RETR_ARC_5;
	rf_write_register(RF_SETUP_RETR, &config, 1);
	config = RF24_CHANNEL;
	rf_write_register(RF_RF_CH, &config, 1);
	config = RF24_PA_LEVEL | RF24_DATARATE;
	rf_write_register(RF_RF_SETUP, &config, 1);
	// unlock dynamic payload features
	config = 0x73;
	rf_spi_execute_command(ACTIVATE,&config,1,false);
	//rf_set_rx_addr(base_addr, 5, 0);	// no need
	//rf_set_tx_addr(base_addr, 5);		// no need
	config = RF_DYNPD_DPL_P0;
	rf_write_register(RF_DYNPD, &config, 1);
	config = RF_FEATURE_EN_DPL | RF_FEATURE_EN_ACK_PAY;
	rf_write_register(RF_FEATURE, &config, 1);
	rf_power_up_param(false, RF_CONFIG_PWR_UP | RF_CONFIG_CRCO | RF_CONFIG_EN_CRC);
	// wait for RF to power-up
	delay_us(130);
}

inline void setup()
{
	watchdog_setup();
	watchdog_calc_timeout_from_sec(8);
	// adc settings
	adc_configure(	ADC_CONFIG_OPTION_REF_SELECT_INT_1_2V |
					ADC_CONFIG_OPTION_SINGLE_STEP_POWER_DOWN_DELAY_INF |
					ADC_CONFIG_OPTION_SAMPLING_SINGLE_STEP |
					ADC_CONFIG_OPTION_RESOLUTION_12_BITS |
					ADC_CONFIG_OPTION_RESULT_JUSTIFICATION_RIGHT
	);
	// debug
	pinMode(GPIO_PIN_ID_P0_0, OUTPUT);

	RF24init();

	millisBegin();

	memory_flash_read_bytes(NODE_CONFIGURATION_ADDRESS,3,(uint8_t*)nc);
	//if (!nc.nodeId) nc.nodeId = 254;
	configuredParentID = nc.parentNodeId;
	// reset parent node settings for discovery
	nc.distance = 0xFF;

	// prepare for I_FIND_PARENTS
	outMsg.bValue = 0;
	BuildMessage(BROADCAST_ADDRESS,0xFF,C_INTERNAL,I_FIND_PARENT_REQUEST, P_BYTE, 1,false);
	SendMessage();
	process_time(2000);
	if ( nc.parentNodeId==0xFF ) {
		// no parents found
		reboot();
	}
	// ID assigned?
	if (nc.nodeId==AUTO) {
		BuildMessage(GATEWAY_ADDRESS,0xFF,C_INTERNAL,I_ID_REQUEST, P_BYTE, 1,false);
		SendMessage();
		if (!process_type(I_ID_RESPONSE) ) {
			reboot();
		}
	}

	// Send a configuration exchange request to controller
	outMsg.bValue = nc.parentNodeId;
	BuildMessage(GATEWAY_ADDRESS,0xFF,C_INTERNAL,I_CONFIG,P_BYTE,1,false);
	SendMessage();
	process_time(1000);

}

void main(){
	// init
	setup();
	// loop
	while(1) {

		watchdog_calc_timeout_from_sec(3);

//		readDHT22();

        /** pour Apollon : */

        //UV
        outMsg.bValue = (int_8) getUV();
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_APOLLON,C_SET,V_UV, P_BYTE,4,false);
        SendMessage();

        //Bright
        outMsg.ulValue =  (int_32) getBrightness();
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_APOLLON,C_SET,V_LIGHT_LEVEL,P_ULONG32,4+1,false);
        SendMessage();

        /** Pour Athena */

		//Temperature
        outMsg.bValue = (int_8) getTemperature();
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_ATHENA,C_SET,V_TEMP, P_BYTE,4,false);
        SendMessage();


        //Humidity
        outMsg.bValue = (int_8) getHumidity();
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_ATHENA,C_SET,V_HUM,P_BYTE,4+1,false);
        SendMessage();

        //Pressure
        outMsg.iValue = (uint_16) getPressure();
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_ATHENA,C_SET,V_PRESSURE,P_UINT16,4+1,false);
        SendMessage();

		// process / wait
		process_time(2000);
	}

}

