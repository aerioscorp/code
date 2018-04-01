/*
 * @file HermesDataSender.c
 * @brief TODO
 * @author TODO
 * @date 17/11/17.
 * @version 1.0
 */

#include "HermesDataSender.h"

#define NUMBER_OF_BYTE_SENT_HERMES 10

const static uint8_t HERMES_TYPE = 2;

typedef struct {
    uint16_t c02Value;      // Valeur entre 0 et 30 000 ppm
    uint16_t c0Value;        // Valeur entre 0 et 12800 ppm
    uint16_t n02Value;       // Valeur entre 0 et 400 ug/m3
    uint8_t o3Value;        // Valeur entre 0 et 200 ug/m3
    uint8_t nh3Value;       // Valeur entre 0 et 60 ppm
}hermesMessage_t;

typedef union {
    hermesMessage_t hermesMessageStruct;
    char data[MAX_PAYLOAD + 1];
}hermesMessage_u;

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
 * See HermesDataSender.h
 */
extern void dataSenderInit()
{
    //TODO
}

/**
 * See HermesDataSender.h
 */
extern void dataSenderDestroy()
{
    //TODO
}

/**
 * See HermesDataSender.h
 */
extern void sendData(char[])
{
    //TODO
}