#include <RF24/RF24.h>
#include <SmingCore/HardwareSerial.h>
#include <SmingCore/Timer.h>

#include "../include/user_config.h"
#include "../include/app_config.h"

/*
 * Variables
 */
State_t state[] = { setUpSensor, prepareReceivingData, receivingData };
bool card[MAX_CARD];
bool lastCommunication;
RF24 radio(4, 15);
Payload payload;
bool flag_rf = false;
static Timer procTimer;

/*
 * Fonction d'interruption, d�s qu'une trame est re�u, un flag est lev� et le message est lu.
 */
void IRAM_ATTR interruptHandler() {
	Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> INTERRUPTION <<<<<<<<<<<<<<<<<<<<<<<<<<<");
	if (!flag_rf && radio.available()) {
		flag_rf = true;
		radio.read(&payload, radio.getDynamicPayloadSize());
	}
}

/*
 * Boucle de fond, d�s qu'un flag est lev�, le message est trait� et le processus suit son cours.
 */
void process() {
	if (flag_rf) {
		Serial.println("Info > Got payload");
		if (!lastCommunication || (lastCommunication && card[payload.cardType])) {
			state[payload.msgType](&payload);
			flag_rf = false;
			Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> END TREATMENT <<<<<<<<<<<<<<<<<<<<<<<<<<<");
		} else {
			flag_rf = false;
		}
	}

}

/*
 * Fonction d'initialisation du microcontroleur.
 * Tous les p�riph�riques utilis�s sont initialis�s.
 * L'interruption RF est activit�.
 * La boucle de fond est lanc�.
 */
void init() {
	Serial.begin(SERIAL_BAUD_RATE);
	Serial.systemDebugOutput(true);

	setupSensor();
	setupMQTT();
	setupRF();


	attachInterrupt(INT_PIN, interruptHandler, FALLING);
	procTimer.initializeMs(2, process).start();
}

