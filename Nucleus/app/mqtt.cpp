/*
 * mqtt.cpp
 *
 *  Created on: 23 janv. 2018
 *      Author: Corentin
 */

#include <SmingCore/SmingCore.h>
#include <SmingCore/Timer.h>
#include <SmingCore/HardwareSerial.h>

#include "../include/mqtt.h"

MqttClient *mqtt;
static Timer procTimer;
uint32_t valueStorage[MAX_SENSOR];

/*
 * Fonction appelée dès que la connexion Wi-Fi a échouée.
 */
void connectFail(String ssid, uint8_t ssid_len, uint8_t bssid[6], uint8_t reason) {
	Serial.println("Error > Connection to Wi-Fi failed !");
}

/*
 * Fonction appelée dès que un IP a été attribué.
 * Le client MQTT est lancé.
 */
void gotIP(IPAddress ip, IPAddress netmask, IPAddress gateway) {
	startMqttClient();
	//publishMessage();
}

/*
 * Fonction appelée dès la déconnexion du MQTT
 * On tente de reconnecter le client MQTT toutes les 2ms.
 */
void checkMQTTDisconnect(TcpClient& client, bool flag) {
	if (flag == true)
		Serial.println("Error > MQTT Broker Disconnected");
	else
		Serial.println("Error > MQTT Broker Unreachable");
	procTimer.initializeMs(2 * 1000, startMqttClient).start();
}

/*
 * Fonction de démarrage du client MQTT.
 * On se connecte au broker.
 */
void startMqttClient() {
	if (!mqtt->setWill("last/will", "Error > The connection from this device is lost:(", 1, true)) {
		debugf("Error > Unable to set the last will and testament. Most probably there is not enough memory on the device.");
	}

	mqtt->connect(NAME_PUBLISHER);
	mqtt->setCompleteDelegate(checkMQTTDisconnect);
}

/*
 * Fonction de publication de message.
 * On se connecte au broker MQTT si ce n'est pas fait
 * Puis on envoie les informations de tous les capteurs sous-forme de requête SQL,
 * ce qui facilitera l'insertion SQL par la suite.
 */
void publishMessage() {
	String msg;
	int i;

	if (mqtt->getConnectionState() != eTCS_Connected)
		startMqttClient();

	for(i = 0; i < MAX_SENSOR; i++) {
		if(valueStorage[i] != 65535) {
			Serial.println("Info > Sending values to server");
			msg = "INSERT INTO " + sensorType_str[i] + " (VALEUR) VALUES (" + valueStorage[i] + ")";
			mqtt->publish(TOPIC, msg);
			valueStorage[i] = 65535;
		}
	}
	//lightSleep_On();
}

/*
 * Fonction d'initialisation et configration du MQTT
 * Configuration du Wi-Fi et des appels de fonctions.
 */
void setupMQTT() {
	Serial.println("Info > Start initialization MQTT");
	mqtt = new MqttClient(MQTT_HOST, MQTT_PORT);
	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiStation.enable(true);
	WifiAccessPoint.enable(false);
	WifiEvents.onStationDisconnect(connectFail);
	WifiEvents.onStationGotIP(gotIP);
	//lightSleep_On();
	Serial.println("Info > Initialization MQTT completed");
}

/*
 * Fonction à revoir du mode d'endormissement du microcontroleur.
 */
void lightSleep_On() {
	wifi_station_disconnect();
	wifi_set_opmode(NULL_MODE);				//	set	WiFi	mode	to	null	mode.
	wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);	//	light	sleep
	wifi_fpm_open();						//	enable	force	sleep
}

/*
 * Fonction à revoir du mode de réveil du microcontroleur.
 */
void lightSleep_Off() {
	wifi_fpm_close();				//	disable	force	sleep	function
	wifi_set_opmode(STATION_MODE);	//	set	station	mode
	wifi_station_connect();			//	connect	to	AP
}
