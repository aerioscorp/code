/*
 * @file ApollonReanimator.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_APOLLONREANIMATOR_H
#define CODE_APOLLONREANIMATOR_H

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
 * @brief wakes up Apollon
 */
extern void putActiveMode();

/**
 * @function extern void putSleepMode()
 * @brief puts Apollon to sleep
 */
extern void putSleepMode();

#endif //CODE_APOLLONREANIMATOR_H
