/*
 * @file ApollonCollector.c
 * @brief TODO
 * @author Sami KOUATLI
 * @date 17/11/17.
 * @version 1.0
 */

#include "ApollonCollector.h"
#include "/lib/Measurer"

#define GPIO_UV_PIN GPIO_PIN_ID_P0_0

/* Function prototypes */
static void takeUV();
static void takeBrightness();

/**
 * See ApollonCollector.h
 */
extern void launchCollector()
{
    takeBrightness();
    takeUV();
}


/**
 * @function static void takeBrightness()
 * @brief takes the brightness measurement (I2C)
 */
static void takeBrightness()
{
    configI2C();
    configOPT3001();
    uint16_t bright =  readOPT3001();

    uint32_t brightRealValue = bright * 1; //TODO Faire la conversion en données réelles

    setBrightness(brightRealValue);
}

/**
 * @function static void takeUV()
 * @brief takes the UV measurement (Analogic, converted with ADC)
 */
static void takeUV()
{
    configADC(GPIO_UV_PIN);
    uint16_t uv = readADC(GPIO_UV_PIN);

    uint8_t uvRealValue = uv * 1; //TODO Faire la conversion en données réelles

    setUV(uvRealValue);
}