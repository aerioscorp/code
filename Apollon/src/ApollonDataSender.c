/*
 * @file ApollonDataSender.c
 * @brief TODO
 * @author Sami KOUATLI
 * @date 17/11/17.
 * @version 1.0
 */

#include "ApollonDataSender.h"
#include "/lib/nRF24LE1_POC_TEKKA.c"


#define CHILD_ID_APOLLON 0
#define CHILD_ID_APOLLON_DESCRIPTION_CONNECT "apollonConnect"
#define CHILD_ID_APOLLON_DESCRIPTION_DISCONNECT "apollonDisconnect

/**
 * See ApollonDataSender.h
 */
extern void dataSenderInit()
{
    setRF24_CHANNEL(84);
    uint8_t base_addr[5] = {0xFF,0xFC,0xE1,0xA8,0xA8};
    setBaseAddress(base_addr);

    setup();
    present(CHILD_ID_APOLLON, S_CUSTOM, CHILD_ID_APOLLON_DESCRIPTION_CONNECT);
}

/**
 * See ApollonDataSender.h
 */
extern void sendData()
{
    // init
    setup(); //TODO Necessaire ?
    // loop
    while(1) {

        watchdog_calc_timeout_from_sec(3);

        /** pour Apollon : */

        //UV
        outMsg.bValue = getUV();
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_APOLLON,C_SET,V_UV, P_BYTE,4,false);
        SendMessage();

        //Bright
        outMsg.ulValue = getBrightness();
        BuildMessage(GATEWAY_ADDRESS,CHILD_ID_APOLLON,C_SET,V_LIGHT_LEVEL,P_ULONG32,4+1,false);
        SendMessage();

        // process / wait
        process_time(2000);
    }
}