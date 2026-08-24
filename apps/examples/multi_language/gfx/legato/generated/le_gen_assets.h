/*******************************************************************************
 Module for Microchip Legato Graphics Library

  Company:
    Microchip Technology Inc.

  File Name:
    le_gen_assets.h

  Summary:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.


  Description:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.

*******************************************************************************/


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

#ifndef LE_GEN_ASSETS_H
#define LE_GEN_ASSETS_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

#include "gfx/legato/legato.h"

extern const lePalette leGlobalPalette;

/*****************************************************************************
 * Legato Graphics Image Assets
 *****************************************************************************/
/*********************************
 * Legato Image Asset
 * Name:   mchpLogo_small
 * Size:   120x28 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage mchpLogo_small;

/*********************************
 * Legato Image Asset
 * Name:   MHGS_logo_smaller
 * Size:   180x169 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage MHGS_logo_smaller;

/*********************************
 * Legato Image Asset
 * Name:   QuickstartDown_WQVGA
 * Size:   160x74 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage QuickstartDown_WQVGA;

/*********************************
 * Legato Image Asset
 * Name:   QuickstartUp_WQVGA
 * Size:   160x74 pixels
 * Type:   RGB Data
 * Format: RGB_565
 ***********************************/
extern leImage QuickstartUp_WQVGA;

/*****************************************************************************
 * Legato Graphics Font Assets
 *****************************************************************************/
/*********************************
 * Legato Font Asset
 * Name:         FontNotoCJKtc
 * Height:       23
 * Baseline:     28
 * Style:        Antialias
 * Glyph Count:  1006
 * Range Count:  25
 * Glyph Ranges: 0x20-0x3FF
                 0x3046
                 0x304A
                 0x306F
                 0x3088
                 0x4E0A
                 0x597D
                 0x65E9
                 0xC544
                 0xC5D0
                 0xC694
                 0xC740
                 0xC774
                 0xC88B
                 0xCE68
***********************************/
extern leRasterFont FontNotoCJKtc;

/*********************************
 * Legato Font Asset
 * Name:         FontNotoArabic
 * Height:       33
 * Baseline:     20
 * Style:        Antialias
 * Glyph Count:  104
 * Range Count:  9
 * Glyph Ranges: 0xA
                 0x20-0x7E
                 0x627-0x628
                 0x62D-0x62E
                 0x631
                 0x635
                 0x644
                 0x64A
***********************************/
extern leRasterFont FontNotoArabic;

/*********************************
 * Legato Font Asset
 * Name:         FontNotoEthiopic
 * Height:       21
 * Baseline:     20
 * Style:        Antialias
 * Glyph Count:  100
 * Range Count:  7
 * Glyph Ranges: 0x20-0x7E
                 0x120D
                 0x121D
                 0x12A5
                 0x12AB
                 0x12F5
***********************************/
extern leRasterFont FontNotoEthiopic;

/*********************************
 * Legato Font Asset
 * Name:         FontDevan
 * Height:       20
 * Baseline:     21
 * Style:        Antialias
 * Glyph Count:  103
 * Range Count:  10
 * Glyph Ranges: 0x20-0x7E
                 0x924
                 0x92A
                 0x92D
                 0x930
                 0x936
                 0x93E
                 0x941
                 0x94D
***********************************/
extern leRasterFont FontDevan;

/*********************************
 * Legato Font Asset
 * Name:         NotoRegular
 * Height:       21
 * Baseline:     21
 * Style:        Antialias
 * Glyph Count:  110
 * Range Count:  27
 * Glyph Ranges: 0x20-0x7E
                 0xF4
                 0x39A
                 0x3AD
                 0x3B1
                 0x3B7
                 0x3BB-0x3BC
                 0x3C1
                 0x414
                 0x431
                 0x435
                 0x43E
                 0x440
                 0x442-0x443
***********************************/
extern leRasterFont NotoRegular;

/*****************************************************************************
 * Legato String Table
 * Encoding        UTF8
 * Language Count: 14
 * String Count:   1
 *****************************************************************************/

// language IDs
#define language_Default    0
#define language_Arabic    1
#define language_Amharic    2
#define language_Swahili    3
#define language_Afrikaans    4
#define language_Zulu    5
#define language_Portoguese    6
#define language_Spanish    7
#define language_ChineseSimp    8
#define language_Korean    9
#define language_Japanse    10
#define language_Hindi    11
#define language_Russian    12
#define language_Greek    13

// string IDs
#define stringID_GoodMorn    0

extern const leStringTable stringTable;


// string list
extern leTableString string_GoodMorn;

void initializeStrings(void);
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* LE_GEN_ASSETS_H */
