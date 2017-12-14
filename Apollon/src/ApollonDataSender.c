/*
 * @file ApollonDataSender.c
 * @brief TODO
 * @author TODO
 * @date 17/11/17.
 * @version 1.0
 */

#include "ApollonDataSender.h"

#define NUMBER_OF_BYTE_SENT_APOLLON 7

const static uint8_t APOLLON_TYPE = 0;

typedef struct {
    uint8_t uvValue;            // Valeur entre 1 et 15;
    uint32_t brigthValue;      //Valeur entre 0.001 et 150 000
}apollonMessage_t;

typedef union {
    apollonMessage_t apollonMessageStruct;
    char data[MAX_PAYLOAD + 1];
}apollonMessage_u;


typedef struct {
    uint8_t sender;          	 // 8 bit - Id of sender (origin)
    uint8_t messageType;
    apollonMessage_u message;
}messageType_t;

/**
 * Message sent and received
 */
typedef union {
    messageType_t message;
    uint8_t array[HEADER_SIZE + MAX_PAYLOAD + 1];
} message_u;


/**
 * See ApollonDataSender.h
 */
extern void dataSenderInit()
{
    //TODO
}

/**
 * See ApollonDataSender.h
 */
extern void dataSenderDestroy()
{
    //TODO
}

/**
 * See ApollonDataSender.h
 */
extern void sendData(char[])
{
    //TODO
}