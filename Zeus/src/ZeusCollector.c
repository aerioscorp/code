/*
 * @file ZeusCollector.c
 * @brief TODO
 * @author TODO
 * @date 17/11/17.
 * @version 1.0
 */

#include "ZeusCollector.h"

// TODO Voir où mettre cet enum.
/* Function prototypes */
static void takePrecipitations();
static void takeWindSpeed();
static void takeWindDirection();
static void takePM10();


/**
 * See ZeusCollector.h
 */
extern void collectorInit()
{
    //TODO
}

/**
 * See ZeusCollector.h
 */
extern void collectorDestroy()
{
    //TODO
}

/**
 * See ZeusCollector.h
 */
extern void launchCollector()
{
    //TODO Faire mesure pluviomètre sur une durée.
    takePrecipitations();
    takeWindSpeed();
    takeWindDirection();
    takePM10();
}





/**
 * @function static void takePrecipitations()
 * @brief takes the precipitation measurement
 */
static void takePrecipitations()
{
    //TODO
}

/**
 * @function static void takeWindSpeed()
 * @brief takes the wind speed measurement
 */
static void takeWindSpeed()
{
    //TODO
}

/**
 * @function static void takeWindDirection()
 * @brief takes the wind direction
 */
static void takeWindDirection()
{
    //TODO
}

/**
 * @function static void takePM10()
 * @brief takes the particulate matter measurement
 */
static void takePM10()
{
    //TODO
}

/**
 * @function static void takeNH3()
 * @brief takes the NH3 (ammonia) measurement
 */
static void takeNH3()
{
    //TODO
}