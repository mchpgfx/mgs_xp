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

#include <stdio.h>
#include "gfx/legato/generated/le_gen_init.h"

#define APP_FIXED_STR_SIZE 3
#define MAX_COUNTER_STR_SIZE 15

typedef enum
{
    APP_TIMER_RUN,
    APP_TIMER_RUNNING,
    APP_TIMER_STOP,
    APP_TIMER_STOPPED,
} APP_TIMER_STATUS;

static APP_TIMER_STATUS appTimerStatus = APP_TIMER_STOPPED;
static uint32_t appTickCounter = 0;

static leFixedString appFixedStrStatic;
static leChar appFixedStrStatBuff[APP_FIXED_STR_SIZE] = {0};

static leDynamicString *appDynamicString;

static char cStrBuff[MAX_COUNTER_STR_SIZE];

void Screen0_OnShow(void)
{
    leFixedString_Constructor(&appFixedStrStatic, appFixedStrStatBuff, APP_FIXED_STR_SIZE);
    appFixedStrStatic.fn->setFont(&appFixedStrStatic, (leFont*)&FontBigStatic);

    appDynamicString = leDynamicString_New();
    appDynamicString->fn->setFont(appDynamicString, (leFont*)&FontBigDynamic);
}

void Screen0_OnHide(void)
{
    leString_Delete((leString*)appDynamicString);
}

void Screen0_OnUpdate(void)
{
    static uint32_t lastTickCount = 0;
    static uint32_t counterValue = 0;
    static uint32_t frameCount = 0;

    if (appTimerStatus == APP_TIMER_RUNNING)
    {
        frameCount++;
        if (frameCount >= 10)
        {
            appTickCounter++;
            frameCount = 0;
        }
    }

    if (lastTickCount != appTickCounter)
    {
        printf("value %lu \r\n", (unsigned long)counterValue);

        snprintf(cStrBuff, MAX_COUNTER_STR_SIZE, "%lu", (unsigned long)counterValue++);

        appFixedStrStatic.fn->setFromCStr(&appFixedStrStatic, cStrBuff);
        Screen0_LabelWidget_Fixed_Stat->fn->setString(
            Screen0_LabelWidget_Fixed_Stat,
            (leString*)&appFixedStrStatic);

        appDynamicString->fn->setFromCStr(appDynamicString, cStrBuff);
        Screen0_LabelWidget_Dyn->fn->setString(Screen0_LabelWidget_Dyn,
                                               (leString*)appDynamicString);

        lastTickCount = appTickCounter;
    }
}

void event_Screen0_ButtonWidget_StartStop_OnPressed(leButtonWidget* btn)
{
    (void)btn;

    if (appTimerStatus == APP_TIMER_STOPPED)
    {
        appTimerStatus = APP_TIMER_RUNNING;
        Screen0_ButtonWidget_StartStop->fn->setString(Screen0_ButtonWidget_StartStop, (leString*)&string_StringStop);
    }
}

void event_Screen0_ButtonWidget_StartStop_OnReleased(leButtonWidget* btn)
{
    (void)btn;

    if (appTimerStatus == APP_TIMER_RUNNING)
    {
        appTimerStatus = APP_TIMER_STOPPED;
        Screen0_ButtonWidget_StartStop->fn->setString(Screen0_ButtonWidget_StartStop, (leString*)&string_StringRun);
    }
}

void event_Screen0_ButtonWidget_English_OnPressed(leButtonWidget* btn)
{
    (void)btn;
    leSetStringLanguage(language_English);
}

void event_Screen0_ButtonWidget_Spanish_OnPressed(leButtonWidget* btn)
{
    (void)btn;
    leSetStringLanguage(language_Spanish);
}

void event_Screen0_ButtonWidget_Chinese_OnPressed(leButtonWidget* btn)
{
    (void)btn;
    leSetStringLanguage(language_Chinese);
}
