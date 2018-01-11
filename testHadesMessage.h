//
// Created by sami on 14/12/17.
//

#ifndef PFE_TESTMESSAGE_H
#define PFE_TESTMESSAGE_H


#define MAX_MESSAGE_LENGTH	(32u)	//!< The maximum size of a message (including header)
#define HEADER_SIZE			(2u)	//!< The size of the header
#define MAX_PAYLOAD (MAX_MESSAGE_LENGTH - HEADER_SIZE) //!< The maximum size of a payload depends of MAX_MESSAGE_LENGTH and HEADER_SIZE

/**
 * Messages coming from Apollon
 */
typedef struct {
    uint8_t uvValue;         // Valeur entre 1 et 15;
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
    int8_t tempValue;       // Valeur entre -80 et +80 °C
    uint8_t humValue;        // Valeur entre 0 et 100 %
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

/**
 * Message Types
 */
typedef union {
    apollonMessage_u apollonMessage;
    athenaMessage_u athenaMessage;
    hermesMessage_u hermesMessage;
    zeusMessage_u zeusMessage;
}messageType_u;

typedef struct {
    uint8_t sender;          	 // 8 bit - Id of sender (origin)
    uint8_t destination;     	 // 8 bit - Id of destination node
    uint8_t version_length;		 // 2 bit - Protocol version
    // 1 bit - Signed flag
    // 5 bit - Length of payload
    uint8_t command_ack_payload; // 3 bit - Command type
    // 1 bit - Request an ack - Indicator that receiver should send an ack back.
    // 1 bit - Is ack messsage - Indicator that this is the actual ack message.
    // 3 bit - Payload data type
    uint8_t messageType;
    messageType_u message;
}messageType_t;


/**
 * Message sent and received
 */
typedef union {
    messageType_t message;
    uint8_t array[HEADER_SIZE + MAX_PAYLOAD + 1];
} message_u;

#endif //PFE_TESTMESSAGE_H
