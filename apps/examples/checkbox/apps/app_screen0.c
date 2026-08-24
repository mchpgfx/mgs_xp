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

static bool checkStateOrange = false;
static bool checkStateBanana = false;
static bool checkStateApple = false;

void event_Screen0_CheckBoxWidget_0_OnChecked(leCheckBoxWidget* btn)
{
    (void)btn;
    checkStateOrange = true;
    Screen0_ImageWidget_0->fn->setVisible(Screen0_ImageWidget_0, true);
    Screen0_CheckBoxWidget_1->fn->setChecked(Screen0_CheckBoxWidget_1, false);
    Screen0_CheckBoxWidget_2->fn->setChecked(Screen0_CheckBoxWidget_2, false);
    Screen0_ImageWidget_0->fn->setImage(Screen0_ImageWidget_0, &orange);
}

void event_Screen0_CheckBoxWidget_0_OnUnchecked(leCheckBoxWidget* btn)
{
    (void)btn;
    checkStateOrange = false;
    if (!checkStateOrange && !checkStateBanana && !checkStateApple)
    {
        Screen0_ImageWidget_0->fn->setVisible(Screen0_ImageWidget_0, false);
    }
}

void event_Screen0_CheckBoxWidget_1_OnChecked(leCheckBoxWidget* btn)
{
    (void)btn;
    checkStateBanana = true;
    Screen0_ImageWidget_0->fn->setVisible(Screen0_ImageWidget_0, true);
    Screen0_CheckBoxWidget_0->fn->setChecked(Screen0_CheckBoxWidget_0, false);
    Screen0_CheckBoxWidget_2->fn->setChecked(Screen0_CheckBoxWidget_2, false);
    Screen0_ImageWidget_0->fn->setImage(Screen0_ImageWidget_0, &banana);
}

void event_Screen0_CheckBoxWidget_1_OnUnchecked(leCheckBoxWidget* btn)
{
    (void)btn;
    checkStateBanana = false;
    if (!checkStateOrange && !checkStateBanana && !checkStateApple)
    {
        Screen0_ImageWidget_0->fn->setVisible(Screen0_ImageWidget_0, false);
    }
}

void event_Screen0_CheckBoxWidget_2_OnChecked(leCheckBoxWidget* btn)
{
    (void)btn;
    checkStateApple = true;
    Screen0_ImageWidget_0->fn->setVisible(Screen0_ImageWidget_0, true);
    Screen0_CheckBoxWidget_0->fn->setChecked(Screen0_CheckBoxWidget_0, false);
    Screen0_CheckBoxWidget_1->fn->setChecked(Screen0_CheckBoxWidget_1, false);
    Screen0_ImageWidget_0->fn->setImage(Screen0_ImageWidget_0, &apple);
}

void event_Screen0_CheckBoxWidget_2_OnUnchecked(leCheckBoxWidget* btn)
{
    (void)btn;
    checkStateApple = false;
    if (!checkStateOrange && !checkStateBanana && !checkStateApple)
    {
        Screen0_ImageWidget_0->fn->setVisible(Screen0_ImageWidget_0, false);
    }
}
