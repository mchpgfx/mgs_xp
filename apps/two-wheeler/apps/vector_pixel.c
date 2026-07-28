/*******************************************************************************
  Vector Pixel Operations

  Company:
    Microchip Technology Inc.

  File Name:
    vector_pixel.c

  Summary:
    Color mode specific pixel draw and blend functions for vector rendering.

  Description:
    Provides pixel blending and span drawing functions that are optimized for
    specific color modes. Runtime detection selects between RGBA8888 and RGB565.
 *******************************************************************************/

#include "vector_pixel.h"
#include "gfx/legato/renderer/legato_renderer.h"
#include "gfx/legato/common/legato_pixelbuffer.h"

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include "arm_neon.h"
#define USE_NEON 1
#else
#define USE_NEON 0
#endif

#define FAST_DIV255(x) (((x) * 257 + 256) >> 16)

/*******************************************************************************
 * RGB565 Helper Functions
 ******************************************************************************/
static inline uint16_t blendPixel_RGB565(uint16_t dst, uint16_t src, uint8_t alpha)
{
    if (alpha == 255)
        return src;
    if (alpha == 0)
        return dst;

    uint32_t dstR = (dst >> 11) & 0x1F;
    uint32_t dstG = (dst >> 5) & 0x3F;
    uint32_t dstB = dst & 0x1F;

    uint32_t srcR = (src >> 11) & 0x1F;
    uint32_t srcG = (src >> 5) & 0x3F;
    uint32_t srcB = src & 0x1F;

    uint32_t inv = 255 - alpha;
    uint32_t outR = FAST_DIV255(srcR * alpha + dstR * inv);
    uint32_t outG = FAST_DIV255(srcG * alpha + dstG * inv);
    uint32_t outB = FAST_DIV255(srcB * alpha + dstB * inv);

    return (uint16_t)((outR << 11) | (outG << 5) | outB);
}

#if USE_NEON
static inline void rgb565_blend_neon_8(uint16_t* dest, uint16_t src, uint8_t alpha)
{
    uint16x8_t vdst = vld1q_u16(dest);
    uint16x8_t vsrc = vdupq_n_u16(src);

    uint16x8_t dstR = vshrq_n_u16(vandq_u16(vdst, vdupq_n_u16(0xF800)), 11);
    uint16x8_t dstG = vshrq_n_u16(vandq_u16(vdst, vdupq_n_u16(0x07E0)), 5);
    uint16x8_t dstB = vandq_u16(vdst, vdupq_n_u16(0x001F));

    uint16x8_t srcR = vshrq_n_u16(vandq_u16(vsrc, vdupq_n_u16(0xF800)), 11);
    uint16x8_t srcG = vshrq_n_u16(vandq_u16(vsrc, vdupq_n_u16(0x07E0)), 5);
    uint16x8_t srcB = vandq_u16(vsrc, vdupq_n_u16(0x001F));

    uint16x8_t valpha = vdupq_n_u16(alpha);
    uint16x8_t vinvalpha = vdupq_n_u16(255 - alpha);

    uint16x8_t outR = vshrq_n_u16(vaddq_u16(vmulq_u16(srcR, valpha),
                                             vmulq_u16(dstR, vinvalpha)), 8);
    uint16x8_t outG = vshrq_n_u16(vaddq_u16(vmulq_u16(srcG, valpha),
                                             vmulq_u16(dstG, vinvalpha)), 8);
    uint16x8_t outB = vshrq_n_u16(vaddq_u16(vmulq_u16(srcB, valpha),
                                             vmulq_u16(dstB, vinvalpha)), 8);

    uint16x8_t result = vorrq_u16(vorrq_u16(vshlq_n_u16(outR, 11),
                                             vshlq_n_u16(outG, 5)), outB);
    vst1q_u16(dest, result);
}

static inline void rgb565_fill_neon_8(uint16_t* dest, uint16_t color)
{
    uint16x8_t vcolor = vdupq_n_u16(color);
    vst1q_u16(dest, vcolor);
}
#endif

static inline uint16_t colorToPixel_RGB565(uint32_t rgba)
{
    uint32_t r = (rgba >> 16) & 0xFF;
    uint32_t g = (rgba >> 8) & 0xFF;
    uint32_t b = rgba & 0xFF;
    return (uint16_t)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3));
}

