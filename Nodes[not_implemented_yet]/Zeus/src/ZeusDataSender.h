/*
 * @file ZeusDataSender.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_ZEUSDATASENDER_H
#define CODE_ZEUSDATASENDER_H

/**
 * @function extern void dataSenderInit()
 * @brief creates the dataSender
 */
extern void dataSenderInit();

/**
 * @function extern void dataSenderDestroy()
 * @brief destroys the dataSender
 */
extern void dataSenderDestroy();

/**
 * @function extern void sendData(char[])
 * @brief sends the data to the Nucleus
 */
extern void sendData(char[]);

#endif //CODE_ZEUSDATASENDER_H
