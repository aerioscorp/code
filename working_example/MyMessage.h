/*
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

/**
 * @file MyMessage.h
 *
 * @brief API and type declarations for MySensors messages
 * @defgroup MyMessagegrp MyMessage
 * @{
 *
 * @brief Here you can find all message types used by the MySensors protocol as well as macros for
 * parsing and manipulating messages.
 */
#ifndef MyMessage_h
#define MyMessage_h

#define MAX_MESSAGE_LENGTH	(32u)	//!< The maximum size of a message (including header)
#define HEADER_SIZE			(2u)	//!< The size of the header
#define MAX_PAYLOAD (MAX_MESSAGE_LENGTH - HEADER_SIZE) //!< The maximum size of a payload depends of MAX_MESSAGE_LENGTH and HEADER_SIZE

/// @brief The command field (message-type) defines the overall properties of a message
typedef enum {
	CONFIGURATION					= 0,
	ASK_SEND_DATA					= 1,
	SEND_DATA			        	= 2
} myCommand;

/// @brief Type of sensor (used when presenting sensors)
typedef enum {
	UV					= 12,
	BRIGHTNESS          = 4
	//TODO Ajouter les autres
} mySensor;


/**
 * Messages coming from Apollon
 */
typedef struct {
	mySensor sensor1;
	uint32_t uvValue;         // Valeur entre 1 et 15;
	mySensor sensor2;
	uint32_t brigthValue;    //Valeur entre 0.001 et 150 000 lux
}apollonMessage_t;

typedef union {
	apollonMessage_t apollonMessageStruct;
	char data[MAX_PAYLOAD + 1];
}apollonMessage_u;

/**
 * Messages coming from Athena
 */
typedef struct {
	mySensor sensor1;
	int8_t tempValue;       // Valeur entre -80 et +80 °C
	mySensor sensor2;
	uint8_t humValue;        // Valeur entre 0 et 100 %
	mySensor sensor3;
	uint16_t pressValue;      // Valeur aux alentours de 1015 hPa
}athenaMessage_t;

typedef union {
	athenaMessage_t athenaMessageStruct;
	char data[MAX_PAYLOAD + 1];
}athenaMessage_u;

/**
 * Messages coming from Hermes
 */
typedef struct {
	mySensor sensor1;
	uint16_t c02Value;      // Valeur entre 0 et 30 000 ppm
	mySensor sensor2;
	uint16_t c0Value;        // Valeur entre 0 et 12800 ppm
	mySensor sensor3;
	uint16_t n02Value;       // Valeur entre 0 et 400 ug/m3
	mySensor sensor4;
	uint8_t o3Value;        // Valeur entre 0 et 200 ug/m3
	mySensor sensor5;
	uint8_t nh3Value;       // Valeur entre 0 et 60 ppm
}hermesMessage_t;

typedef union {
	hermesMessage_t hermesMessageStruct;
	char data[MAX_PAYLOAD + 1];
}hermesMessage_u;

/**
 * Messages coming from Zeus
 */
typedef struct {
	mySensor sensor1;
	uint16_t precipitValue;           // Valeur entre 0.1 et 50
	mySensor sensor2;
	uint16_t windSpeedValue;          // Valeur entre 0.1 et 50 m/s
	mySensor sensor3;
	uint8_t windDirectionValue;      // Valeur entre 0 et 7 (Direction)
	mySensor sensor4;
	uint8_t pm10Value;               // Valeur entre 0 et 60 ug/m3
}zeusMessage_t;

typedef union {
	zeusMessage_t zeusMessageStruct;
	char data[MAX_PAYLOAD + 1];
}zeusMessage_u;


/**
 * Message Types
 */

typedef union {
	char data[MAX_PAYLOAD + 1];
	uint8_t type;
}otherMessage_u;

typedef union {
	apollonMessage_u apollonMessage;
	athenaMessage_u athenaMessage;
	hermesMessage_u hermesMessage;
	zeusMessage_u zeusMessage;
	otherMessage_u otherMessage;
}messageType_u;

typedef struct {
	uint8_t command;
	uint8_t cardType;
	messageType_u messageType;
}message_t;


/**
 * Message sent and received
 */
typedef union {
	message_t message;
	uint8_t array[HEADER_SIZE + MAX_PAYLOAD + 1];
} message_u;

#endif
/** @}*/
