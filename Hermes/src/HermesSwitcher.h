/*
 * @file HermesSwitcher.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_HERMESSWITCHER_H
#define CODE_HERMESSWITCHER_H

#include "HermesCollector.h"
#include "HermesDataSender.h"
#include "HermesReanimator.h"

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
 * @function extern void setCO(int rateCO)
 * @brief setter of the measurement of the CO (carbon monoxide)
 * @param rateCO the CO rate
 */
extern void setCO(int rateCO);

/**
 * @function extern void setCO2(int rateCO2)
 * @brief setter of the measurement of the CO2 (carbon dioxide)
 * @param rateCO2 the CO2 rate
 */
extern void setCO2(int rateCO2);


/**
 * @function extern void setO3(int rateO3)
 * @brief setter of the measurement of the O3 (ozone)
 * @param rateO3 the O3 rate
 */
extern void setO3(int rateO3);


/**
 * @function extern void setNO2(int rateNO2)
 * @brief setter of the measurement of the NO2 (nitrogen dioxide)
 * @param rateNO2 the NO2 rate
 *
 */
extern void setNO2(int rateNO2);

/**
 * @function extern void setNH3(int rateNH3)
 * @brief setter of the measurement of the NH3 (ammonia)
 * @param rateNH3 the NH3 rate
 */
extern void setNH3(int rateNH3);

#endif //CODE_HERMESSWITCHER_H
