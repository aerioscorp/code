/*
 * @file ZeusReanimator.h
 * @brief 
 * @author 
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_ZEUSREANIMATOR_H
#define CODE_ZEUSREANIMATOR_H

/**
 * @function extern void reanimatorInit()
 * @brief creates the reanimator
 */
extern void reanimatorInit();

/**
 * @function extern void reanimatorDestroy()
 * @brief destroys the reanimator
 */
extern void reanimatorDestroy();

/**
 * @function extern void putActiveMode()
 * @brief wakes up Zeus
 */
extern void putActiveMode();

/**
 * @function extern void putSleepMode()
 * @brief puts Zeus to sleep
 */
extern void putSleepMode();

#endif //CODE_ZEUSREANIMATOR_H
