/*
 * @file AthenaDataSender.c
 * @brief TODO
 * @author TODO
 * @date 17/11/17.
 * @version 1.0
 */

#include "AthenaDataSender.h"

#define NUMBER_OF_BYTE_SENT_ATHENA 6

const static uint8_t ATHENA_TYPE = 1;

typedef struct {
    int8_t tempValue;       // Valeur entre -80 et +80 °C
    uint8_t humValue;        // Valeur entre 0 et 100 %
    uint16_t pressValue;      // Valeur aux alentours de 1015 hPa
}athenaMessage_t;

typedef union {
    athenaMessage_t athenaMessageStruct;
    char data[MAX_PAYLOAD + 1];
}athenaMessage_u;

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
 * See AthenaDataSender.h
 */
extern void dataSenderInit()
{
    //TODO
}

/**
 * See AthenaDataSender.h
 */
extern void dataSenderDestroy()
{
    //TODO
}

/**
 * See AthenaDataSender.h
 */
extern void sendData(char[])
{
    //TODO
}