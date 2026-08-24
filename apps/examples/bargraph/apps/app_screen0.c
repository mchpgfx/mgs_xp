// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C)  Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#include "gfx/legato/generated/le_gen_init.h"
#include <stdbool.h>

static const int initialFruit[] = {54, 34, 95};
static const float averageWeightOz[] = {297.0f, 142.8f, 16.15f};
static bool convertionZero = false;
static bool convertionOne = false;

void event_Screen0_CheckBoxWidget_0_OnChecked(leCheckBoxWidget* btn)
{
    (void)btn;
    convertionZero = true;
    if (convertionOne)
    {
        Screen0_CheckBoxWidget_1->fn->setChecked(Screen0_CheckBoxWidget_1, LE_FALSE);
    }
    Screen0_BarGraphWidget_0->fn->setMaxValue(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 20);
    Screen0_BarGraphWidget_0->fn->setTickLength(Screen0_BarGraphWidget_0, 5);
    Screen0_BarGraphWidget_0->fn->setValueAxisTicksVisible(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, true);
    Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 0, (int32_t)(averageWeightOz[0] / 16));
    Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 1, (int32_t)(averageWeightOz[1] / 16));
    Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 2, (int32_t)(averageWeightOz[2] / 16));
}

void event_Screen0_CheckBoxWidget_0_OnUnchecked(leCheckBoxWidget* btn)
{
    (void)btn;
    convertionZero = false;
    if (!convertionZero && !convertionOne)
    {
        Screen0_BarGraphWidget_0->fn->setMaxValue(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 100);
        Screen0_BarGraphWidget_0->fn->setValueAxisTicksVisible(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, true);
        Screen0_BarGraphWidget_0->fn->setValueAxisTicksInterval(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 10);
        Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 0, initialFruit[0]);
        Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 1, initialFruit[1]);
        Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 2, initialFruit[2]);
    }
}

void event_Screen0_CheckBoxWidget_1_OnChecked(leCheckBoxWidget* btn)
{
    (void)btn;
    convertionOne = true;
    if (convertionZero)
    {
        Screen0_CheckBoxWidget_0->fn->setChecked(Screen0_CheckBoxWidget_0, LE_FALSE);
    }
    Screen0_BarGraphWidget_0->fn->setMaxValue(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 10);
    Screen0_BarGraphWidget_0->fn->setValueAxisTicksInterval(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 2);
    Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 0, (int32_t)(averageWeightOz[0] * 0.028));
    Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 1, (int32_t)(averageWeightOz[1] * 0.028));
    Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 2, (int32_t)(averageWeightOz[2] * 0.028));
}

void event_Screen0_CheckBoxWidget_1_OnUnchecked(leCheckBoxWidget* btn)
{
    (void)btn;
    convertionOne = false;
    if (!convertionZero && !convertionOne)
    {
        Screen0_BarGraphWidget_0->fn->setMaxValue(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 100);
        Screen0_BarGraphWidget_0->fn->setValueAxisTicksVisible(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, true);
        Screen0_BarGraphWidget_0->fn->setValueAxisTicksInterval(Screen0_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 10);
        Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 0, initialFruit[0]);
        Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 1, initialFruit[1]);
        Screen0_BarGraphWidget_0->fn->setDataInSeries(Screen0_BarGraphWidget_0, 0, 2, initialFruit[2]);
    }
}
