/*
 * @file ApollonSwitcher.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_APOLLONSWITCHER_H
#define CODE_APOLLONSWITCHER_H

#include "ApollonCollector.h"
#include "ApollonDataSender.h"
#include "ApollonReanimator.h"


/**
 * @function extern void switcherInit()
 * @brief creates the switcher
 */
extern void switcherInit();

/**
 * @function extern void switcherDestroy()
 * @brief destroys the switcher
 */
extern void switcherDestroy();

/**
 * @function extern void setUV(int UV)
 * @brief setter of the UV rate
 * @param UV rate
 */
extern void setUV(int UV);

/**
 * @function extern void setBrightness(int brightness)
 * @brief setter of the brightness rate
 * @param brightness rate
 */
extern void setBrightness(int brightness);

#endif //CODE_APOLLONSWITCHER_H
