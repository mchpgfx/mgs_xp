/*******************************************************************************
  Vector Math Utilities

  Company:
    Microchip Technology Inc.

  File Name:
    vector_math.c

  Summary:
    Fixed-point math and trigonometric functions for vector rendering.

  Description:
    Provides 16.16 fixed-point arithmetic, square root, and atan2 lookup table
    implementations for efficient vector drawing calculations.
 *******************************************************************************/

#include "vector_math.h"

fix16_t fix16_sqrt64(int64_t x)
{
    if (x <= 0) return 0;

    uint64_t val = (uint64_t)x << FIX16_SHIFT;
    uint64_t root = 0;
    uint64_t bit = (uint64_t)1 << 62;

    while (bit > val) bit >>= 2;

    while (bit != 0)
    {
        if (val >= root + bit)
        {
            val -= root + bit;
            root = (root >> 1) + bit;
        }
        else
        {
            root >>= 1;
        }
        bit >>= 2;
    }

    return (fix16_t)root;
}

int32_t isqrt(int32_t val)
{
    if (val <= 0) return 0;
    if (val == 1) return 1;

    int32_t x = val;
    int32_t y = (x + 1) / 2;

    while (y < x)
    {
        x = y;
        y = (x + val / x) / 2;
    }

    return x;
}

int32_t atan2Deg256(int32_t y, int32_t x)
{
    if (x == 0 && y == 0)
        return 0;
    if (x == 0)
        return (y > 0) ? 90 : 270;
    if (y == 0)
        return (x > 0) ? 0 : 180;

    static const uint8_t atanTable[257] = {
         0,  0,  0,  1,  1,  1,  1,  2,  2,  2,  2,  2,  3,  3,  3,  3,
         4,  4,  4,  4,  4,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,
         7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9,  9, 10, 10, 10, 10,
        10, 11, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 14,
        14, 14, 14, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 17, 17, 17,
        17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20,
        21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 24,
        24, 24, 24, 24, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 27, 27,
        27, 27, 27, 27, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 30,
        30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
        32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 35,
        35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37,
        37, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 40,
        40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42,
        42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44,
        44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45
    };

    int32_t ax = (x < 0) ? -x : x;
    int32_t ay = (y < 0) ? -y : y;

    int32_t angle;
    if (ax >= ay)
    {
        int32_t ratio = (ay * 256) / ax;
        angle = atanTable[ratio];
    }
    else
    {
        int32_t ratio = (ax * 256) / ay;
        angle = 90 - atanTable[ratio];
    }

    if (x < 0 && y > 0)
        angle = 180 - angle;
    else if (x < 0 && y < 0)
        angle = 180 + angle;
    else if (x > 0 && y < 0)
        angle = 360 - angle;

    return angle;
}

int32_t pointToSegmentDistSq256(int32_t px, int32_t py,
                                 int32_t x0, int32_t y0,
                                 int32_t x1, int32_t y1,
                                 int64_t lenSq)
{
    if (lenSq == 0)
    {
        int64_t ddx = px - x0;
        int64_t ddy = py - y0;
        return (int32_t)((ddx * ddx + ddy * ddy) * 256);
    }

    int64_t t = ((int64_t)(px - x0) * (x1 - x0) + (int64_t)(py - y0) * (y1 - y0));

    if (t < 0)
    {
        int64_t ddx = px - x0;
        int64_t ddy = py - y0;
        return (int32_t)((ddx * ddx + ddy * ddy) * 256 / 1);
    }
    else if (t > lenSq)
    {
        int64_t ddx = px - x1;
        int64_t ddy = py - y1;
        return (int32_t)((ddx * ddx + ddy * ddy) * 256 / 1);
    }
    else
    {
        int64_t cross = (int64_t)(py - y0) * (x1 - x0) - (int64_t)(px - x0) * (y1 - y0);
        return (int32_t)((cross * cross * 256) / lenSq);
    }
}
