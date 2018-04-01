/*
 * @file ZeusDataSender.c
 * @brief TODO
 * @author TODO
 * @date 17/11/17.
 * @version 1.0
 */

#include "ZeusDataSender.h"

#define NUMBER_OF_BYTE_SENT_ZEUS 8

const static uint8_t ZEUS_TYPE = 3;

/**
 * Messages coming from Zeus
 */
typedef struct {
    uint16_t precipitValue;           // Valeur entre 0.1 et 50
    uint16_t windSpeedValue;          // Valeur entre 0.1 et 50 m/s
    uint8_t windDirectionValue;      // Valeur entre 0 et 7 (Direction)
    uint8_t pm10Value;               // Valeur entre 0 et 60 ug/m3
}zeusMessage_t;

typedef union {
    zeusMessage_t zeusMessageStruct;
    char data[MAX_PAYLOAD + 1];
}zeusMessage_u;

typedef struct {
    uint8_t sender;          	 // 8 bit - Id of sender (origin)
    uint8_t messageType;
    apollonMessage_u message;
}messageType_t;

typedef union {
    messageType_t message;
    uint8_t array[HEADER_SIZE + MAX_PAYLOAD + 1];
} message_u;

/**
 * See ZeusDataSender.h
 */
extern void dataSenderInit()
{
    //TODO
}

/**
 * See ZeusDataSender.h
 */
extern void dataSenderDestroy()
{
    //TODO
}

/**
 * See ZeusDataSender.h
 */
extern void sendData(char[])
{
    //TODO
}