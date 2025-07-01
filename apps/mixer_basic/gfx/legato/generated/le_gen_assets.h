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
 * Name:   Button2Down
 * Size:   144x56 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage Button2Down;

/*********************************
 * Legato Image Asset
 * Name:   Button2Up
 * Size:   144x56 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage Button2Up;

/*********************************
 * Legato Image Asset
 * Name:   Button3Down
 * Size:   194x56 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage Button3Down;

/*********************************
 * Legato Image Asset
 * Name:   Button3Up
 * Size:   194x56 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage Button3Up;

/*********************************
 * Legato Image Asset
 * Name:   RLSliderKnob
 * Size:   10x10 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage RLSliderKnob;

/*********************************
 * Legato Image Asset
 * Name:   SliderKnob
 * Size:   20x40 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage SliderKnob;

/*********************************
 * Legato Image Asset
 * Name:   Small2ButtonDown
 * Size:   31x27 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage Small2ButtonDown;

/*********************************
 * Legato Image Asset
 * Name:   Small2ButtonUp
 * Size:   31x27 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage Small2ButtonUp;

/*********************************
 * Legato Image Asset
 * Name:   SmallButtonDown
 * Size:   68x27 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage SmallButtonDown;

/*********************************
 * Legato Image Asset
 * Name:   SmallButtonUp
 * Size:   68x27 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage SmallButtonUp;

/*********************************
 * Legato Image Asset
 * Name:   Button1Down
 * Size:   95x56 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage Button1Down;

/*********************************
 * Legato Image Asset
 * Name:   Button1Up
 * Size:   96x56 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage Button1Up;

/*********************************
 * Legato Image Asset
 * Name:   graphic_eq
 * Size:   11x12 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage graphic_eq;

/*********************************
 * Legato Image Asset
 * Name:   ButtonsAccs
 * Size:   109x26 pixels
 * Type:   RGB Data
 * Format: RGBA_8888
 ***********************************/
extern leImage ButtonsAccs;

/*****************************************************************************
 * Legato Graphics Font Assets
 *****************************************************************************/
/*********************************
 * Legato Font Asset
 * Name:         FontSmall
 * Height:       23
 * Baseline:     12
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  13
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont FontSmall;

/*********************************
 * Legato Font Asset
 * Name:         FontMed
 * Height:       23
 * Baseline:     15
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  12
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont FontMed;

/*********************************
 * Legato Font Asset
 * Name:         FontLarge
 * Height:       23
 * Baseline:     18
 * Style:        Antialias
 * Glyph Count:  95
 * Range Count:  5
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont FontLarge;

/*****************************************************************************
 * Legato String Table
 * Encoding        ASCII
 * Language Count: 1
 * String Count:   31
 *****************************************************************************/

// language IDs
#define language_English    0

// string IDs
#define stringID_StringEth    0
#define stringID_StringMain    1
#define stringID_Stringn5    2
#define stringID_StringOutput    3
#define stringID_StringI2S    4
#define stringID_Stringn20    5
#define stringID_Stringn25    6
#define stringID_Stringn15    7
#define stringID_StringUSB    8
#define stringID_String5    9
#define stringID_StringStop    10
#define stringID_StringL    11
#define stringID_StringHost    12
#define stringID_StringM    13
#define stringID_StringMTX1    14
#define stringID_String0    15
#define stringID_StringReset    16
#define stringID_StringS    17
#define stringID_Stringn10    18
#define stringID_StringSax    19
#define stringID_StringPCM    20
#define stringID_StringCh4    21
#define stringID_StringLead    22
#define stringID_StringCh1    23
#define stringID_StringMute    24
#define stringID_StringRun    25
#define stringID_String10    26
#define stringID_StringCh2    27
#define stringID_StringR    28
#define stringID_StringCue    29
#define stringID_StringCh3    30

extern const leStringTable stringTable;


// string list
extern leTableString string_StringEth;
extern leTableString string_StringMain;
extern leTableString string_Stringn5;
extern leTableString string_StringOutput;
extern leTableString string_StringI2S;
extern leTableString string_Stringn20;
extern leTableString string_Stringn25;
extern leTableString string_Stringn15;
extern leTableString string_StringUSB;
extern leTableString string_String5;
extern leTableString string_StringStop;
extern leTableString string_StringL;
extern leTableString string_StringHost;
extern leTableString string_StringM;
extern leTableString string_StringMTX1;
extern leTableString string_String0;
extern leTableString string_StringReset;
extern leTableString string_StringS;
extern leTableString string_Stringn10;
extern leTableString string_StringSax;
extern leTableString string_StringPCM;
extern leTableString string_StringCh4;
extern leTableString string_StringLead;
extern leTableString string_StringCh1;
extern leTableString string_StringMute;
extern leTableString string_StringRun;
extern leTableString string_String10;
extern leTableString string_StringCh2;
extern leTableString string_StringR;
extern leTableString string_StringCue;
extern leTableString string_StringCh3;

void initializeStrings(void);
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* LE_GEN_ASSETS_H */