/*******************************************************************************
 * RGBA8888 Helper Functions
 ******************************************************************************/
static inline uint8_t blendChannel(uint8_t dst, uint8_t src, uint8_t alpha)
{
    uint32_t inv = 255 - alpha;
    return (uint8_t)FAST_DIV255(src * alpha + dst * inv);
}

#if USE_NEON
static inline void rgba8888_blend_neon_4(uint32_t* dest, uint32_t src, uint8_t alpha)
{
    uint8x16_t vdst = vld1q_u8((uint8_t*)dest);
    uint8x16_t vsrc = vreinterpretq_u8_u32(vdupq_n_u32(src));

    uint8x16_t valpha = vdupq_n_u8(alpha);
    uint8x16_t vinvalpha = vdupq_n_u8(255 - alpha);

    uint16x8_t dst_lo = vmovl_u8(vget_low_u8(vdst));
    uint16x8_t dst_hi = vmovl_u8(vget_high_u8(vdst));
    uint16x8_t src_lo = vmovl_u8(vget_low_u8(vsrc));
    uint16x8_t src_hi = vmovl_u8(vget_high_u8(vsrc));

    uint16x8_t alpha_lo = vmovl_u8(vget_low_u8(valpha));
    uint16x8_t alpha_hi = vmovl_u8(vget_high_u8(valpha));
    uint16x8_t invalpha_lo = vmovl_u8(vget_low_u8(vinvalpha));
    uint16x8_t invalpha_hi = vmovl_u8(vget_high_u8(vinvalpha));

    uint16x8_t out_lo = vaddq_u16(vmulq_u16(src_lo, alpha_lo),
                                   vmulq_u16(dst_lo, invalpha_lo));
    uint16x8_t out_hi = vaddq_u16(vmulq_u16(src_hi, alpha_hi),
                                   vmulq_u16(dst_hi, invalpha_hi));

    uint8x8_t result_lo = vshrn_n_u16(out_lo, 8);
    uint8x8_t result_hi = vshrn_n_u16(out_hi, 8);

    uint8x16_t result = vcombine_u8(result_lo, result_hi);
    vst1q_u8((uint8_t*)dest, result);
}

static inline void rgba8888_fill_neon_4(uint32_t* dest, uint32_t color)
{
    uint32x4_t vcolor = vdupq_n_u32(color);
    vst1q_u32(dest, vcolor);
}
#endif

static inline uint32_t blendPixel_RGBA8888(uint32_t dst, uint32_t src, uint8_t alpha)
{
    if (alpha == 255)
        return src;
    if (alpha == 0)
        return dst;

    uint8_t dstR = (dst >> 24) & 0xFF;
    uint8_t dstG = (dst >> 16) & 0xFF;
    uint8_t dstB = (dst >> 8) & 0xFF;
    uint8_t dstA = dst & 0xFF;

    uint8_t srcR = (src >> 24) & 0xFF;
    uint8_t srcG = (src >> 16) & 0xFF;
    uint8_t srcB = (src >> 8) & 0xFF;
    uint8_t srcA = src & 0xFF;

    uint8_t outR = blendChannel(dstR, srcR, alpha);
    uint8_t outG = blendChannel(dstG, srcG, alpha);
    uint8_t outB = blendChannel(dstB, srcB, alpha);
    uint8_t outA = (srcA > dstA) ? srcA : dstA;

    return (outR << 24) | (outG << 16) | (outB << 8) | outA;
}

/*******************************************************************************
 * RGB565 Pixel Drawing Functions
 ******************************************************************************/
void putPixelBlend_RGB565(const RenderContext* ctx, int32_t x, int32_t y,
                          uint32_t color, uint8_t alpha)
{
    if (x < ctx->clip.x || x >= ctx->clip.x + ctx->clip.width ||
        y < ctx->clip.y || y >= ctx->clip.y + ctx->clip.height)
        return;

    int32_t bx = x - ctx->offsetX;
    int32_t by = y - ctx->offsetY;

    if (bx < 0 || by < 0 || bx >= ctx->stride)
        return;

    uint16_t* fb = (uint16_t*)ctx->fb;
    uint16_t* dst = fb + by * ctx->stride + bx;
    uint16_t pxColor = colorToPixel_RGB565(color);
    *dst = blendPixel_RGB565(*dst, pxColor, alpha);
}

