/*
 * radio.cpp
 *
 *  Created on: 23 janv. 2018
 *      Author: Corentin
 */

#include <SmingCore/HardwareSerial.h>

#include "../include/radio.h"
#include "../include/app_config.h"

DataProcess_t dataProcess[] = {aerosDataProcess, luminosDataProcess, precipitosDataProcess, thermosDataProcess };

/*
 * Fonction permettant de ré-autoriser la communication NRF à tout le monde.
 */
void releaseCommunication(CardType_e cardType) {
	lastCommunication = false;
	card[cardType] = false;
}

/*
 * Fonction permettant de bloquer la communication NRF pour tous les noeuds,
 * sauf pour celui souhaitant transférer ses données.
 */
void getCommunication(CardType_e cardType) {
	lastCommunication = true;
	card[cardType] = true;
}

/*
 * Fonction permettant d'envoyer un Acknowledge au noeud communiquant.
 * Coupe l'écoute RF pour l'envoi RF.
 */
void sendAck(Payload *payload) {
	Ack ack;
	radio.stopListening();
	radio.powerDown();
	ack.msgType = payload->msgType;
	ack.cardType = payload->cardType;
	radio.write(&ack, sizeof(ack));
	radio.startListening();
}

/*
 * Fonction permettant de recevoir les données d'un noeud.
 * Stocke les données du noeud.
 * Envoie un Ack
 * Rend la communication possible à tout le monde.
 * Publie les données du noeud.
 */
void receivingData(Payload *payload) {
	Serial.println("Type du message : SEND_DATA");
	dataProcess[payload->cardType](&(payload->dataSensor));
	sendAck(payload);
	releaseCommunication(payload->cardType);
	//lightSleep_Off();
	publishMessage();
}

/*
 * Fonction autorisant le noeud communiquant a envoyé ses données.
 * Envoie un ack.
 * Prend la communication RF pour lui.
 */
void prepareReceivingData(Payload *payload) {
	Serial.println("Type du message : ASK_SEND_DATA");
	sendAck(payload);
	getCommunication(payload->cardType);
}

/*
 * Fonction configurant le noeud communiquant.
 * Envoie un ack.
 * Evolution de la fonction :
 * Il est possible d'ajouter un configuration particulière aux noeuds
 */
void setUpSensor(Payload *payload) {
	Serial.println("Type du message : CONFIGURATION");
	sendAck(payload);
}

/*
 * Fonction d'initialisation et configuration de la com RF.
 * Les paramètres configurés ici doivent être similaire à ceux des noeuds.
 * Configuration du canal, des pipes (adresse, écoute/lecture), des auto acks, du CRC.
 * Lance l'écoute RF
 */
void setupRF() {
	int i;
	for(i = 0; i < MAX_SENSOR; i++)
		card[MAX_CARD] = false;
	lastCommunication = false;

	Serial.println("Info > Start initialization RF");
	radio.begin();
	radio.setAutoAck(1);
	radio.setChannel(84);
	radio.setAutoAck(BROADCAST_PIPE, false);
	radio.enableAckPayload();
	radio.setDataRate(RF24_250KBPS);
	radio.setRetries(5, 15);
	radio.setCRCLength(RF24_CRC_16);
	radio.enableDynamicPayloads();
	radio.openWritingPipe(RF24_BASE_RADIO_ID + BROADCAST_ADDRESS);
	radio.openReadingPipe(CAPTEUR_PIPE, RF24_BASE_RADIO_ID);
	radio.openReadingPipe(BROADCAST_PIPE, RF24_BASE_RADIO_ID + BROADCAST_ADDRESS);
	radio.startListening();
	radio.printDetails();
	Serial.println("Info > Initialization RF completed");
	Serial.println("Info > Listening RF");
}


