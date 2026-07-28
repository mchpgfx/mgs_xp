/*******************************************************************************
  Vector Math Utilities

  Company:
    Microchip Technology Inc.

  File Name:
    vector_math.h

  Summary:
    Fixed-point math and trigonometric functions for vector rendering.

  Description:
    Provides 16.16 fixed-point arithmetic, square root, and atan2 lookup table
    implementations for efficient vector drawing calculations.
 *******************************************************************************/

#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * 16.16 Fixed-Point Math
 ******************************************************************************/
typedef int32_t fix16_t;

#define FIX16_SHIFT         16
#define FIX16_SCALE         (1 << FIX16_SHIFT)
#define FIX16_ONE           (1 << FIX16_SHIFT)
#define FIX16_HALF          (1 << (FIX16_SHIFT - 1))
#define FIX16_FROM_INT(i)   ((fix16_t)((i) << FIX16_SHIFT))
#define FIX16_TO_INT(f)     ((f) >> FIX16_SHIFT)
#define FIX16_FLOOR(f)      ((f) >> FIX16_SHIFT)
#define FIX16_CEIL(f)       (-((-(f)) >> FIX16_SHIFT))
#define FIX16_FROM_FLOAT(f) ((fix16_t)((f) * FIX16_SCALE))
#define FIX16_MUL(a, b)     ((fix16_t)(((int64_t)(a) * (int64_t)(b)) >> FIX16_SHIFT))
#define FIX16_DIV(a, b)     ((fix16_t)(((int64_t)(a) << FIX16_SHIFT) / (b)))
#define FIX16_MUL64(a, b)   (((int64_t)(a) * (int64_t)(b)) >> FIX16_SHIFT)

/**
 * @brief Compute square root of a 64-bit fixed-point value.
 * @param x Input value in 16.16 fixed-point (passed as 64-bit for overflow safety).
 * @return Square root in 16.16 fixed-point format.
 */
fix16_t fix16_sqrt64(int64_t x);

/**
 * @brief Compute square root of a 32-bit fixed-point value.
 * @param x Input value in 16.16 fixed-point format.
 * @return Square root in 16.16 fixed-point format.
 */
static inline fix16_t fix16_sqrt(fix16_t x)
{
    return fix16_sqrt64((int64_t)x);
}

/**
 * @brief Compute absolute value of a fixed-point number.
 * @param x Input value in 16.16 fixed-point format.
 * @return Absolute value in 16.16 fixed-point format.
 */
static inline fix16_t fix16_abs(fix16_t x)
{
    return x < 0 ? -x : x;
}

/*******************************************************************************
 * Integer Math
 ******************************************************************************/

/**
 * @brief Integer square root using Newton's method.
 * @param val Input integer value.
 * @return Integer square root (floor).
 */
int32_t isqrt(int32_t val);

/**
 * @brief Compute angle in degrees using lookup table.
 *
 * Returns angle in range [0, 360) degrees.
 * 0 degrees points right (+X), angles increase counter-clockwise.
 *
 * @param y Y coordinate (negative Y is up in screen coordinates).
 * @param x X coordinate.
 * @return Angle in degrees (0-359).
 */
int32_t atan2Deg256(int32_t y, int32_t x);

/**
 * @brief Compute squared distance from a point to a line segment (scaled by 256).
 *
 * Used for line rendering with brute-force bounding box algorithm.
 *
 * @param px    Point X coordinate.
 * @param py    Point Y coordinate.
 * @param x0    Segment start X.
 * @param y0    Segment start Y.
 * @param x1    Segment end X.
 * @param y1    Segment end Y.
 * @param lenSq Squared length of the segment.
 * @return Squared distance scaled by 256.
 */
int32_t pointToSegmentDistSq256(int32_t px, int32_t py,
                                 int32_t x0, int32_t y0,
                                 int32_t x1, int32_t y1,
                                 int64_t lenSq);

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_MATH_H */
