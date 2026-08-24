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

#include <stdio.h>
#include <stdbool.h>

#include "gfx/legato/generated/le_gen_init.h"

#define CALENDAR_SHOW_Y     40
#define CALENDAR_HIDE_Y     480

#define DATE_STR_SIZE       12
#define YEAR_STR_SIZE       4
#define DAY_STR_SIZE        2

#define MONTH_DEFAULT MONTH_JAN
#define YEAR_DEFAULT 2025
#define DAY_DEFAULT 1

#define MAX_NUM_DAYS 31
#define YEAR_MIN    1930
#define YEAR_MAX    2100

#define MAX_CELL_ROWS 6
#define MAX_CELL_COLS 7

typedef enum
{
    MONTH_JAN = 1,
    MONTH_FEB,
    MONTH_MAR,
    MONTH_APR,
    MONTH_MAY,
    MONTH_JUN,
    MONTH_JUL,
    MONTH_AUG,
    MONTH_SEP,
    MONTH_OCT,
    MONTH_NOV,
    MONTH_DEC,
    NUM_MONTHS
} APP_MONTH_t;

typedef struct
{
    uint32_t numDays;
    leString * str;
} APP_MONTH_INFO_t;

static APP_MONTH_INFO_t monthInf[NUM_MONTHS] =
{
    [MONTH_JAN] = {31, (leString *) &string_strJan},
    [MONTH_FEB] = {28, (leString *) &string_strFeb},
    [MONTH_MAR] = {31, (leString *) &string_strMar},
    [MONTH_APR] = {30, (leString *) &string_strApr},
    [MONTH_MAY] = {31, (leString *) &string_strMay},
    [MONTH_JUN] = {30, (leString *) &string_strJun},
    [MONTH_JUL] = {31, (leString *) &string_strJul},
    [MONTH_AUG] = {31, (leString *) &string_strAug},
    [MONTH_SEP] = {30, (leString *) &string_strSept},
    [MONTH_OCT] = {31, (leString *) &string_strOct},
    [MONTH_NOV] = {30, (leString *) &string_strNov},
    [MONTH_DEC] = {31, (leString *) &string_strDec},
};

static leFixedString setDateFixedStr;
static leChar setDateStrBuff[DATE_STR_SIZE] = {0};

static leFixedString yearFixedStr;
static leChar yearStrBuff[YEAR_STR_SIZE] = {0};

static leFixedString daysFixedStr[MAX_NUM_DAYS];
static leChar daysStrBuff[MAX_NUM_DAYS][DAY_STR_SIZE] = {0};

static APP_MONTH_t month = MONTH_DEFAULT;
static uint32_t year = YEAR_DEFAULT;

static uint32_t dayofweek(uint32_t y, uint32_t m, uint32_t d)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    if (m < 3)
    {
        y -= 1;
    }

    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

static int32_t getDayByCell(uint32_t startDay, uint32_t cellRow, uint32_t cellCol)
{
    int32_t day = (cellRow * MAX_CELL_COLS) + cellCol + 1;

    day -= startDay;

    return day;
}

static void APP_CreateCalendar(uint32_t calYear, uint32_t calMonth)
{
    uint32_t cellRow = 0;
    uint32_t cellCol = 0;
    uint32_t maxDays;
    uint32_t startDay;

    startDay = dayofweek(calYear, calMonth, 1);

    if (calMonth == MONTH_FEB &&
        ((calYear % 4 == 0 && calYear % 100 != 0) || (calYear % 400 == 0)))
    {
        maxDays = 29;
    }
    else
    {
        maxDays = monthInf[calMonth].numDays;
    }

    for (cellRow = 0; cellRow < MAX_CELL_ROWS; cellRow++)
    {
        for (cellCol = 0; cellCol < MAX_CELL_COLS; cellCol++)
        {
            leButtonWidget * cell;
            char dayStr[DAY_STR_SIZE + 1] = {0};

            cell = Screen0_keyCalendar->fn->getCellButton(Screen0_keyCalendar, cellRow, cellCol);
            if (cell != NULL)
            {
                int32_t day = getDayByCell(startDay, cellRow, cellCol);
                if (day >= 1 && day <= (int32_t)maxDays)
                {
                    snprintf(dayStr, DAY_STR_SIZE + 1, "%u", (unsigned int)day);
                    daysFixedStr[day - 1].fn->setFromCStr(&daysFixedStr[day - 1], dayStr);
                    cell->fn->setString(cell, (leString *) &daysFixedStr[day - 1]);
                    cell->fn->setPressedImage(cell, &ButtonDown);
                    cell->fn->setReleasedImage(cell, &ButtonUp);

                    cell->fn->setEnabled(cell, LE_TRUE);
                }
                else
                {
                    cell->fn->setString(cell, (leString *) NULL);
                    cell->fn->setPressedImage(cell, NULL);
                    cell->fn->setReleasedImage(cell, NULL);

                    cell->fn->setEnabled(cell, LE_FALSE);
                }
            }
        }
    }
}

