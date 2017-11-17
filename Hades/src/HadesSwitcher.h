/*
 * @file HadesSwitcher.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_HADESSWITCHER_H
#define CODE_HADESSWITCHER_H

#include "HadesCollector.h"
#include "HadesDataSender.h"
#include "HadesReanimator.h"
#include "HadesDataReceiver.h"

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
 * @function extern void setPicture(int picture)
 * @brief setter of the picture
 * @param picture taken
 */
extern void setPicture(char[] picture);

/**
 * @function extern void setGPS(int[] GPS)
 * @brief setter of the  GPS coordonates
 * @param coordsGPS found
 */
extern void setGPS(int[] coordsGPS);

#endif //CODE_HADESSWITCHER_H
