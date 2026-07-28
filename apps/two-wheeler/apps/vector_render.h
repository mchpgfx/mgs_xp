/*******************************************************************************
  Vector Render APIs

  Company:
    Microchip Technology Inc.

  File Name:
    vector_render.h

  Summary:
    Span-based vector drawing APIs for lines, rectangles, and arcs.

  Description:
    Provides optimized vector drawing functions that bypass the general-purpose
    Legato vector kernel. Uses span-based rendering with edge anti-aliasing
    calculated via coverage values for maximum performance.

    The color mode is selected at compile time via VECTOR_COLOR_MODE_RGB565.
    When undefined (default), RGBA8888 mode is used.

  Compile-Time Options:
    VECTOR_COLOR_MODE_RGB565 - Define to use RGB565 mode (16-bit color)
                               Leave undefined for RGBA8888 mode (32-bit color)

    USE_OPTIMIZED_LINE_DRAWING - Define to use scanline-based line algorithm
                                 Undefine for brute-force bounding box algorithm
 *******************************************************************************/

#ifndef VECTOR_RENDER_H
#define VECTOR_RENDER_H

#include <stdint.h>
#include "gfx/legato/vector/legato_vector.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Line Drawing Implementation Selection
 *
 * Define USE_OPTIMIZED_LINE_DRAWING to use the scanline-based algorithm with
 * 16.16 fixed-point math. This version computes X spans analytically per
 * scanline and only calculates distance once per pixel.
 *
 * Undefine to use the original brute-force bounding box algorithm.
 ******************************************************************************/
#define USE_OPTIMIZED_LINE_DRAWING

/*******************************************************************************
 * Core Drawing Functions
 ******************************************************************************/

/**
 * @brief Draw an anti-aliased line.
 *
 * Renders a line between two points with configurable width. Uses span-based
 * rendering with edge anti-aliasing for smooth appearance. Horizontal and
 * vertical lines are handled with optimized fast paths.
 *
 * @param p0        Pointer to the start point (fixed-point leVector2).
 * @param p1        Pointer to the end point (fixed-point leVector2).
 * @param color     32-bit RGBA8888 color value (0xAARRGGBB format).
 *                  Converted to RGB565 internally if VECTOR_COLOR_MODE_RGB565 is defined.
 * @param alpha     Global alpha value (0-255) for transparency blending.
 * @param width     Line width in pixels.
 */
void leDraw_VectorBasicLine(const struct leVector2* p0,
                            const struct leVector2* p1,
                            uint32_t color,
                            uint8_t alpha,
                            int32_t width);

/**
 * @brief Draw a filled rectangle with optional rounded corners.
 *
 * Renders a filled rectangle using span-based rendering. Supports rounded
 * corners with per-corner radius and applies edge anti-aliasing for smooth
 * appearance at boundaries.
 *
 * @param rect          Pointer to the rectangle definition (origin and extents).
 * @param color         32-bit RGBA8888 color value (0xAARRGGBB format).
 * @param alpha         Global alpha value (0-255) for transparency blending.
 * @param cornerRadius  Corner radius in pixels. Set to 0 for sharp corners.
 *                      Automatically clamped to half the rectangle dimension.
 */
void leDraw_VectorBasicRectFill(const struct leRectF* rect,
                                uint32_t color,
                                uint8_t alpha,
                                int32_t cornerRadius);

/**
 * @brief Draw a stroked (outline) rectangle with optional rounded corners.
 *
 * Renders a rectangle outline using span-based rendering. The stroke is
 * centered on the rectangle boundary. Supports rounded corners with
 * configurable stroke width.
 *
 * @param rect          Pointer to the rectangle definition (origin and extents).
 * @param color         32-bit RGBA8888 color value (0xAARRGGBB format).
 * @param alpha         Global alpha value (0-255) for transparency blending.
 * @param strokeWidth   Width of the stroke in pixels (minimum 1).
 * @param cornerRadius  Corner radius in pixels. Set to 0 for sharp corners.
 *                      Automatically clamped to half the rectangle dimension.
 */
void leDraw_VectorBasicRectStroke(const struct leRectF* rect,
                                  uint32_t color,
                                  uint8_t alpha,
                                  int32_t strokeWidth,
                                  int32_t cornerRadius);

/**
 * @brief Draw an anti-aliased arc stroke (ring segment).
 *
 * Renders an arc outline with configurable stroke width. The arc is defined
 * by a center point, radius, start angle, and angular span. Anti-aliasing
 * is applied to both inner and outer edges.
 *
 * @param center        Pointer to the arc center point (fixed-point leVector2).
 * @param radius        Arc radius in fixed-point format (leReal_i16).
 * @param startAngle16  Start angle in 1/16th degree units (e.g., 90*16 = 90 degrees).
 *                      0 degrees points right, angles increase counter-clockwise.
 * @param spanAngle16   Angular span in 1/16th degree units. Positive for CCW,
 *                      negative for CW direction. Use 360*16 for full circle.
 * @param color         32-bit RGBA8888 color value (0xAARRGGBB format).
 * @param alpha         Global alpha value (0-255) for transparency blending.
 * @param strokeWidth   Width of the arc stroke in pixels (minimum 1).
 * @param capStyle      Cap style for arc endpoints (LE_CAPSTYLE_NONE, LE_CAPSTYLE_SQUARE,
 *                      or LE_CAPSTYLE_ROUND). Round caps draw circles at arc endpoints.
 */