void event_Screen0_keyCalendar_OnKeyClick(leKeyPadWidget* wgt, leButtonWidget* cell, uint32_t row, uint32_t col)
{
    int32_t day;
    uint32_t startDay;
    char setDateStr[DATE_STR_SIZE + 1] = {0};
    uint32_t maxDays;

    (void)wgt;
    (void)cell;

    if (month == MONTH_FEB &&
        ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
    {
        maxDays = 29;
    }
    else
    {
        maxDays = monthInf[month].numDays;
    }

    startDay = dayofweek(year, month, 1);

    day = getDayByCell(startDay, row, col);
    if (day >= 1 && day <= (int32_t)maxDays)
    {
        snprintf(setDateStr, DATE_STR_SIZE + 1, "%d/%d/%d", month, day, (int)year);
        setDateFixedStr.fn->setFromCStr(&setDateFixedStr, setDateStr);

        Screen0_btnSetDate->fn->setString(Screen0_btnSetDate, (leString *) &setDateFixedStr);

        Screen0_pnlCalendarDialog->fn->setY(Screen0_pnlCalendarDialog, 480);
    }
}

void event_Screen0_btnPrevYear_OnReleased(leButtonWidget* btn)
{
    char yearStr[YEAR_STR_SIZE + 1] = {0};

    (void)btn;

    if (year > YEAR_MIN)
        year--;

    snprintf(yearStr, YEAR_STR_SIZE + 1, "%u", (unsigned int)year);
    yearFixedStr.fn->setFromCStr(&yearFixedStr, yearStr);
    Screen0_lblYear->fn->setString(Screen0_lblYear, (leString *) &yearFixedStr);

    APP_CreateCalendar(year, month);
}

void event_Screen0_btnPrevMonth_OnReleased(leButtonWidget* btn)
{
    (void)btn;

    if (month > MONTH_JAN)
        month--;

    Screen0_lblMonth->fn->setString(Screen0_lblMonth, monthInf[month].str);

    APP_CreateCalendar(year, month);
}

void event_Screen0_btnNextYear_OnReleased(leButtonWidget* btn)
{
    char yearStr[YEAR_STR_SIZE + 1] = {0};

    (void)btn;

    if (year < YEAR_MAX)
        year++;

    snprintf(yearStr, YEAR_STR_SIZE + 1, "%u", (unsigned int)year);
    yearFixedStr.fn->setFromCStr(&yearFixedStr, yearStr);

    Screen0_lblYear->fn->setString(Screen0_lblYear, (leString *) &yearFixedStr);

    APP_CreateCalendar(year, month);
}

void event_Screen0_btnNextMonth_OnReleased(leButtonWidget* btn)
{
    (void)btn;

    if (month < MONTH_DEC)
        month++;

    Screen0_lblMonth->fn->setString(Screen0_lblMonth, monthInf[month].str);

    APP_CreateCalendar(year, month);
}

void event_Screen0_btnSetDate_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    Screen0_pnlCalendarDialog->fn->setY(Screen0_pnlCalendarDialog, CALENDAR_SHOW_Y);
}

void event_Screen0_btnClose_OnReleased(leButtonWidget* btn)
{
    (void)btn;
    Screen0_pnlCalendarDialog->fn->setY(Screen0_pnlCalendarDialog, CALENDAR_HIDE_Y);
}

void Screen0_OnShow(void)
{
    uint32_t day;

    for (day = 0; day < MAX_NUM_DAYS; day++)
    {
        leFixedString_Constructor(&daysFixedStr[day], daysStrBuff[day], DAY_STR_SIZE);
        daysFixedStr[day].fn->setFont(&daysFixedStr[day], (leFont*) &NotoSansSmall);
    }

    leFixedString_Constructor(&yearFixedStr, yearStrBuff, YEAR_STR_SIZE);
    yearFixedStr.fn->setFont(&yearFixedStr, (leFont*) &NotoSansSmall);

    leFixedString_Constructor(&setDateFixedStr, setDateStrBuff, DATE_STR_SIZE);
    setDateFixedStr.fn->setFont(&setDateFixedStr, (leFont*) &NotoSansSmall);

    APP_CreateCalendar(year, month);
}

void Screen0_OnHide(void)
{
}

void Screen0_OnUpdate(void)
{
}
