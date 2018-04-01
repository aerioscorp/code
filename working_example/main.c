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

#define DHTPIN GPIO_PIN_ID_P1_4

#define ACTIVATE      		0x50
#define MAX_RESEND 			5
#define RF24_CHANNEL	   	84
#define RF24_DATARATE 	   	RF_RF_SETUP_RF_DR_250_KBPS
#define RF24_PA_LEVEL 	   	RF_RF_SETUP_RF_PWR_0_DBM

// LSB first
#define LUMINOS_TYPE 0x01;
uint8_t base_addr[5] = {0xFF,0xFC,0xE1,0xA8,0xA8};
#define APOLLON_SIZE  10
uint32_t uvValue;
uint32_t brightValue;

#define GATEWAY_ADDRESS ((uint8_t)0x00)
#define BROADCAST_ADDRESS ((uint8_t)0xFF)
#define AUTO ((uint8_t)0xFF)
#define CE_PULSE_LENGTH	10

#define pinMode gpio_pin_configure
#define OUTPUT			GPIO_PIN_CONFIG_OPTION_DIR_OUTPUT
#define INPUT			GPIO_PIN_CONFIG_OPTION_DIR_INPUT

#define reboot() watchdog_cause_software_reset()
#define RF24available() rf_irq_rx_dr_active()

#define ISR(p1) void isr##p1() __interrupt(p1)

// millis() implementation
#define TLSTART 256-16000000/1000/12/6
unsigned long ml = 0;
uint8_t mcs = 0;


message_u outMsg;
message_u inMsg;

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

void BuildMessage(uint8_t command) {
    outMsg.message.command = command;
    outMsg.message.cardType = LUMINOS_TYPE;
}

void BuildApollonMessage(uint8_t command, uint32_t uvValue, uint32_t brightValue) {
    outMsg.message.command = command;
    outMsg.message.cardType = LUMINOS_TYPE;
    outMsg.message.messageType.apollonMessage.apollonMessageStruct.sensor1 = UV;
    outMsg.message.messageType.apollonMessage.apollonMessageStruct.uvValue= uvValue;
    outMsg.message.messageType.apollonMessage.apollonMessageStruct.sensor2 = BRIGHTNESS;
    outMsg.message.messageType.apollonMessage.apollonMessageStruct.brigthValue = brightValue;
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
    base_addr[0] = nextnode;
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
    if ( RF24available() ) {
        RF24readMessage(inMsg.array);
        result = inMsg.message.command;
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

bool SendMessage(uint8_t address) {
    return RF24write(address, outMsg.array, APOLLON_SIZE, (address == BROADCAST_ADDRESS) );
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

}

void main(){
    // init
    setup();

    // loop
  // while(1){
        millisBegin();

        BuildMessage(CONFIGURATION);
        SendMessage(BROADCAST_ADDRESS);
        process_type(CONFIGURATION);

        BuildMessage(ASK_SEND_DATA);
        SendMessage(BROADCAST_ADDRESS);
        process_type(ASK_SEND_DATA);

        watchdog_calc_timeout_from_sec(3);

        uvValue = 3;
        brightValue =  521;
        BuildApollonMessage(SEND_DATA,uvValue,brightValue);
        SendMessage(BROADCAST_ADDRESS);
        process_type(SEND_DATA);
        process_time(1000);
   //}
}

