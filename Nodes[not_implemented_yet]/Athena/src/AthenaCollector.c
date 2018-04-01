/*
 * @file AthenaCollector.c
 * @brief TODO
 * @author TODO
 * @date 17/11/17.
 * @version 1.0
 */

#include "AthenaCollector.h"

/* Function prototypes */
static void takePressure();
static void takeTemperature();
static void takeHumidity();


/**
 * See AthenaCollector.h
 */
extern void collectorInit()
{
    //TODO
}

/**
 * See AthenaCollector.h
 */
extern void collectorDestroy()
{
    //TODO
}

/**
 * See AthenaCollector.h
 */
extern void launchCollector()
{
    takeHumidity();
    takePressure();
    takeTemperature();
}



/**
 * @function static void takeBrightness()
 * @brief takes the pressure measurement
 */
static void takePressure()
{
    //TODO
}

/**
 * @function static void takeUV()
 * @brief takes the temperature measurement
 */
static void takeTemperature()
{
    //TODO
}

/**
 * @function static void takeUV()
 * @brief takes the humidity measurement
 */
static void takeHumidity()
{
    //TODO
}
