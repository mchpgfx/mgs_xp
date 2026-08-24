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

void event_Screen0_ButtonWidget_0_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    Screen0_ImageSequenceWidget_0_0->fn->showNextImage(Screen0_ImageSequenceWidget_0_0);
    Screen0_ImageSequenceWidget_0_1->fn->showNextImage(Screen0_ImageSequenceWidget_0_1);
    Screen0_ImageSequenceWidget_0_2->fn->showNextImage(Screen0_ImageSequenceWidget_0_2);
}

void event_Screen0_ButtonWidget_0_0_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    Screen0_ImageSequenceWidget_0_0->fn->showPreviousImage(Screen0_ImageSequenceWidget_0_0);
    Screen0_ImageSequenceWidget_0_1->fn->showPreviousImage(Screen0_ImageSequenceWidget_0_1);
    Screen0_ImageSequenceWidget_0_2->fn->showPreviousImage(Screen0_ImageSequenceWidget_0_2);
}

void event_Screen0_ButtonWidget_0_1_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    Screen0_ImageSequenceWidget_1_0->fn->play(Screen0_ImageSequenceWidget_1_0);
    Screen0_ImageSequenceWidget_1_1->fn->play(Screen0_ImageSequenceWidget_1_1);
    Screen0_ImageSequenceWidget_1_2->fn->play(Screen0_ImageSequenceWidget_1_2);
}

void event_Screen0_ButtonWidget_0_1_0_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    Screen0_ImageSequenceWidget_1_0->fn->stop(Screen0_ImageSequenceWidget_1_0);
    Screen0_ImageSequenceWidget_1_1->fn->stop(Screen0_ImageSequenceWidget_1_1);
    Screen0_ImageSequenceWidget_1_2->fn->stop(Screen0_ImageSequenceWidget_1_2);
}

void event_Screen0_ImageSequenceWidget_0_0_OnImageChanged(leImageSequenceWidget* wgt)
{
    (void)wgt;
    int32_t currentImage = Screen0_ImageSequenceWidget_0_0->activeIdx;

    switch (currentImage)
    {
        case 0:
            Screen0_LabelWidget_1->fn->setString(Screen0_LabelWidget_1, (leString*)&string_Battery0);
            break;
        case 1:
            Screen0_LabelWidget_1->fn->setString(Screen0_LabelWidget_1, (leString*)&string_Battery1);
            break;
        case 2:
            Screen0_LabelWidget_1->fn->setString(Screen0_LabelWidget_1, (leString*)&string_Battery2);
            break;
        case 3:
            Screen0_LabelWidget_1->fn->setString(Screen0_LabelWidget_1, (leString*)&string_Battery3);
            break;
        case 4:
            Screen0_LabelWidget_1->fn->setString(Screen0_LabelWidget_1, (leString*)&string_Battery4);
            break;
        default:
            break;
    }
}

void Screen0_OnShow(void)
{

}

void Screen0_OnHide(void)
{
    
}
