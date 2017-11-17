/*
 * @file ZeusCollector.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_ZEUSCOLLECTOR_H
#define CODE_ZEUSCOLLECTOR_H

#include "ZeusSwitcher.h"

/**
 * @function extern void collectorInit()
 * @brief creates the collector
 */
extern void collectorInit();

/**
 * @function extern void collectorDestroy()
 * @brief destroys the collector
 */
extern void collectorDestroy();

/**
 * @function extern void launchCollector()
 * @brief launch the measurement of ZeusCollector
 */
extern void launchCollector();

#endif //CODE_ZEUSCOLLECTOR_H
