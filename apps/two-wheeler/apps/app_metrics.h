/*******************************************************************************
  Performance Metrics Display Header

  Company:
    Microchip Technology Inc.

  File Name:
    app_metrics.h

  Summary:
    Interface for performance metrics label updates.

  Description:
    This module provides functions to update performance metrics labels
    (Update%, Draw%, FPS) on any screen that has the standard metrics widgets.
 *******************************************************************************/

#ifndef APP_METRICS_H
#define APP_METRICS_H

#include "gfx/legato/legato.h"

#ifdef __cplusplus
extern "C" {
#endif

#define METRICS_UPDATE_INTERVAL_MS 1000

void Metrics_Init(void);
bool Metrics_Update(leLabelWidget* lblUpdatePct, leLabelWidget* lblDrawPct, leLabelWidget* lblFPSValue);

#ifdef __cplusplus
}
#endif

#endif /* APP_METRICS_H */