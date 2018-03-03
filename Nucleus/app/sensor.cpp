/*
 * sensor.cpp
 *
 *  Created on: 23 janv. 2018
 *      Author: Corentin
 */

#include <SmingCore/HardwareSerial.h>

#include "../include/sensor.h"
#include "../include/app_config.h"

/*
 * Fonction de stockage pour Aeros
 */
void aerosDataProcess(DataSensor *dataSensor) {
	Serial.println("Info > Store value");
}

/*
 * Fonction de stockage pour Luminos
 */
void luminosDataProcess(DataSensor *dataSensor) {
	Serial.println("Info > Store value");
	Serial.printf("Info > %s = %d ", sensorType_str[dataSensor->dataLuminos.sensorType_01].c_str(), dataSensor->dataLuminos.value_01);
	Serial.println();
	Serial.printf("Info > %s = %d ", sensorType_str[dataSensor->dataLuminos.sensorType_02].c_str(), dataSensor->dataLuminos.value_02);
	Serial.println();
	valueStorage[dataSensor->dataLuminos.sensorType_01] = dataSensor->dataLuminos.value_01;
	valueStorage[dataSensor->dataLuminos.sensorType_02] = dataSensor->dataLuminos.value_02;
}

/*
 * Fonction de stockage pour Precipitos
 */
void precipitosDataProcess(DataSensor *dataSensor) {
	Serial.println("Info > Store value");
	Serial.println("Info > Pas encore implémenté");
}

/*
 * Fonction de stockage pour Thermos
 */
void thermosDataProcess(DataSensor *dataSensor) {
	Serial.println("Info > Store value");
	Serial.println("Info > Pas encore implémenté");
}

/*
 * Fonction d'initilisation des valeurs de capteurs.
 */
void setupSensor() {
	int i;
	for(i = 0; i < MAX_SENSOR; i++)
		valueStorage[i] = 65535;
}
