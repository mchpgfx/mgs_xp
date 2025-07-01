/*******************************************************************************
  Application Header

  File Name:
    app_macros.h

  Summary:
    Helper macros for libary and widget APIs

  Description:
    Helper macros for libary and widget APIs
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/
//DOM-IGNORE-END

#ifndef _APP_MACROS_H    /* Guard against multiple inclusion */
#define _APP_MACROS_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#define APP_LE_ENABLE_TOUCH(widget, enable) widget->flags = (enable == LE_TRUE) ? (widget->flags | LE_WIDGET_ENABLED) : (widget->flags & ~LE_WIDGET_ENABLED)
#define APP_LE_SETVISIBLE(widget, visible) widget->fn->setVisible(widget, visible)
#define APP_LE_GETX(widget) widget->fn->getX(widget)
#define APP_LE_GETY(widget) widget->fn->getY(widget)
#define APP_LE_SETX(widget, xpos) widget->fn->setX(widget, xpos)
#define APP_LE_SETPOS(widget, xpos, ypos) widget->fn->setPosition(widget, xpos, ypos)
#define APP_LE_SETY(widget, ypos) widget->fn->setY(widget, ypos)
#define APP_LE_SETWIDTH(widget, width) widget->fn->setWidth(widget, width)
#define APP_LE_SETEVENTFILTER(widget, filter) widget->fn->installEventFilter(widget, filter)
#define APP_LE_SHOWIMAGE_IDX(imageSequenceWidget, idx) imageSequenceWidget->fn->showImage(imageSequenceWidget, idx)
#define APP_LE_SHOWIMAGE_NEXT(imageSequenceWidget) imageSequenceWidget->fn->showNextImage(imageSequenceWidget)
#define APP_LE_SETLABELSTRING(labelWidget, string) labelWidget->fn->setString(labelWidget, (leString*)&string);
#define APP_LE_INVALIDATE(widget) widget->fn->invalidate(widget)
#define APP_LE_SETSCHEME(widget, scheme) widget->fn->setScheme(widget, scheme)
#define APP_LE_SETBUTTONIMAGE(widget, image) { widget->fn->setPressedImage(widget, (leImage*)image); \
                                              widget->fn->setReleasedImage(widget, (leImage*)image); }
#define APP_LE_SETSTRING(widget, string) widget->fn->setString(widget, (leString*)string);    
    
#define APP_LE_SETBUTTONPRESSED(widget, pressed) widget->fn->setPressed(widget, pressed);
#define APP_LE_SETLABELDYNSTRING(labelWidget, lStr, cStr) {lStr.fn->setFromCStr(&lStr, cStr); \
                                                           labelWidget->fn->setString(labelWidget, (leString*)&lStr); }
#define APP_LE_SETLABELDYNSTRINGFROMFLOAT(labelWidget, lStr, cStr, value) {sprintf(cStr, "%.2f", value); \
                                                                           lStr.fn->setFromCStr(&lStr, cStr); \
                                                                           labelWidget->fn->setString(labelWidget, (leString*)&lStr); }
#define APP_LE_SETLABELDYNSTRINGFROMINT(labelWidget, lStr, cStr, value) {sprintf(cStr, "%lu", value); \
                                                                           lStr.fn->setFromCStr(&lStr, cStr); \
                                                                           labelWidget->fn->setString(labelWidget, (leString*)&lStr); }

#ifndef SYS_CONSOLE_PRINT
#define SYS_CONSOLE_PRINT(fmt, ...)                 printf(fmt, ##__VA_ARGS__)
#endif
    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
