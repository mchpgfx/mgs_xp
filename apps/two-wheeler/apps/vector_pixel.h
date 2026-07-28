/*******************************************************************************
  Vector Pixel Operations

  Company:
    Microchip Technology Inc.

  File Name:
    vector_pixel.h

  Summary:
    Color mode specific pixel draw and blend functions for vector rendering.

  Description:
    Provides pixel blending and span drawing functions that are optimized for
    specific color modes. The color mode is detected at runtime from the
    render buffer and the appropriate function pointers are set in the
    RenderContext. Supports RGB565 (16-bit) and RGBA8888 (32-bit) modes.
 *******************************************************************************/

#ifndef VECTOR_PIXEL_H
#define VECTOR_PIXEL_H

#include <stdint.h>
#include "gfx/legato/common/legato_common.h"
#include "gfx/legato/common/legato_rect.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Color Mode Enumeration
 ******************************************************************************/
typedef enum {
    RENDER_COLOR_MODE_RGB565,
    RENDER_COLOR_MODE_RGBA8888
} RenderColorMode;

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/
struct RenderContext;

/*******************************************************************************
 * Function Pointer Types
 ******************************************************************************/
typedef void (*PutPixelBlendFunc)(const struct RenderContext* ctx, int32_t x, int32_t y,
                                   uint32_t color, uint8_t alpha);
typedef void (*DrawHSpanFunc)(const struct RenderContext* ctx, int32_t y,
                               int32_t x0, int32_t x1,
                               uint32_t color, uint8_t alpha);
typedef void (*DrawHSpanAAFunc)(const struct RenderContext* ctx, int32_t y,
                                 int32_t x0, int32_t x1,
                                 int32_t aaLeft, int32_t aaRight,
                                 uint32_t color, uint8_t baseAlpha);

/*******************************************************************************
 * Render Functions Structure
 ******************************************************************************/
typedef struct {
    PutPixelBlendFunc putPixelBlend;
    DrawHSpanFunc drawHSpan;
    DrawHSpanAAFunc drawHSpanAA;
} RenderFuncs;

/*******************************************************************************
 * Render Context
 ******************************************************************************/
typedef struct RenderContext {
    void* fb;
    int32_t stride;
    int32_t offsetX;
    int32_t offsetY;
    leRect clip;
    RenderColorMode colorMode;
    const RenderFuncs* funcs;
} RenderContext;

/**
 * @brief Initialize the render context from the current Legato render buffer.
 * @param ctx Pointer to RenderContext to initialize.
 * @return LE_TRUE if successful, LE_FALSE if render buffer unavailable.
 */
leBool initRenderContext(RenderContext* ctx);

/*******************************************************************************
 * Pixel Drawing Functions (RGB565 versions)
 ******************************************************************************/
void putPixelBlend_RGB565(const RenderContext* ctx, int32_t x, int32_t y,
                          uint32_t color, uint8_t alpha);
void drawHSpan_RGB565(const RenderContext* ctx, int32_t y,
                      int32_t x0, int32_t x1,
                      uint32_t color, uint8_t alpha);
void drawHSpanAA_RGB565(const RenderContext* ctx, int32_t y,
                        int32_t x0, int32_t x1,
                        int32_t aaLeft, int32_t aaRight,
                        uint32_t color, uint8_t baseAlpha);

/*******************************************************************************
 * Pixel Drawing Functions (RGBA8888 versions)
 ******************************************************************************/
void putPixelBlend_RGBA8888(const RenderContext* ctx, int32_t x, int32_t y,
                            uint32_t color, uint8_t alpha);
void drawHSpan_RGBA8888(const RenderContext* ctx, int32_t y,
                        int32_t x0, int32_t x1,
                        uint32_t color, uint8_t alpha);
void drawHSpanAA_RGBA8888(const RenderContext* ctx, int32_t y,
                          int32_t x0, int32_t x1,
                          int32_t aaLeft, int32_t aaRight,
                          uint32_t color, uint8_t baseAlpha);

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_PIXEL_H */
