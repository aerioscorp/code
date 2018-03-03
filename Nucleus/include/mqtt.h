/*
 * mqtt.h
 *
 *  Created on: 23 janv. 2018
 *      Author: Corentin
 */

#ifndef INCLUDE_MQTT_H_
#define INCLUDE_MQTT_H_

#include "sensor.h"

/*
 * Define pour la communication MQTT
 */
#define WIFI_SSID			"IoT"
#define WIFI_PWD 			"!IotEseo49"
#define MQTT_HOST 			"172.17.1.1"
#define MQTT_PORT 1883
#define NAME_PUBLISHER 		"PFE_ESP8266"
#define MQTT_USERNAME		""
#define MQTT_PWD			""
#define TOPIC				((String)"main/pfe/sensors")

void connectFail(String ssid, uint8_t ssid_len, uint8_t bssid[6], uint8_t reason);
void gotIP(IPAddress ip, IPAddress netmask, IPAddress gateway);
void checkMQTTDisconnect(TcpClient& client, bool flag);
void startMqttClient();
void publishMessage();
void setupMQTT();
void lightSleep_On();
void lightSleep_Off();

#endif /* INCLUDE_MQTT_H_ */
