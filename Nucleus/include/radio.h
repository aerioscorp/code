/*
 * radio.h
 *
 *  Created on: 23 janv. 2018
 *      Author: Corentin
 */

#ifndef INCLUDE_RADIO_H_
#define INCLUDE_RADIO_H_

#include <RF24/RF24.h>
#include "sensor.h"

/*
 **** NRF24L01 pins connection: ****
 * VCC		3.3v
 * SCK      GPIO14
 * MOSI     GPIO13
 * MISO		GPIO12
 * CE		GPIO4 (changeable)
 * CSN		GPIO15 (changeable)
 * IRQ		GPIO5
 * GND      GND
 */
extern RF24 radio;
#define INT_PIN  			5

/*
 * Define pour la communication RF24
 */
#define RF24_BASE_RADIO_ID 	((uint64_t)0xA8A8E1FC00LL)
#define CAPTEUR_PIPE 		((uint8_t)0x01)
#define BROADCAST_PIPE 		((uint8_t)0x02)
#define BROADCAST_ADDRESS	((uint8_t)0xFF)

/*
 * Structures pour les trames de communication
 */
typedef enum : uint8_t {
		SETUP,
		ASK_SEND_DATA,
		SEND_DATA,
		DATA_OK,
		MAX_MSG
} MsgType_e;

typedef struct {
	MsgType_e msgType;
	CardType_e cardType;
	DataSensor dataSensor;
} __attribute__((packed)) Payload;

typedef struct {
	MsgType_e msgType;
	CardType_e cardType;
} Ack;

typedef void (*DataProcess_t)(DataSensor *);

void releaseCommunication(CardType_e cardType);
void getCommunication(CardType_e cardType);
void sendAck(Payload *payload);
void receivingData(Payload *payload);
void prepareReceivingData(Payload *payload);
void setUpSensor(Payload *payload);
void setupRF();

extern Payload payload;
extern bool lastCommunication;
extern bool card[MAX_CARD];

#endif /* INCLUDE_RADIO_H_ */
