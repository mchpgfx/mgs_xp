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

static int32_t rotationAngle = 0;

void event_Screen0_ButtonWidget_0_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    rotationAngle += 45;
    if (rotationAngle >= 360)
    {
        rotationAngle = 0;
    }

    int32_t x1 = 0, y1 = 50, x2 = 100, y2 = 50;

    switch (rotationAngle)
    {
        case 0:   x1 = 0;   y1 = 50;  x2 = 100; y2 = 50;  break;
        case 45:  x1 = 0;   y1 = 0;   x2 = 100; y2 = 100; break;
        case 90:  x1 = 50;  y1 = 0;   x2 = 50;  y2 = 100; break;
        case 135: x1 = 100; y1 = 0;   x2 = 0;   y2 = 100; break;
        case 180: x1 = 100; y1 = 50;  x2 = 0;   y2 = 50;  break;
        case 225: x1 = 100; y1 = 100; x2 = 0;   y2 = 0;   break;
        case 270: x1 = 50;  y1 = 100; x2 = 50;  y2 = 0;   break;
        case 315: x1 = 0;   y1 = 100; x2 = 100; y2 = 0;   break;
        default: break;
    }

    Screen0_LineWidget_0->fn->setStartPoint(Screen0_LineWidget_0, x1, y1);
    Screen0_LineWidget_0->fn->setEndPoint(Screen0_LineWidget_0, x2, y2);
}
