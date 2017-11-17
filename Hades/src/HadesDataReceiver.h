/*
 * @file HadesDataReceiver.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_HADESDATARECEIVER_H
#define CODE_HADESDATARECEIVER_H

#include "HadesSwitcher.h"
#include "HadesReanimator.h"

/* Function prototypes */
static void verfyId();
static void assignDataById();

/**
 * @function extern void dataReceiverInit()
 * @brief creates the dataReceiver
 */
extern void dataReceiverInit();

/**
 * @function extern void dataReceiverDestroy()
 * @brief destroys the dataReceiver
 */
extern void dataSenderDestroy();

/**
 * @function extern char[] receiveData()
 * @brief receives the data from the nodes
 */
extern char[] receiveData();

#endif //CODE_HADESDATARECEIVER_H

/**
 * @function static void verfyId()
 * @brief verifies the Id of the incoming message
 */
static void verfyId()
{
    //TODO
}

/**
 * @function static void assignDataById()
 * @brief assigns the data received to the right attributes of HadesSwitcher
 */
static void assignDataById()
{
    //TODO
}