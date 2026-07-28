/*******************************************************************************
  Performance Metrics Display Functions

  Company:
    Microchip Technology Inc.

  File Name:
    app_metrics.c

  Summary:
    Implementation of performance metrics label updates.

  Description:
    This module provides functions to update performance metrics labels
    (Update%, Draw%, FPS) on any screen that has the standard metrics widgets.
 *******************************************************************************/

 #include <stdbool.h>

#include "gfx/legato/generated/le_gen_init.h"
#include "app_metrics.h"

/*******************************************************************************
 * String Buffers for Metrics Labels
 ******************************************************************************/
#define METRICS_BUFFER_SIZE 12

static leFixedString updatePctStr;
static leChar updatePctCharBuffer[METRICS_BUFFER_SIZE];
static char updatePctCStrBuffer[METRICS_BUFFER_SIZE];

static leFixedString drawPctStr;
static leChar drawPctCharBuffer[METRICS_BUFFER_SIZE];
static char drawPctCStrBuffer[METRICS_BUFFER_SIZE];

static leFixedString fpsStr;
static leChar fpsCharBuffer[METRICS_BUFFER_SIZE];
static char fpsCStrBuffer[METRICS_BUFFER_SIZE];

static bool metricsInitialized = false;
static uint32_t lastMetricsUpdateTime = 0;

extern volatile unsigned int tickCountMS;

/*******************************************************************************
 * Metrics_Init
 * Initialize string buffers for metrics display.
 ******************************************************************************/
void Metrics_Init(void)
{
    leFixedString_Constructor(&updatePctStr, updatePctCharBuffer, METRICS_BUFFER_SIZE);
    updatePctStr.fn->setFont(&updatePctStr, (leFont*)&figmaFont_Geist_Mono_12);

    leFixedString_Constructor(&drawPctStr, drawPctCharBuffer, METRICS_BUFFER_SIZE);
    drawPctStr.fn->setFont(&drawPctStr, (leFont*)&figmaFont_Geist_Mono_12);

    leFixedString_Constructor(&fpsStr, fpsCharBuffer, METRICS_BUFFER_SIZE);
    fpsStr.fn->setFont(&fpsStr, (leFont*)&figmaFont_Geist_Mono_12);

    lastMetricsUpdateTime = tickCountMS;
}

/*******************************************************************************
 * Metrics_Update
 * Updates the performance metrics labels every second.
 * Returns true if labels were updated, false otherwise.
 ******************************************************************************/
bool Metrics_Update(leLabelWidget* lblUpdatePct, leLabelWidget* lblDrawPct, leLabelWidget* lblFPSValue)
{
    uint32_t currentTime = tickCountMS;
    uint32_t elapsedMs = tickCountMS - lastMetricsUpdateTime;

    if (elapsedMs < METRICS_UPDATE_INTERVAL_MS)
    {
        return false;
    }

    lastMetricsUpdateTime = currentTime;

#if LE_USAGE_MONITOR_PERIOD_SECS
    const LegatoPerformanceMetrics_t* metrics = Legato_GetPerformanceMetrics();

    if (lblUpdatePct != NULL)
    {
        uint32_t whole = metrics->updateTimePct100 / 100;
        uint32_t frac = metrics->updateTimePct100 % 100;
        sprintf(updatePctCStrBuffer, "%lu.%02lu%%", (unsigned long)whole, (unsigned long)frac);
        updatePctStr.fn->setFromCStr(&updatePctStr, updatePctCStrBuffer);
        lblUpdatePct->fn->setString(lblUpdatePct, (leString*)&updatePctStr);
    }

    if (lblDrawPct != NULL)
    {
        uint32_t whole = metrics->renderTimePct100 / 100;
        uint32_t frac = metrics->renderTimePct100 % 100;
        sprintf(drawPctCStrBuffer, "%lu.%02lu%%", (unsigned long)whole, (unsigned long)frac);
        drawPctStr.fn->setFromCStr(&drawPctStr, drawPctCStrBuffer);
        lblDrawPct->fn->setString(lblDrawPct, (leString*)&drawPctStr);
    }

    if (lblFPSValue != NULL)
    {
        sprintf(fpsCStrBuffer, "%lu, %lu", (unsigned long) metrics->fps, (unsigned long)APP_GetAnimFps());
        fpsStr.fn->setFromCStr(&fpsStr, fpsCStrBuffer);
        lblFPSValue->fn->setString(lblFPSValue, (leString*)&fpsStr);
    }
#endif

    return true;
}
