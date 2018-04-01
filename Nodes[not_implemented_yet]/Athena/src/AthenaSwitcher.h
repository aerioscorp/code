/*
 * @file AthenaSwitcher.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_ATHENASWITCHER_H
#define CODE_ATHENASWITCHER_H

#include "AthenaCollector.h"
#include "AthenaDataSender.h"
#include "AthenaReanimator.h"

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
 * @function extern void setPressure(int pressure)
 * @brief setter of the pressure
 * @param pressure rate
 */
extern void setPressure(int pressure);

/**
 * @function extern void setTemperature(int temperature)
 * @brief setter of the temperature
 * @param temperature rate
 */
extern void setTemperature(int temperature);

/**
 * @function extern void setHumidity(int humidity)
 * @brief setter of the humidity
 * @param humidity rate
 */
extern void setHumidity(int humidity);

#endif //CODE_ATHENASWITCHER_H
