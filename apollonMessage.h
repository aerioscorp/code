//
// Created by sami on 07/12/17.
//

#ifndef PFE_APOLLONMESSAGE_H
#define PFE_APOLLONMESSAGE_H


#define MAX_MESSAGE_LENGTH	(32u)	//!< The maximum size of a message (including header)
#define HEADER_SIZE			(2u)	//!< The size of the header
#define MAX_PAYLOAD (MAX_MESSAGE_LENGTH - HEADER_SIZE) //!< The maximum size of a payload depends of MAX_MESSAGE_LENGTH and HEADER_SIZE

typedef union {
    struct {
        uint8_t sender;          	 // 8 bit - Id of sender (origin)
        uint8_t MessageType;         // ApollonType                 //TODO Faire la structure MessageType

        // Each message can transfer a payload. We add one extra byte for string
        // terminator \0 to be "printable" this is not transferred OTA
        // This union is used to simplify the construction of the binary data types transferred.
        union {
            struct { // Float messages
                uint8_t uvValue;        // Valeur entre 1 et 15;
                uint32_t brigthValue;      //Valeur entre 0.001 et 150 000
            };
            char data[MAX_PAYLOAD + 1];
        };
    };
    uint8_t array[HEADER_SIZE + MAX_PAYLOAD + 1];
} apollonMessage;


#endif //PFE_APOLLONMESSAGE_H
