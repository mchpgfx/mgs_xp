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
#include <stdbool.h>

#define VALUE_STR_SIZE_8 8

uint32_t sliderValue = 0;
bool sliderChanged = false;

/* String objects for showing new code */
static leFixedString sliderStr;
static leChar sliderStrBuff[VALUE_STR_SIZE_8] = {0};

void event_Screen0_ProgressBarWidget_0_ValueChanged(leProgressBarWidget* wgt, uint32_t val)
{
    /*Update the string value shown on the widget when the Progress Bar value changes*/
    char valueCStr[VALUE_STR_SIZE_8] = {0};
    
    snprintf(valueCStr, VALUE_STR_SIZE_8, "%u", sliderValue);
        
    sliderStr.fn->setFromCStr(&sliderStr, valueCStr);
    Screen0_LabelWidget_1->fn->setString(Screen0_LabelWidget_1, (leString *) &sliderStr);
}

void event_Screen0_SliderWidget_0_OnValueChanged(leSliderWidget* scr)
{
    /*Get the value of the slider*/
    sliderValue = Screen0_SliderWidget_0->fn->getValue(Screen0_SliderWidget_0);
    sliderChanged = true;
}

void Screen0_OnShow(void)
{
    /*Initialize string objects for label */
    leFixedString_Constructor(&sliderStr, sliderStrBuff, VALUE_STR_SIZE_8); //Set data store
    sliderStr.fn->setFont(&sliderStr, (leFont*) &Font0);  //Set Font
}
void Screen0_OnHide(void)
{
    
}
void Screen0_OnUpdate(void)
{
    /*Update the value of the Progress Bar Widget when the event of the Slider is entered*/
    if(sliderChanged == true)
    {
        Screen0_ProgressBarWidget_0->fn->setValue(Screen0_ProgressBarWidget_0, sliderValue);
        sliderChanged = false;
    }       
}
