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

static bool label0_visible = false;

void event_Screen0_ButtonWidget_0_OnReleased(leButtonWidget* btn)
{
    (void)btn;

    if (label0_visible)
    {
        Screen0_LabelWidget_0->fn->setVisible(Screen0_LabelWidget_0, LE_FALSE);
        label0_visible = false;
    }
    else
    {
        Screen0_LabelWidget_0->fn->setVisible(Screen0_LabelWidget_0, LE_TRUE);
        label0_visible = true;
    }
}

void event_Screen0_ButtonWidget_Toggle_OnPressed(leButtonWidget* btn)
{
    (void)btn;
    Screen0_LabelWidget_1->fn->setString(Screen0_LabelWidget_1, (leString*)&string_toggleOn);
}

void event_Screen0_ButtonWidget_Toggle_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    Screen0_LabelWidget_1->fn->setString(Screen0_LabelWidget_1, (leString*)&string_toggleOff);
}
