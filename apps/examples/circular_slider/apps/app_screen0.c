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

#define MAX_VAL_LEN     4

static char cSliderCharBuffer[16];
static leDynamicString p_SliderValstring;

//Legato Char buffer
static leChar p_SliderValBuff[MAX_VAL_LEN] = {0};

void Screen0_OnShow(void)
{
    leFixedString_Constructor(&p_SliderValstring,  p_SliderValBuff, MAX_VAL_LEN *2);
    p_SliderValstring.fn->setFont(&p_SliderValstring, (leFont*)& NotoSanB);
}

void event_Screen0_CircularSliderWidget_0_OnValueChanged(leCircularSliderWidget* sld, int32_t val)
{
    (void)sld;
    
    memset(cSliderCharBuffer, 0, sizeof(cSliderCharBuffer));
    sprintf(cSliderCharBuffer, "%ld", (long)val);
    p_SliderValstring.fn->setFromCStr(&p_SliderValstring, cSliderCharBuffer);
    Screen0_LabelSliderVal->fn->setString(Screen0_LabelSliderVal, (leString*)&p_SliderValstring);
}
