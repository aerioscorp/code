/*
 * luminos.h
 *
 *  Created on: 23 janv. 2018
 *      Author: Corentin
 */

#ifndef INCLUDE_SENSOR_H_
#define INCLUDE_SENSOR_H_

/*
 * Structures de données des capteurs
 */
typedef enum : uint8_t {
		AEROS,
		LUMINOS,
		PRECIPITOS,
		THERMOS,
		MAX_CARD
} CardType_e;

typedef enum : uint8_t {
		CO,
		CO2,
		DIRECTION_VENT,
		HUMIDITE,
		LUMINOSITE,
		NH3,
		NO2,
		O3,
		PARTICULES,
		PLUVIOMETRIE,
		PRESSION,
		TEMPERATURE,
		UV,
		VITESSE_VENT,
		MAX_SENSOR
} SensorType_e;

typedef struct {
	SensorType_e sensorType_01;
	uint32_t value_01;
	SensorType_e sensorType_02;
	uint32_t value_02;
} __attribute__((packed)) DataAeros;

typedef struct {
	SensorType_e sensorType_01;
	uint32_t value_01;
	SensorType_e sensorType_02;
	uint32_t value_02;
} __attribute__((packed)) DataLuminos;

typedef struct {
	SensorType_e sensorType_01;
	uint32_t value_01;
	SensorType_e sensorType_02;
	uint32_t value_02;
} __attribute__((packed)) DataPrecipitos;

typedef struct {
	SensorType_e sensorType_01;
	uint32_t value_01;
	SensorType_e sensorType_02;
	uint32_t value_02;
} __attribute__((packed)) DataThermos;

typedef union {
	DataAeros dataAeros;
	DataLuminos dataLuminos;
	DataPrecipitos dataPrecipitos;
	DataThermos dataThermos;
} __attribute__((packed)) DataSensor;

void aerosDataProcess(DataSensor *dataSensor);
void luminosDataProcess(DataSensor *dataSensor);
void precipitosDataProcess(DataSensor *dataSensor);
void thermosDataProcess(DataSensor *dataSensor);
void setupSensor();

const String sensorType_str[MAX_SENSOR] {
		"CO",
		"CO2",
		"DIRECTION_VENT",
		"HUMIDITE",
		"LUMINOSITE",
		"NH3",
		"NO2",
		"O3",
		"PARTICULES",
		"PLUVIOMETRIE",
		"PRESSION",
		"TEMPERATURE",
		"UV",
		"VITESSE_VENT",
};

extern uint32_t valueStorage[MAX_SENSOR];

#endif /* INCLUDE_SENSOR_H_ */
