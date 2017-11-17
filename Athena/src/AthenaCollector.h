/*
 * @file AthenaCollector.h
 * @brief TODO
 * @author Sami
 * @date 17/11/17.
 * @version 1.0
 */

#ifndef CODE_ATHENACOLLECTOR_H
#define CODE_ATHENACOLLECTOR_H

#include "AthenaSwitcher.h"

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
 * @brief launch the measurement of AthenaCollector
 */
extern void launchCollector();

#endif //CODE_ATHENACOLLECTOR_H
