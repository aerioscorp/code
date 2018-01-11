//
// Created by sami on 14/12/17.
//

#include "reg24le1.h"
#include "stdlib.h"
#include "string.h"
#include "rf.h"
#include "gpio.h"
#include "timer0.h"
#include "interrupt.h"
#include "watchdog.h"
#include "memory.h"
#include "adc.h"
#include "apollonSwitcher.h"

#define RF24_CHANNEL	   	78
#define RF24_DATARATE 	   	RF_RF_SETUP_RF_DR_250_KBPS
#define RF24_PA_LEVEL 	   	RF_RF_SETUP_RF_PWR_0_DBM
#define ADDRESS_LENGTH      5
#define CE_PULSE_LENGTH 	10

message_u inMsg;
//TODO Pour les tests, valeurs factices de reception.
uint8_t uvValue;     //! TEST
uint32_t brigthValue;  //! TEST

void flush_fifo_irq() {
    rf_flush_tx();
    rf_flush_rx();
    rf_irq_clear_all();
}

/*inline uint8_t getDynamicPayloadSize(void) {
    uint8_t result;
    rf_read_rx_payload_width(&result);

    // payloads > 32 are not allowed
    if(result > 32) {
        // flush RX FIFO
        rf_flush_rx();
        result = 0;
    }
    return result;
}*/

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
    // present sensors
    present(CHILD_ID_MILLIS, S_CUSTOM, CHILD_ID_MILLIS_DESCRIPTION);
    present(CHILD_ID_TEMP, S_TEMP, CHILD_ID_TEMP_DESCRIPTION);
    present(CHILD_ID_HUMIDITY, S_HUM, CHILD_ID_HUMIDITY_DESCRIPTION);
    present(CHILD_ID_VOLTAGE, S_POWER, CHILD_ID_VOLTAGE_DESCRIPTION);
    // send sketch info
    sendSketchInfo(SketchName, SketchVersion);
    // loop
    while(1) {

        watchdog_calc_timeout_from_sec(3);

//		readDHT22();

        outMsg.ulValue = millis();
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_MILLIS,C_SET,V_VAR1, P_ULONG32,4,false);
        SendMessage();

        outMsg.iValue = (int16_t)(1200.0 / 4096.0 * adc_start_single_conversion_get_value(ADC_CHANNEL_1_THIRD_VDD) * 3);
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_VOLTAGE,C_SET,V_VOLTAGE,P_INT16,2,false);
        SendMessage();

        outMsg.fPrecision = 1;
        outMsg.fValue = temperature/10.0;
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_TEMP,C_SET,V_TEMP,P_FLOAT32,4+1,false);
        SendMessage();

        outMsg.fValue = humidity/10.0;
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_HUMIDITY,C_SET,V_HUM,P_FLOAT32,4+1,false);
        SendMessage();

        // process / wait
        process_time(2000);

        //TODO Pour les tests
        //! TEST Print brigthValue et uvValue
    }

}