void leDraw_VectorBasicArcStroke(const struct leVector2* center,
                                 int32_t radius,
                                 int32_t startAngle16,
                                 int32_t spanAngle16,
                                 uint32_t color,
                                 uint8_t alpha,
                                 int32_t strokeWidth,
                                 enum leCapStyle capStyle);

/**
 * @brief Draw a filled arc (pie wedge or full circle).
 *
 * Renders a filled arc/pie segment from the center point outward. The arc
 * is defined by a center point, radius, start angle, and angular span.
 * Edge anti-aliasing is applied to the outer circular boundary.
 *
 * @param center        Pointer to the arc center point (fixed-point leVector2).
 * @param radius        Arc radius in fixed-point format (leReal_i16).
 * @param startAngle16  Start angle in 1/16th degree units (e.g., 90*16 = 90 degrees).
 *                      0 degrees points right, angles increase counter-clockwise.
 * @param spanAngle16   Angular span in 1/16th degree units. Positive for CCW,
 *                      negative for CW direction. Use 360*16 for full circle.
 * @param color         32-bit RGBA8888 color value (0xAARRGGBB format).
 * @param alpha         Global alpha value (0-255) for transparency blending.
 */
void leDraw_VectorBasicArcFill(const struct leVector2* center,
                               int32_t radius,
                               int32_t startAngle16,
                               int32_t spanAngle16,
                               uint32_t color,
                               uint8_t alpha);

/*******************************************************************************
 * API-Compatible Wrapper Functions
 *
 * These functions provide drop-in compatibility with the standard Legato
 * vector API (legato_vector.h). They extract relevant parameters from the
 * attribute structs and delegate to the optimized implementations.
 *
 * Ignored/unsupported parameters:
 *   - aaMode: Fixed internal anti-aliasing is always applied
 *   - hardness: Not supported, edges use coverage-based AA
 *   - rotation: Not supported for rectangles
 *   - capStyle: Not supported for lines (square caps used)
 *   - mask: Not supported for arc strokes
 ******************************************************************************/

/**
 * @brief API-compatible wrapper for leDraw_VectorBasicLine.
 */
void leDrawExt_VectorBasicLine(const struct leVector2* p0,
                               const struct leVector2* p1,
                               const struct leVectorLineAttr* attr);

/**
 * @brief API-compatible wrapper for leDraw_VectorBasicRectFill.
 */
void leDrawExt_VectorBasicRectFill(const struct leRectF* rect,
                                   const struct leVectorRect_FillAttr* attr);

/**
 * @brief API-compatible wrapper for leDraw_VectorBasicRectStroke.
 */
void leDrawExt_VectorBasicRectStroke(const struct leRectF* rect,
                                     const struct leVectorRect_StrokeAttr* attr);

/**
 * @brief API-compatible wrapper for leDraw_VectorBasicArcStroke.
 */
void leDrawExt_VectorBasicArcStroke(const struct leVector2* center,
                                    leReal_i16 radius,
                                    int32_t start,
                                    int32_t span,
                                    const struct leVectorArc_StrokeAttr* attr);

/**
 * @brief API-compatible wrapper for leDraw_VectorBasicArcFill.
 */
void leDrawExt_VectorBasicArcFill(const struct leVector2* center,
                                  leReal_i16 radius,
                                  int32_t start,
                                  int32_t span,
                                  const struct leVectorArc_FillAttr* attr);

/*******************************************************************************
 * Legacy RGBA8888-specific aliases (for backwards compatibility)
 ******************************************************************************/
#define leDraw_VectorLine_RGBA8888        leDraw_VectorBasicLine
#define leDraw_VectorRectFill_RGBA8888    leDraw_VectorBasicRectFill
#define leDraw_VectorRectStroke_RGBA8888  leDraw_VectorBasicRectStroke
#define leDraw_VectorArcStroke_RGBA8888   leDraw_VectorBasicArcStroke
#define leDraw_VectorArcFill_RGBA8888     leDraw_VectorBasicArcFill

#define leDrawExt_VectorLine_RGBA8888       leDrawExt_VectorBasicLine
#define leDrawExt_VectorRectFill_RGBA8888   leDrawExt_VectorBasicRectFill
#define leDrawExt_VectorRectStroke_RGBA8888 leDrawExt_VectorBasicRectStroke
#define leDrawExt_VectorArcStroke_RGBA8888  leDrawExt_VectorBasicArcStroke
#define leDrawExt_VectorArcFill_RGBA8888    leDrawExt_VectorBasicArcFill

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_RENDER_H */