void drawHSpan_RGB565(const RenderContext* ctx, int32_t y,
                      int32_t x0, int32_t x1,
                      uint32_t color, uint8_t alpha)
{
    if (y < ctx->clip.y || y >= ctx->clip.y + ctx->clip.height)
        return;

    if (x0 < ctx->clip.x) x0 = ctx->clip.x;
    if (x1 > ctx->clip.x + ctx->clip.width) x1 = ctx->clip.x + ctx->clip.width;
    if (x0 >= x1)
        return;

    int32_t by = y - ctx->offsetY;
    int32_t bx0 = x0 - ctx->offsetX;

    if (by < 0 || bx0 < 0)
        return;

    uint16_t* fb = (uint16_t*)ctx->fb;
    uint16_t* dst = fb + by * ctx->stride + bx0;
    int32_t count = x1 - x0;
    uint16_t pxColor = colorToPixel_RGB565(color);

    if (alpha == 255)
    {
#if USE_NEON
        while (count >= 8)
        {
            rgb565_fill_neon_8(dst, pxColor);
            dst += 8;
            count -= 8;
        }
#endif
        while (count-- > 0)
            *dst++ = pxColor;
    }
    else
    {
#if USE_NEON
        while (count >= 8)
        {
            rgb565_blend_neon_8(dst, pxColor, alpha);
            dst += 8;
            count -= 8;
        }
#endif
        while (count-- > 0)
        {
            *dst = blendPixel_RGB565(*dst, pxColor, alpha);
            dst++;
        }
    }
}

void drawHSpanAA_RGB565(const RenderContext* ctx, int32_t y,
                        int32_t x0, int32_t x1,
                        int32_t aaLeft, int32_t aaRight,
                        uint32_t color, uint8_t baseAlpha)
{
    if (y < ctx->clip.y || y >= ctx->clip.y + ctx->clip.height)
        return;

    int32_t clipX0 = ctx->clip.x;
    int32_t clipX1 = ctx->clip.x + ctx->clip.width;

    if (aaLeft > 0 && x0 >= clipX0 && x0 < clipX1)
    {
        uint8_t edgeAlpha = (uint8_t)(((uint32_t)baseAlpha * (256 - aaLeft)) >> 8);
        putPixelBlend_RGB565(ctx, x0, y, color, edgeAlpha);
        x0++;
    }

    int32_t solidX1 = x1;
    if (aaRight > 0 && x1 > clipX0 && x1 <= clipX1)
    {
        solidX1 = x1 - 1;
    }

    if (x0 < solidX1)
    {
        drawHSpan_RGB565(ctx, y, x0, solidX1, color, baseAlpha);
    }

    if (aaRight > 0 && x1 > clipX0 && x1 <= clipX1)
    {
        uint8_t edgeAlpha = (uint8_t)(((uint32_t)baseAlpha * (256 - aaRight)) >> 8);
        putPixelBlend_RGB565(ctx, x1 - 1, y, color, edgeAlpha);
    }
}

/*******************************************************************************
 * RGBA8888 Pixel Drawing Functions
 ******************************************************************************/
void putPixelBlend_RGBA8888(const RenderContext* ctx, int32_t x, int32_t y,
                            uint32_t color, uint8_t alpha)
{
    if (x < ctx->clip.x || x >= ctx->clip.x + ctx->clip.width ||
        y < ctx->clip.y || y >= ctx->clip.y + ctx->clip.height)
        return;

    int32_t bx = x - ctx->offsetX;
    int32_t by = y - ctx->offsetY;

    if (bx < 0 || by < 0 || bx >= ctx->stride)
        return;

    uint32_t* fb = (uint32_t*)ctx->fb;
    uint32_t* dst = fb + by * ctx->stride + bx;
    *dst = blendPixel_RGBA8888(*dst, color, alpha);
}

