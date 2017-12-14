//
// Created by sami on 07/12/17.
//


#include "reg24le1.h"
#include "stdlib.h"
#include "string.h"
#include "apollonMessage.h"
#include "rf.h"
#include "gpio.h"
#include "timer0.h"
#include "interrupt.h"
#include "memory.h"
#include "adc.h"
#include "apollonSwitcher.h"


#define RF24_CHANNEL	   	76
#define RF24_DATARATE 	   	RF_RF_SETUP_RF_DR_250_KBPS
#define RF24_PA_LEVEL 	   	RF_RF_SETUP_RF_PWR_0_DBM
#define ADDRESS_LENGTH 5
#define NUCLEUS_ADDRESS ((uint8_t)0xC0000)
#define THIS_APOLLON_ADDRESS ((uint8_t)0x01) // This address
#define NUMBER_OF_BYTE_SENT 7
#define CE_PULSE_LENGTH	10

MyMessage outMsg;


void BuildMessage() {
    outMsg.sender = THIS_APOLLON_ADDRESS;
    outMsg.MessageType = 0;             // Zero referes to an Apollon module
    outMsg.uvValue = getUV();
    outMsg.brigthValue = getBrigthness();
}


inline bool write_buf(uint8_t* buf) {
    // write payload to FIFO
    uint8_t FIFO_STATUS;
    uint8_t status = rf_spi_execute_command(RF_W_TX_PAYLOAD_NOACK, buf, NUMBER_OF_BYTE_SENT, false);
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

bool RF24write(uint8_t* buf) {
    uint8_t config;
    bool result;
    //stop listening
    rf_clear_ce();
    // switch to TX mode
    config = RF_CONFIG_PWR_UP | RF_CONFIG_CRCO | RF_CONFIG_EN_CRC;
    rf_write_register(RF_CONFIG, &config,1);
    // flush FIFO and interrupts
    flush_fifo_irq();
    // set pipe0 TX address
    rf_set_tx_addr(NUCLEUS_ADDRESS, ADDRESS_LENGTH);
    // write payload
    result = write_buf(buf);
    // flush FIFO and interrupts
    flush_fifo_irq();
    // go!
    rf_set_ce();
    // wait for radio to come up
    delay_us(130);
    return result;
}


bool SendMessage() {
    return RF24write(outMsg.array);
}

inline void setup() {
    uint8_t config;
    rf_spi_configure_enable();

    config = RF_SETUP_AW_5BYTES;
    rf_write_register(RF_SETUP_AW, &config, 1);

    config = RF_EN_AA_ENAA_NONE;
    rf_write_register(RF_EN_AA, &config, 1);


    config = RF_SETUP_RETR_ARC_0;
    rf_write_register(RF_SETUP_RETR, &config, 1);

    config = RF24_CHANNEL;
    rf_write_register(RF_RF_CH, &config, 1);

    config = RF24_PA_LEVEL | RF24_DATARATE;
    rf_write_register(RF_RF_SETUP, &config, 1);


    rf_power_up_param(false, RF_CONFIG_PWR_UP | RF_CONFIG_CRCO | RF_CONFIG_EN_CRC);
    // wait for RF to power-up
    delay_us(130);
}




//TODO
void main(){
    setup();
    while(1) {
        BuildMessage();
        SendMessage();

        // process / wait
        process_time(2000);
    }
}

