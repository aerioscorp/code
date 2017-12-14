/*
 * @file ZeusSwitcher.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_ZEUSSWITCHER_H
#define CODE_ZEUSSWITCHER_H

#include "ZeusCollector.h"
#include "ZeusDataSender.h"
#include "ZeusReanimator.h"

uint8_t NORTH=0;
uint8_t NORTH_EAST=1;
uint8_t EAST=2;
uint8_t SOUTH_EAST=3;
uint8_t SOUTH=4;
uint8_t SOUTH_WEST=5;
uint8_t WEST=6;
uint8_t NORTH_WEST=7;


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
 * @function extern void setPrecipitation(int precipitation)
 * @brief setter of the precipitations
 * @param precipitation rate
 */
extern void setPrecipitation(int precipitation);

/**
 * @function extern void setWindSpeed(int windSpeed)
 * @brief setter of the wind speed
 * @param windSpeed the speed of the wind
 */
extern void setWindSpeed(int windSpeed);

/**
 * @function extern void setWindDirection(uint8_t windDirection)
 * @brief setter of the wind direction
 * @param windDirection the direction of the wind
 */
extern void setWindDirection(uint8_t windDirection);

/**
 * @function extern void setPM10(int PM10)
 * @brief setter of the PM10
 * @param PM10 the particulate matter rate
 */
extern void setPM10(int PM10);

#endif //CODE_ZEUSSWITCHER_H