void drawHSpan_RGBA8888(const RenderContext* ctx, int32_t y,
                        int32_t x0, int32_t x1,
                        uint32_t color, uint8_t alpha)
{
    if (y < ctx->clip.y || y >= ctx->clip.y + ctx->clip.height)
        return;

    if (x0 < ctx->clip.x) x0 = ctx->clip.x;
    if (x1 > ctx->clip.x + ctx->clip.width) x1 = ctx->clip.x + ctx->clip.width;
    if (x0 >= x1)
        return;

    int32_t by = y - ctx->offsetY;
    int32_t bx0 = x0 - ctx->offsetX;

    if (by < 0 || bx0 < 0)
        return;

    uint32_t* fb = (uint32_t*)ctx->fb;
    uint32_t* dst = fb + by * ctx->stride + bx0;
    int32_t count = x1 - x0;

    if (alpha == 255)
    {
#if USE_NEON
        while (count >= 4)
        {
            rgba8888_fill_neon_4(dst, color);
            dst += 4;
            count -= 4;
        }
#endif
        while (count-- > 0)
            *dst++ = color;
    }
    else
    {
#if USE_NEON
        while (count >= 4)
        {
            rgba8888_blend_neon_4(dst, color, alpha);
            dst += 4;
            count -= 4;
        }
#endif
        while (count-- > 0)
        {
            *dst = blendPixel_RGBA8888(*dst, color, alpha);
            dst++;
        }
    }
}

void drawHSpanAA_RGBA8888(const RenderContext* ctx, int32_t y,
                          int32_t x0, int32_t x1,
                          int32_t aaLeft, int32_t aaRight,
                          uint32_t color, uint8_t baseAlpha)
{
    if (y < ctx->clip.y || y >= ctx->clip.y + ctx->clip.height)
        return;

    int32_t clipX0 = ctx->clip.x;
    int32_t clipX1 = ctx->clip.x + ctx->clip.width;

    if (aaLeft > 0 && x0 >= clipX0 && x0 < clipX1)
    {
        uint8_t edgeAlpha = (uint8_t)(((uint32_t)baseAlpha * (256 - aaLeft)) >> 8);
        putPixelBlend_RGBA8888(ctx, x0, y, color, edgeAlpha);
        x0++;
    }

    int32_t solidX1 = x1;
    if (aaRight > 0 && x1 > clipX0 && x1 <= clipX1)
    {
        solidX1 = x1 - 1;
    }

    if (x0 < solidX1)
    {
        drawHSpan_RGBA8888(ctx, y, x0, solidX1, color, baseAlpha);
    }

    if (aaRight > 0 && x1 > clipX0 && x1 <= clipX1)
    {
        uint8_t edgeAlpha = (uint8_t)(((uint32_t)baseAlpha * (256 - aaRight)) >> 8);
        putPixelBlend_RGBA8888(ctx, x1 - 1, y, color, edgeAlpha);
    }
}

/*******************************************************************************
 * Function Tables
 ******************************************************************************/
static const RenderFuncs renderFuncs_RGB565 = {
    .putPixelBlend = putPixelBlend_RGB565,
    .drawHSpan = drawHSpan_RGB565,
    .drawHSpanAA = drawHSpanAA_RGB565
};

static const RenderFuncs renderFuncs_RGBA8888 = {
    .putPixelBlend = putPixelBlend_RGBA8888,
    .drawHSpan = drawHSpan_RGBA8888,
    .drawHSpanAA = drawHSpanAA_RGBA8888
};

/*******************************************************************************
 * Render Context Initialization
 ******************************************************************************/
leBool initRenderContext(RenderContext* ctx)
{
    lePixelBuffer* renderBuf = leGetRenderBuffer();
    if (renderBuf == NULL || renderBuf->pixels == NULL)
        return LE_FALSE;

    leRect frame;
    leRenderer_GetFrameRect(&frame);
    leRenderer_GetClipRect(&ctx->clip);

    ctx->fb = renderBuf->pixels;
    ctx->stride = renderBuf->size.width;
    ctx->offsetX = frame.x;
    ctx->offsetY = frame.y;

    switch (renderBuf->mode)
    {
        case LE_COLOR_MODE_RGB_565:
            ctx->colorMode = RENDER_COLOR_MODE_RGB565;
            ctx->funcs = &renderFuncs_RGB565;
            break;
        case LE_COLOR_MODE_RGBA_8888:
        case LE_COLOR_MODE_ARGB_8888:
        default:
            ctx->colorMode = RENDER_COLOR_MODE_RGBA8888;
            ctx->funcs = &renderFuncs_RGBA8888;
            break;
    }

    return LE_TRUE;
}
