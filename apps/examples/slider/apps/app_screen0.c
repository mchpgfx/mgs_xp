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
#include <stdio.h>
#include <string.h>

char valueBuffer[32] = {0};

leFixedString sliderStr;                           //Legato string object
leChar tempBuffer[32] = {0};

void Screen0_OnShow(void)
{
    leFixedString_Constructor(&sliderStr, tempBuffer, 12);
    sliderStr.fn->setFont(&sliderStr, leStringTable_GetStringFont(leGetState()->stringTable,
                                                              stringID_Slider,
                                                              0));     
}

void event_Screen0_SliderWidget1_OnValueChanged(leSliderWidget* scr)
{
    Screen0_SliderWidget2->fn->setValue(Screen0_SliderWidget2, scr->fn->getValue(scr));
    sprintf(valueBuffer , "%ld", scr->fn->getValue(scr));
    sliderStr.fn->setFromCStr(&sliderStr, valueBuffer);
    Screen0_ValueLabel->fn->setString(Screen0_ValueLabel, (leString*)&sliderStr);
}
void event_Screen0_SliderWidget2_OnValueChanged(leSliderWidget* scr)
{
    Screen0_SliderWidget1->fn->setValue(Screen0_SliderWidget1, scr->fn->getValue(scr));
    sprintf(valueBuffer , "%ld", scr->fn->getValue(scr));
    sliderStr.fn->setFromCStr(&sliderStr, valueBuffer);
    Screen0_ValueLabel->fn->setString(Screen0_ValueLabel, (leString*)&sliderStr);
}
