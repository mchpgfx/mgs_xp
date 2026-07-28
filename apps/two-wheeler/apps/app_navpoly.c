#include "gfx/legato/generated/le_gen_assets.h"
#include "gfx/legato/generated/le_gen_init.h"
#include "gfx/legato/vector/legato_vector.h"
#include "gfx/legato/renderer/legato_renderer.h"
#include "app_sys_timer.h"

#include <math.h>
#include <stdio.h>

// NEON SIMD support for ARM Cortex-A7
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include "arm_neon.h"
#define USE_NEON 1
#else
#define USE_NEON 0
#endif

#define APP_TICK_FREQ_MS 40
#define WIDGET_WIDTH  360
#define WIDGET_HEIGHT 300
#define ADJACENT_SEGMENTS 5     // Number of segments to show before/after current
#define PI 3.14159265f
#define TWO_PI (2.0f * PI)
#define ROTATION_SMOOTHING 0.08f  // How fast rotation catches up (0-1, lower = smoother)
#define POSITION_MARKER_RADIUS 20

#define LINE_WIDTH 20
#define BOUNDS_PADDING (LINE_WIDTH / 2.0f + 2.0f)  // Extra padding for line thickness and rounding

#define PATH_COLOR_RGBA 0x1E293BFF //00D1FFFF
#define JOINT_COLOR_RGBA 0xA3FF00FF  // Gray for joint intersecting lines
#define JOINT_LINE_LENGTH (LINE_WIDTH * 2)
#define JOINT_LINE_SPACING 10  // Distance between the two joint lines

#define MAX_ZOOMPCT_NAVPOLY 200
#define MIN_ZOOMPCT_NAVPOLY 50

#define USE_FIXED_BLEND 0 // Set to 1 to use fixed background blending optimization (no framebuffer read), 0 for normal blending

//------------------------------------------------------------------------------
// Optimized Anti-Aliased Thick Line Drawing
// Uses scanline rasterization instead of per-pixel kernel testing
//------------------------------------------------------------------------------

// 16.16 fixed point math
typedef int32_t fix16_t;
#define FIX16_SHIFT     16
#define FIX16_SCALE     (1 << FIX16_SHIFT)
#define FIX16_ONE       (1 << FIX16_SHIFT)
#define FIX16_HALF      (1 << (FIX16_SHIFT - 1))
#define FIX16_FROM_INT(i)   ((fix16_t)((i) << FIX16_SHIFT))
#define FIX16_TO_INT(f)     ((f) >> FIX16_SHIFT)
// Floor: arithmetic right shift rounds toward -infinity (works for both positive and negative)
#define FIX16_FLOOR(f)      ((f) >> FIX16_SHIFT)
// Ceil: use identity ceil(x) = -floor(-x)
#define FIX16_CEIL(f)       (-((-(f)) >> FIX16_SHIFT))
#define FIX16_FROM_FLOAT(f) ((fix16_t)((f) * FIX16_SCALE))

// 64-bit multiply - use when operands may be large (coordinates, lengths)
#define FIX16_MUL(a, b)     ((fix16_t)(((int64_t)(a) * (int64_t)(b)) >> FIX16_SHIFT))

// 32-bit multiply - faster on ARM Cortex-A7, use when |a|,|b| < 32768 (15.16 range)
// Safe for: normalized directions, small deltas, alpha values
#define FIX16_MUL_SMALL(a, b) ((fix16_t)(((a) * (b)) >> FIX16_SHIFT))

#define FIX16_DIV(a, b)     ((fix16_t)(((int64_t)(a) << FIX16_SHIFT) / (b)))

// Fixed point square root for 16.16 format (takes 64-bit input to avoid overflow)
static fix16_t fix16_sqrt64(int64_t x) {
    if (x <= 0) return 0;

    // Scale up by 2^16 before sqrt so result is in 16.16 format
    uint64_t val = (uint64_t)x << FIX16_SHIFT;
    uint64_t root = 0;
    uint64_t bit = (uint64_t)1 << 62;

    // Find highest bit
    while (bit > val) bit >>= 2;

    // Digit-by-digit sqrt
    while (bit != 0) {
        if (val >= root + bit) {
            val -= root + bit;
            root = (root >> 1) + bit;
        } else {
            root >>= 1;
        }
        bit >>= 2;
    }

    return (fix16_t)root;
}

// 64-bit multiply for squared values that may overflow 32-bit
#define FIX16_MUL64(a, b)   (((int64_t)(a) * (int64_t)(b)) >> FIX16_SHIFT)

// 32-bit version for smaller values (like distance calculations bounded by halfWidth)
static fix16_t fix16_sqrt(fix16_t x) {
    return fix16_sqrt64((int64_t)x);
}

//------------------------------------------------------------------------------
// Optimized RGB565 pixel operations (bypasses generic renderer overhead)
//------------------------------------------------------------------------------

// RGB565 format: RRRRR GGGGGG BBBBB
#define RGB565_R_MASK   0xF800
#define RGB565_G_MASK   0x07E0
#define RGB565_B_MASK   0x001F

// Fixed background color for optimized blending (avoids read-modify-write)
// Default: black (0x0000). Change to match your widget background.
#ifndef RGB565_FIXED_BACKGROUND
#define RGB565_FIXED_BACKGROUND 0x0000
#endif

// Fast divide by 255: x / 255 ≈ (x * 257 + 256) >> 16
// Exact for x in [0, 65535], which covers all our blend cases
#define FAST_DIV255(x) (((x) * 257 + 256) >> 16)

// Optimized RGB565 blend with fixed background (no framebuffer read required)
// result = src * alpha + background * (255 - alpha)
static inline uint16_t rgb565_blend_fixed(uint16_t src, uint32_t alpha)
{
    // Pre-extract fixed background components (compiler will optimize if constant)
    const uint32_t bgR = (RGB565_FIXED_BACKGROUND & RGB565_R_MASK) >> 11;
    const uint32_t bgG = (RGB565_FIXED_BACKGROUND & RGB565_G_MASK) >> 5;
    const uint32_t bgB = (RGB565_FIXED_BACKGROUND & RGB565_B_MASK);

    uint32_t srcR = (src & RGB565_R_MASK) >> 11;
    uint32_t srcG = (src & RGB565_G_MASK) >> 5;
    uint32_t srcB = (src & RGB565_B_MASK);

    // Blend with fixed background using fast division
    uint32_t invAlpha = 255 - alpha;
    uint32_t outR = FAST_DIV255(srcR * alpha + bgR * invAlpha);
    uint32_t outG = FAST_DIV255(srcG * alpha + bgG * invAlpha);
    uint32_t outB = FAST_DIV255(srcB * alpha + bgB * invAlpha);

    return (uint16_t)((outR << 11) | (outG << 5) | outB);
}


// Fast RGB565 alpha blend: result = src * alpha + dest * (255 - alpha)
// Uses 5-6-5 bit extraction and fixed-point math for speed
static inline uint16_t rgb565_blend(uint16_t dest, uint16_t src, uint32_t alpha)
{
    // Extract RGB components
    uint32_t dstR = (dest & RGB565_R_MASK) >> 11;
    uint32_t dstG = (dest & RGB565_G_MASK) >> 5;
    uint32_t dstB = (dest & RGB565_B_MASK);
    uint32_t srcR = (src & RGB565_R_MASK) >> 11;
    uint32_t srcG = (src & RGB565_G_MASK) >> 5;
    uint32_t srcB = (src & RGB565_B_MASK);

    // Blend: out = src * alpha/255 + dest * (255-alpha)/255
    uint32_t invAlpha = 255 - alpha;
    uint32_t outR = FAST_DIV255(srcR * alpha + dstR * invAlpha);
    uint32_t outG = FAST_DIV255(srcG * alpha + dstG * invAlpha);
    uint32_t outB = FAST_DIV255(srcB * alpha + dstB * invAlpha);

    return (uint16_t)((outR << 11) | (outG << 5) | outB);
}



// Cached render buffer state for fast pixel access
typedef struct {
    uint16_t* pixels;
    int32_t width;
    int32_t frameX;  // Frame rect origin (scratch buffer position in screen coords)
    int32_t frameY;
} RenderState565;

static inline void initRenderState565(RenderState565* state, leRect* clipRect)
{
    lePixelBuffer* buf = leGetRenderBuffer();
    leRect frameRect;
    leRenderer_GetFrameRect(&frameRect);
    leRenderer_GetClipRect(clipRect);

    state->pixels = (uint16_t*)buf->pixels;
    state->width = buf->size.width;
    // Frame rect is the scratch buffer's position in screen coordinates
    state->frameX = frameRect.x;
    state->frameY = frameRect.y;
}

static inline void putPixel565(RenderState565* state, int32_t x, int32_t y, uint16_t color)
{
    // Offset to scratch buffer coordinates (scratch buffer origin is at frameX, frameY)
    int32_t bx = x - state->frameX;
    int32_t by = y - state->frameY;
    state->pixels[by * state->width + bx] = color;
}

static inline void blendPixel565(RenderState565* state, int32_t x, int32_t y, uint16_t color, uint32_t alpha)
{
    // Offset to scratch buffer coordinates (scratch buffer origin is at frameX, frameY)
    int32_t bx = x - state->frameX;
    int32_t by = y - state->frameY;
#if USE_FIXED_BLEND
    // Use fixed background blend - no framebuffer read required
    state->pixels[by * state->width + bx] = rgb565_blend_fixed(color, alpha);
#else
    uint16_t* ptr = &state->pixels[by * state->width + bx];
    *ptr = rgb565_blend(*ptr, color, alpha);
#endif    
}

static inline fix16_t fix16_abs(fix16_t x) {
    return x < 0 ? -x : x;
}

//------------------------------------------------------------------------------
// Optimized RGBA8888 pixel operations (bypasses generic renderer overhead)
//------------------------------------------------------------------------------

// RGBA8888 format: 0xRRGGBBAA
#define RGBA8888_R_SHIFT   24
#define RGBA8888_G_SHIFT   16
#define RGBA8888_B_SHIFT   8
#define RGBA8888_A_SHIFT   0

// Fast RGBA8888 alpha blend: result = src * alpha + dest * (255 - alpha)
static inline uint32_t rgba8888_blend(uint32_t dest, uint32_t src, uint32_t alpha)
{
    uint32_t dstR = (dest >> RGBA8888_R_SHIFT) & 0xFF;
    uint32_t dstG = (dest >> RGBA8888_G_SHIFT) & 0xFF;
    uint32_t dstB = (dest >> RGBA8888_B_SHIFT) & 0xFF;
    uint32_t dstA = (dest >> RGBA8888_A_SHIFT) & 0xFF;

    uint32_t srcR = (src >> RGBA8888_R_SHIFT) & 0xFF;
    uint32_t srcG = (src >> RGBA8888_G_SHIFT) & 0xFF;
    uint32_t srcB = (src >> RGBA8888_B_SHIFT) & 0xFF;
    uint32_t srcA = (src >> RGBA8888_A_SHIFT) & 0xFF;

    uint32_t invAlpha = 255 - alpha;
    uint32_t outR = FAST_DIV255(srcR * alpha + dstR * invAlpha);
    uint32_t outG = FAST_DIV255(srcG * alpha + dstG * invAlpha);
    uint32_t outB = FAST_DIV255(srcB * alpha + dstB * invAlpha);
    uint32_t outA = FAST_DIV255(srcA * alpha + dstA * invAlpha);

    return (outR << RGBA8888_R_SHIFT) | (outG << RGBA8888_G_SHIFT) |
           (outB << RGBA8888_B_SHIFT) | (outA << RGBA8888_A_SHIFT);
}

#if USE_NEON
// NEON-optimized: blend 4 RGBA8888 pixels at once
// dest/src are arrays of 4 pixels, alpha is uniform for all 4
static inline void rgba8888_blend_neon_4(uint32_t* dest, uint32_t src, uint8_t alpha)
{
    // Load 4 destination pixels (16 bytes = 4x RGBA)
    uint8x16_t vdst = vld1q_u8((uint8_t*)dest);

    // Broadcast source color to all 4 pixel positions
    uint8x16_t vsrc = vreinterpretq_u8_u32(vdupq_n_u32(src));

    // Create alpha and inverse alpha vectors
    uint8x16_t valpha = vdupq_n_u8(alpha);
    uint8x16_t vinvalpha = vdupq_n_u8(255 - alpha);

    // Widen to 16-bit for multiply: dst_lo, dst_hi, src_lo, src_hi
    uint16x8_t dst_lo = vmovl_u8(vget_low_u8(vdst));
    uint16x8_t dst_hi = vmovl_u8(vget_high_u8(vdst));
    uint16x8_t src_lo = vmovl_u8(vget_low_u8(vsrc));
    uint16x8_t src_hi = vmovl_u8(vget_high_u8(vsrc));

    // Widen alpha
    uint16x8_t alpha_lo = vmovl_u8(vget_low_u8(valpha));
    uint16x8_t alpha_hi = vmovl_u8(vget_high_u8(valpha));
    uint16x8_t invalpha_lo = vmovl_u8(vget_low_u8(vinvalpha));
    uint16x8_t invalpha_hi = vmovl_u8(vget_high_u8(vinvalpha));

    // Blend: out = (src * alpha + dst * (255-alpha)) / 255
    // Use >> 8 as fast approximation (slightly off but visually fine)
    uint16x8_t out_lo = vaddq_u16(vmulq_u16(src_lo, alpha_lo), vmulq_u16(dst_lo, invalpha_lo));
    uint16x8_t out_hi = vaddq_u16(vmulq_u16(src_hi, alpha_hi), vmulq_u16(dst_hi, invalpha_hi));

    // Divide by 255 using >> 8 (fast approximation)
    uint8x8_t result_lo = vshrn_n_u16(out_lo, 8);
    uint8x8_t result_hi = vshrn_n_u16(out_hi, 8);

    // Combine and store
    uint8x16_t result = vcombine_u8(result_lo, result_hi);
    vst1q_u8((uint8_t*)dest, result);
}

// Fill 4 consecutive RGBA8888 pixels with same color (no blending)
static inline void rgba8888_fill_neon_4(uint32_t* dest, uint32_t color)
{
    uint32x4_t vcolor = vdupq_n_u32(color);
    vst1q_u32(dest, vcolor);
}
#endif

// Cached render buffer state for fast RGBA8888 pixel access
typedef struct {
    uint32_t* pixels;
    int32_t width;
    int32_t frameX;
    int32_t frameY;
} RenderState8888;

static inline void initRenderState8888(RenderState8888* state, leRect* clipRect)
{
    lePixelBuffer* buf = leGetRenderBuffer();
    leRect frameRect;
    leRenderer_GetFrameRect(&frameRect);
    leRenderer_GetClipRect(clipRect);

    state->pixels = (uint32_t*)buf->pixels;
    state->width = buf->size.width;
    state->frameX = frameRect.x;
    state->frameY = frameRect.y;
}

static inline void putPixel8888(RenderState8888* state, int32_t x, int32_t y, uint32_t color)
{
    int32_t bx = x - state->frameX;
    int32_t by = y - state->frameY;
    state->pixels[by * state->width + bx] = color;
}

static inline void blendPixel8888(RenderState8888* state, int32_t x, int32_t y, uint32_t color, uint32_t alpha)
{
    int32_t bx = x - state->frameX;
    int32_t by = y - state->frameY;
    uint32_t* ptr = &state->pixels[by * state->width + bx];
    *ptr = rgba8888_blend(*ptr, color, alpha);
}

// Draw a thick anti-aliased line using scanline rasterization
// Uses 16.16 fixed point math and optimized RGB565 pixel ops
static void drawAALine(fix16_t x0, fix16_t y0, fix16_t x1, fix16_t y1,
                       fix16_t width, uint16_t color565, uint32_t alpha)
{
    // Initialize optimized render state once
    RenderState565 rs;
    leRect clipRect;
    initRenderState565(&rs, &clipRect);

    // Line vector and length (use 64-bit for squared length to avoid overflow)
    fix16_t dx = x1 - x0;
    fix16_t dy = y1 - y0;
    int64_t lineLenSq = FIX16_MUL64(dx, dx) + FIX16_MUL64(dy, dy);
    fix16_t lineLen = fix16_sqrt64(lineLenSq);

    if (lineLen < 64) return;  // ~0.001 in fixed point

    // Normalized direction and perpendicular
    fix16_t dirX = FIX16_DIV(dx, lineLen);
    fix16_t dirY = FIX16_DIV(dy, lineLen);
    fix16_t perpX = -dirY;
    fix16_t perpY = dirX;

    fix16_t halfWidth = width >> 1;

    // Compute bounding box corners
    fix16_t perpHalfX = FIX16_MUL(perpX, halfWidth);
    fix16_t perpHalfY = FIX16_MUL(perpY, halfWidth);

    fix16_t corners[8] = {
        x0 + perpHalfX, y0 + perpHalfY,
        x0 - perpHalfX, y0 - perpHalfY,
        x1 + perpHalfX, y1 + perpHalfY,
        x1 - perpHalfX, y1 - perpHalfY
    };

    fix16_t minX = corners[0], maxX = corners[0];
    fix16_t minY = corners[1], maxY = corners[1];
    for (int i = 2; i < 8; i += 2) {
        if (corners[i] < minX) minX = corners[i];
        if (corners[i] > maxX) maxX = corners[i];
        if (corners[i+1] < minY) minY = corners[i+1];
        if (corners[i+1] > maxY) maxY = corners[i+1];
    }

    // Expand for round caps
    minX -= halfWidth;
    maxX += halfWidth;
    minY -= halfWidth;
    maxY += halfWidth;

    int startY = FIX16_FLOOR(minY);
    int endY = FIX16_CEIL(maxY);
    int startX = FIX16_FLOOR(minX);
    int endX = FIX16_CEIL(maxX);

    // Clip to render area (use clip rect for bounds checking)
    if (startY < clipRect.y) startY = clipRect.y;
    if (endY > clipRect.y + clipRect.height) endY = clipRect.y + clipRect.height;
    if (startX < clipRect.x) startX = clipRect.x;
    if (endX > clipRect.x + clipRect.width) endX = clipRect.x + clipRect.width;

    fix16_t halfWidthSq = FIX16_MUL(halfWidth, halfWidth);

    // Scanline rasterization - compute X span per scanline
    for (int py = startY; py < endY; py++)
    {
        fix16_t cy = FIX16_FROM_INT(py) + FIX16_HALF;

        // Compute X range where line intersects this scanline
        fix16_t scanMinX = maxX + FIX16_ONE;
        fix16_t scanMaxX = minX - FIX16_ONE;

        // Check intersection with start cap (circle at x0, y0)
        fix16_t cdy0 = cy - y0;
        if (fix16_abs(cdy0) <= halfWidth) {
            fix16_t cdy0Sq = FIX16_MUL(cdy0, cdy0);
            fix16_t capDx = fix16_sqrt(halfWidthSq - cdy0Sq);
            fix16_t capLeft = x0 - capDx;
            fix16_t capRight = x0 + capDx;
            if (capLeft < scanMinX) scanMinX = capLeft;
            if (capRight > scanMaxX) scanMaxX = capRight;
        }

        // Check intersection with end cap (circle at x1, y1)
        fix16_t cdy1 = cy - y1;
        if (fix16_abs(cdy1) <= halfWidth) {
            fix16_t cdy1Sq = FIX16_MUL(cdy1, cdy1);
            fix16_t capDx = fix16_sqrt(halfWidthSq - cdy1Sq);
            fix16_t capLeft = x1 - capDx;
            fix16_t capRight = x1 + capDx;
            if (capLeft < scanMinX) scanMinX = capLeft;
            if (capRight > scanMaxX) scanMaxX = capRight;
        }

        // Check intersection with line body (rectangle edges)
        if (fix16_abs(dy) > 64) {
            // Edge 1
            fix16_t edge1Y0 = y0 + perpHalfY;
            fix16_t edge1Y1 = y1 + perpHalfY;
            fix16_t edge1X0 = x0 + perpHalfX;
            fix16_t edge1X1 = x1 + perpHalfX;
            if ((cy >= edge1Y0 && cy <= edge1Y1) || (cy >= edge1Y1 && cy <= edge1Y0)) {
                fix16_t t1 = FIX16_DIV(cy - edge1Y0, edge1Y1 - edge1Y0);
                fix16_t ix1 = edge1X0 + FIX16_MUL(t1, edge1X1 - edge1X0);
                if (ix1 < scanMinX) scanMinX = ix1;
                if (ix1 > scanMaxX) scanMaxX = ix1;
            }

            // Edge 2
            fix16_t edge2Y0 = y0 - perpHalfY;
            fix16_t edge2Y1 = y1 - perpHalfY;
            fix16_t edge2X0 = x0 - perpHalfX;
            fix16_t edge2X1 = x1 - perpHalfX;
            if ((cy >= edge2Y0 && cy <= edge2Y1) || (cy >= edge2Y1 && cy <= edge2Y0)) {
                fix16_t t2 = FIX16_DIV(cy - edge2Y0, edge2Y1 - edge2Y0);
                fix16_t ix2 = edge2X0 + FIX16_MUL(t2, edge2X1 - edge2X0);
                if (ix2 < scanMinX) scanMinX = ix2;
                if (ix2 > scanMaxX) scanMaxX = ix2;
            }
        } else {
            // Horizontal line - body spans full X range if Y is within halfWidth
            fix16_t bodyMinY = (y0 < y1 ? y0 : y1) - halfWidth;
            fix16_t bodyMaxY = (y0 > y1 ? y0 : y1) + halfWidth;
            if (cy >= bodyMinY && cy <= bodyMaxY) {
                fix16_t bodyLeft = (x0 < x1 ? x0 : x1);
                fix16_t bodyRight = (x0 > x1 ? x0 : x1);
                if (bodyLeft < scanMinX) scanMinX = bodyLeft;
                if (bodyRight > scanMaxX) scanMaxX = bodyRight;
            }
        }

        // Skip scanline if no intersection
        if (scanMinX > scanMaxX) continue;

        // Clamp to clip rect
        int pxStart = FIX16_FLOOR(scanMinX);
        int pxEnd = FIX16_CEIL(scanMaxX);
        if (pxStart < clipRect.x) pxStart = clipRect.x;
        if (pxEnd > clipRect.x + clipRect.width) pxEnd = clipRect.x + clipRect.width;

        // Precompute thresholds for early-out tests (avoid sqrt for most pixels)
        fix16_t innerRadius = halfWidth - FIX16_ONE;
        fix16_t innerRadiusSq = (innerRadius > 0) ? FIX16_MUL(innerRadius, innerRadius) : 0;

        for (int px = pxStart; px < pxEnd; px++)
        {
            fix16_t cx = FIX16_FROM_INT(px) + FIX16_HALF;

            // Project point onto line to find closest point
            fix16_t toCenterX = cx - x0;
            fix16_t toCenterY = cy - y0;

            // Parameter along line (0 = at p0, 1 = at p1)
            fix16_t dotProd = FIX16_MUL(toCenterX, dirX) + FIX16_MUL(toCenterY, dirY);
            fix16_t t = FIX16_DIV(dotProd, lineLen);

            fix16_t distSq;
            fix16_t dcx, dcy;

            if (t < 0) {
                dcx = cx - x0;
                dcy = cy - y0;
                distSq = FIX16_MUL(dcx, dcx) + FIX16_MUL(dcy, dcy);
            }
            else if (t > FIX16_ONE) {
                dcx = cx - x1;
                dcy = cy - y1;
                distSq = FIX16_MUL(dcx, dcx) + FIX16_MUL(dcy, dcy);
            }
            else {
                fix16_t closestX = x0 + FIX16_MUL(t, dx);
                fix16_t closestY = y0 + FIX16_MUL(t, dy);
                dcx = cx - closestX;
                dcy = cy - closestY;
                distSq = FIX16_MUL(dcx, dcx) + FIX16_MUL(dcy, dcy);
            }

            // Early out: pixel clearly outside line (no sqrt needed)
            if (distSq > halfWidthSq) continue;

            // Early in: pixel clearly inside line (no sqrt needed, full alpha)
            if (distSq <= innerRadiusSq) {
                putPixel565(&rs, px, py, color565);
                continue;
            }

            // Edge pixel: need sqrt for accurate anti-aliasing
            fix16_t distance = fix16_sqrt(distSq);
            fix16_t edgeDist = halfWidth - distance;

            if (edgeDist <= 0) continue;

            uint32_t pixelAlpha = (uint32_t)((alpha * edgeDist) >> FIX16_SHIFT);

            if (pixelAlpha > 250) {
                putPixel565(&rs, px, py, color565);
            }
            else if (pixelAlpha > 0) {
                blendPixel565(&rs, px, py, color565, pixelAlpha);
            }
        }
    }
}

// Draw a thick anti-aliased line using scanline rasterization for RGBA8888
// Uses 16.16 fixed point math and optimized RGBA8888 pixel ops
static void drawAALine8888(fix16_t x0, fix16_t y0, fix16_t x1, fix16_t y1,
                           fix16_t width, uint32_t color, uint32_t alpha)
{
    RenderState8888 rs;
    leRect clipRect;
    initRenderState8888(&rs, &clipRect);

    fix16_t dx = x1 - x0;
    fix16_t dy = y1 - y0;
    int64_t lineLenSq = FIX16_MUL64(dx, dx) + FIX16_MUL64(dy, dy);
    fix16_t lineLen = fix16_sqrt64(lineLenSq);

    if (lineLen < 64) return;

    fix16_t dirX = FIX16_DIV(dx, lineLen);
    fix16_t dirY = FIX16_DIV(dy, lineLen);
    fix16_t perpX = -dirY;
    fix16_t perpY = dirX;

    fix16_t halfWidth = width >> 1;

    fix16_t perpHalfX = FIX16_MUL(perpX, halfWidth);
    fix16_t perpHalfY = FIX16_MUL(perpY, halfWidth);

    fix16_t corners[8] = {
        x0 + perpHalfX, y0 + perpHalfY,
        x0 - perpHalfX, y0 - perpHalfY,
        x1 + perpHalfX, y1 + perpHalfY,
        x1 - perpHalfX, y1 - perpHalfY
    };

    fix16_t minX = corners[0], maxX = corners[0];
    fix16_t minY = corners[1], maxY = corners[1];
    for (int i = 2; i < 8; i += 2) {
        if (corners[i] < minX) minX = corners[i];
        if (corners[i] > maxX) maxX = corners[i];
        if (corners[i+1] < minY) minY = corners[i+1];
        if (corners[i+1] > maxY) maxY = corners[i+1];
    }

    minX -= halfWidth;
    maxX += halfWidth;
    minY -= halfWidth;
    maxY += halfWidth;

    int startY = FIX16_FLOOR(minY);
    int endY = FIX16_CEIL(maxY);
    int startX = FIX16_FLOOR(minX);
    int endX = FIX16_CEIL(maxX);

    if (startY < clipRect.y) startY = clipRect.y;
    if (endY > clipRect.y + clipRect.height) endY = clipRect.y + clipRect.height;
    if (startX < clipRect.x) startX = clipRect.x;
    if (endX > clipRect.x + clipRect.width) endX = clipRect.x + clipRect.width;

    fix16_t halfWidthSq = FIX16_MUL(halfWidth, halfWidth);

    for (int py = startY; py < endY; py++)
    {
        fix16_t cy = FIX16_FROM_INT(py) + FIX16_HALF;

        fix16_t scanMinX = maxX + FIX16_ONE;
        fix16_t scanMaxX = minX - FIX16_ONE;

        fix16_t cdy0 = cy - y0;
        if (fix16_abs(cdy0) <= halfWidth) {
            fix16_t cdy0Sq = FIX16_MUL(cdy0, cdy0);
            fix16_t capDx = fix16_sqrt(halfWidthSq - cdy0Sq);
            fix16_t capLeft = x0 - capDx;
            fix16_t capRight = x0 + capDx;
            if (capLeft < scanMinX) scanMinX = capLeft;
            if (capRight > scanMaxX) scanMaxX = capRight;
        }

        fix16_t cdy1 = cy - y1;
        if (fix16_abs(cdy1) <= halfWidth) {
            fix16_t cdy1Sq = FIX16_MUL(cdy1, cdy1);
            fix16_t capDx = fix16_sqrt(halfWidthSq - cdy1Sq);
            fix16_t capLeft = x1 - capDx;
            fix16_t capRight = x1 + capDx;
            if (capLeft < scanMinX) scanMinX = capLeft;
            if (capRight > scanMaxX) scanMaxX = capRight;
        }

        if (fix16_abs(dy) > 64) {
            fix16_t edge1Y0 = y0 + perpHalfY;
            fix16_t edge1Y1 = y1 + perpHalfY;
            fix16_t edge1X0 = x0 + perpHalfX;
            fix16_t edge1X1 = x1 + perpHalfX;
            if ((cy >= edge1Y0 && cy <= edge1Y1) || (cy >= edge1Y1 && cy <= edge1Y0)) {
                fix16_t t1 = FIX16_DIV(cy - edge1Y0, edge1Y1 - edge1Y0);
                fix16_t ix1 = edge1X0 + FIX16_MUL(t1, edge1X1 - edge1X0);
                if (ix1 < scanMinX) scanMinX = ix1;
                if (ix1 > scanMaxX) scanMaxX = ix1;
            }

            fix16_t edge2Y0 = y0 - perpHalfY;
            fix16_t edge2Y1 = y1 - perpHalfY;
            fix16_t edge2X0 = x0 - perpHalfX;
            fix16_t edge2X1 = x1 - perpHalfX;
            if ((cy >= edge2Y0 && cy <= edge2Y1) || (cy >= edge2Y1 && cy <= edge2Y0)) {
                fix16_t t2 = FIX16_DIV(cy - edge2Y0, edge2Y1 - edge2Y0);
                fix16_t ix2 = edge2X0 + FIX16_MUL(t2, edge2X1 - edge2X0);
                if (ix2 < scanMinX) scanMinX = ix2;
                if (ix2 > scanMaxX) scanMaxX = ix2;
            }
        } else {
            fix16_t bodyMinY = (y0 < y1 ? y0 : y1) - halfWidth;
            fix16_t bodyMaxY = (y0 > y1 ? y0 : y1) + halfWidth;
            if (cy >= bodyMinY && cy <= bodyMaxY) {
                fix16_t bodyLeft = (x0 < x1 ? x0 : x1);
                fix16_t bodyRight = (x0 > x1 ? x0 : x1);
                if (bodyLeft < scanMinX) scanMinX = bodyLeft;
                if (bodyRight > scanMaxX) scanMaxX = bodyRight;
            }
        }

        if (scanMinX > scanMaxX) continue;

        int pxStart = FIX16_FLOOR(scanMinX);
        int pxEnd = FIX16_CEIL(scanMaxX);
        if (pxStart < clipRect.x) pxStart = clipRect.x;
        if (pxEnd > clipRect.x + clipRect.width) pxEnd = clipRect.x + clipRect.width;

        // Precompute thresholds for early-out tests (avoid sqrt for most pixels)
        // innerRadiusSq = (halfWidth - 1)^2: pixels inside this are fully opaque
        // outerRadiusSq = halfWidth^2: pixels outside this are fully transparent
        fix16_t innerRadius = halfWidth - FIX16_ONE;
        fix16_t innerRadiusSq = (innerRadius > 0) ? FIX16_MUL(innerRadius, innerRadius) : 0;

        for (int px = pxStart; px < pxEnd; px++)
        {
            fix16_t cx = FIX16_FROM_INT(px) + FIX16_HALF;

            fix16_t toCenterX = cx - x0;
            fix16_t toCenterY = cy - y0;

            fix16_t dotProd = FIX16_MUL(toCenterX, dirX) + FIX16_MUL(toCenterY, dirY);
            fix16_t t = FIX16_DIV(dotProd, lineLen);

            fix16_t distSq;
            fix16_t dcx, dcy;

            if (t < 0) {
                dcx = cx - x0;
                dcy = cy - y0;
                distSq = FIX16_MUL(dcx, dcx) + FIX16_MUL(dcy, dcy);
            }
            else if (t > FIX16_ONE) {
                dcx = cx - x1;
                dcy = cy - y1;
                distSq = FIX16_MUL(dcx, dcx) + FIX16_MUL(dcy, dcy);
            }
            else {
                fix16_t closestX = x0 + FIX16_MUL(t, dx);
                fix16_t closestY = y0 + FIX16_MUL(t, dy);
                dcx = cx - closestX;
                dcy = cy - closestY;
                distSq = FIX16_MUL(dcx, dcx) + FIX16_MUL(dcy, dcy);
            }

            // Early out: pixel clearly outside line (no sqrt needed)
            if (distSq > halfWidthSq) continue;

            // Early in: pixel clearly inside line (no sqrt needed, full alpha)
            if (distSq <= innerRadiusSq) {
                putPixel8888(&rs, px, py, color);
                continue;
            }

            // Edge pixel: need sqrt for accurate anti-aliasing
            fix16_t distance = fix16_sqrt(distSq);
            fix16_t edgeDist = halfWidth - distance;

            if (edgeDist <= 0) continue;

            uint32_t pixelAlpha = (uint32_t)((alpha * edgeDist) >> FIX16_SHIFT);

            if (pixelAlpha > 250) {
                putPixel8888(&rs, px, py, color);
            }
            else if (pixelAlpha > 0) {
                blendPixel8888(&rs, px, py, color, pixelAlpha);
            }
        }
    }
}

// Wrapper that matches leVectorLineAttr interface (converts float coords to fixed point)
static void drawAALineAttr(float x0, float y0, float x1, float y1,
                           const leVectorLineAttr* attr)
{
    // Convert color to RGB565 (attr->color is already in native format)
    drawAALine(FIX16_FROM_FLOAT(x0), FIX16_FROM_FLOAT(y0),
               FIX16_FROM_FLOAT(x1), FIX16_FROM_FLOAT(y1),
               attr->width, (uint16_t)attr->color, attr->alpha);
}

typedef struct
{
    int16_t startx;
    int16_t starty;
    int16_t endx;
    int16_t endy;
} NAV_RouteSegment;

NAV_RouteSegment waypoints[] = {
    // Start heading north
    {100,  800,  100,  600},
    {100,  600,  100,  400},
    // Turn right (east)
    {100,  400,  250,  350},
    {250,  350,  450,  350},
    // Curve up and right
    {450,  350,  550,  250},
    {550,  250,  600,  100},
    // Head north
    {600,  100,  600,  -100},
    {600,  -100, 600,  -250},
    // Turn left (west)
    {600,  -250, 450,  -350},
    {450,  -350, 250,  -350},
    // Continue west and curve south
    {250,  -350, 100,  -250},
    {100,  -250, 100,  -50},
    // Head south
    {100,  -50,  100,  150},
    // Turn right (east)
    {100,  150,  250,  200},
    {250,  200,  450,  200},
    // Curve south
    {450,  200,  550,  350},
    {550,  350,  550,  550},
    // Turn west
    {550,  550,  350,  650},
    {350,  650,  150,  700},
    // Head south to loop back
    {150,  700,  100,  800},
};

// Street names for each waypoint segment (unique for each)
static const char* streetNames[] = {
    "Main St",
    "Park Ave",
    "Oak Dr",
    "Riverside Blvd",
    "Elm Ct",
    "Summit Rd",
    "Pine Way",
    "Harbor Ln",
    "Maple Ter",
    "Valley View",
    "Cedar Ridge",
    "Hillcrest Dr",
    "Birch Pl",
    "Walnut Cir",
    "Lakeshore Dr",
    "Cherry Ln",
    "Sunset Blvd",
    "Willow Bend",
    "Forest Ave",
    "Station Rd"
};

// Fixed strings for label updates
static leChar distanceStrBuf[16];
static leChar streetStrBuf[32];
static leFixedString distanceFixedStr;
static leFixedString streetFixedStr;

// Scale factor: pixels to miles (adjust as needed for realistic distances)
#define PIXELS_TO_MILES 0.001f

static uint32_t lastTickCounter = 0;
static SYS_TIME_HANDLE appTimerHandle;
static leRect visibleBounds = {0};        // Bounding rect of visible segments (for partial invalidation)

// Shared navigation state (calculated in OnUpdate, used in OnDraw)
static struct {
    float curPosX;
    float curPosY;
    float displayAngle;
    float cosAngle;      // Cached cos(displayAngle) for consistent rotation
    float sinAngle;      // Cached sin(displayAngle) for consistent rotation
    float zoomFactor;    // Zoom scale factor (0.3 to 2.0, default 1.0)
    uint32_t currentSegment;
    float xOffset;       // Pan offset X from center (touch drag)
    float yOffset;       // Pan offset Y from center (touch drag)
} navState = {0};

// Normalize angle to [-PI, PI]
static float normalizeAngle(float angle)
{
    while (angle > PI) angle -= TWO_PI;
    while (angle < -PI) angle += TWO_PI;
    return angle;
}

// Smoothly interpolate between angles, handling wrap-around
static float lerpAngle(float current, float target, float t)
{
    float diff = normalizeAngle(target - current);
    return current + diff * t;
}

// Calculate segment length
static float getSegmentLength(const NAV_RouteSegment* seg)
{
    float dx = seg->endx - seg->startx;
    float dy = seg->endy - seg->starty;
    return sqrtf(dx * dx + dy * dy);
}

// Rotate point (px, py) around origin by angle (radians)
static void rotatePoint(float px, float py, float angle, float* outX, float* outY)
{
    float cosA = cosf(angle);
    float sinA = sinf(angle);
    *outX = px * cosA - py * sinA;
    *outY = px * sinA + py * cosA;
}

void NavPoly_OnShow(void)
{
    lastTickCounter = 0;
    navState.displayAngle = 0.0f;  // Reset rotation animation
    navState.cosAngle = 1.0f;      // cos(0) = 1
    navState.sinAngle = 0.0f;      // sin(0) = 0
    navState.zoomFactor = 1.0f;    // Default 100% zoom
    navState.xOffset = 0.0f;       // Reset pan offset
    navState.yOffset = 0.0f;

    // Initialize fixed strings for distance and street labels
    leFixedString_Constructor(&distanceFixedStr, distanceStrBuf, sizeof(distanceStrBuf));
    distanceFixedStr.fn->setFont(&distanceFixedStr, (leFont*)&smallFont);

    leFixedString_Constructor(&streetFixedStr, streetStrBuf, sizeof(streetStrBuf));
    streetFixedStr.fn->setFont(&streetFixedStr, (leFont*)&smallFont);
}

void NavPoly_OnUpdate(leDrawSurfaceWidget* NavScreen_surfPath, 
                      uint32_t appTickCounter, 
                      uint32_t pct, 
                      leLabelWidget * distance,
                      leLabelWidget * street,
                      leImageWidget * dirIcon,
                      int32_t xoffset,
                      int32_t yoffset)
{
    if (appTickCounter != lastTickCounter)
    {
        uint32_t numWaypoints = sizeof(waypoints) / sizeof(waypoints[0]);

        // Clamp zoom percentage to 30-200% and convert to factor
        if (pct < 30) pct = MIN_ZOOMPCT_NAVPOLY;
        if (pct > 200) pct = MAX_ZOOMPCT_NAVPOLY;
        navState.zoomFactor = (float)pct / 100.0f;

        // Store pan offset from touch
        navState.xOffset = (float)xoffset;
        navState.yOffset = (float)yoffset;

        // Calculate total path length
        float totalLength = 0;
        for (uint32_t i = 0; i < numWaypoints; i++)
            totalLength += getSegmentLength(&waypoints[i]);

        // Current distance traveled along path (wraps around)
        float distanceTraveled = fmodf((float)appTickCounter, totalLength);

        // Find which segment we're on and position within it
        float segmentProgress = 0;
        float accumulated = 0;
        navState.currentSegment = 0;

        for (uint32_t i = 0; i < numWaypoints; i++)
        {
            float segLen = getSegmentLength(&waypoints[i]);
            if (accumulated + segLen > distanceTraveled)
            {
                navState.currentSegment = i;
                segmentProgress = (distanceTraveled - accumulated) / segLen;
                break;
            }
            accumulated += segLen;
        }

        // Current position on the path (interpolated)
        navState.curPosX = waypoints[navState.currentSegment].startx +
                        segmentProgress * (waypoints[navState.currentSegment].endx - waypoints[navState.currentSegment].startx);
        navState.curPosY = waypoints[navState.currentSegment].starty +
                        segmentProgress * (waypoints[navState.currentSegment].endy - waypoints[navState.currentSegment].starty);

        // Calculate target angle of current segment (to make it vertical, pointing up)
        float dx = waypoints[navState.currentSegment].endx - waypoints[navState.currentSegment].startx;
        float dy = waypoints[navState.currentSegment].endy - waypoints[navState.currentSegment].starty;
        float segmentAngle = atan2f(dy, dx);
        float targetAngle = -segmentAngle - (PI / 2.0f);

        // Smoothly animate rotation toward target angle
        navState.displayAngle = lerpAngle(navState.displayAngle, targetAngle, ROTATION_SMOOTHING);
        navState.displayAngle = normalizeAngle(navState.displayAngle);

        // Cache sin/cos for consistent rotation across all points
        navState.cosAngle = cosf(navState.displayAngle);
        navState.sinAngle = sinf(navState.displayAngle);

        // Calculate widget center in screen space
        lePoint widgetOrigin = {0, 0};
        leUtils_PointToScreenSpace((leWidget*)NavScreen_surfPath, &widgetOrigin);

        float widgetCenterX = (float)widgetOrigin.x + NavScreen_surfPath->widget.rect.width / 2.0f;
        float widgetCenterY = (float)widgetOrigin.y + NavScreen_surfPath->widget.rect.height / 2.0f;

        // Calculate bounding rectangles for each visible segment and damage those areas
        for (int32_t offset = -ADJACENT_SEGMENTS; offset <= ADJACENT_SEGMENTS; offset++)
        {
            int32_t idx = (int32_t)navState.currentSegment + offset;

            // Wrap around for continuous loop
            while (idx < 0)
                idx += numWaypoints;
            while (idx >= (int32_t)numWaypoints)
                idx -= numWaypoints;

            // Get segment endpoints relative to current position, scaled by zoom
            float x0 = ((float)waypoints[idx].startx - navState.curPosX) * navState.zoomFactor;
            float y0 = ((float)waypoints[idx].starty - navState.curPosY) * navState.zoomFactor;
            float x1 = ((float)waypoints[idx].endx - navState.curPosX) * navState.zoomFactor;
            float y1 = ((float)waypoints[idx].endy - navState.curPosY) * navState.zoomFactor;

            // Rotate points using cached sin/cos
            float rx0 = x0 * navState.cosAngle - y0 * navState.sinAngle + widgetCenterX;
            float ry0 = x0 * navState.sinAngle + y0 * navState.cosAngle + widgetCenterY;
            float rx1 = x1 * navState.cosAngle - y1 * navState.sinAngle + widgetCenterX;
            float ry1 = x1 * navState.sinAngle + y1 * navState.cosAngle + widgetCenterY;

            // Calculate bounding rectangle for this segment
            float minX = (rx0 < rx1) ? rx0 : rx1;
            float maxX = (rx0 > rx1) ? rx0 : rx1;
            float minY = (ry0 < ry1) ? ry0 : ry1;
            float maxY = (ry0 > ry1) ? ry0 : ry1;

            // Create damage rect with padding for line width
            // leRect segmentRect = {
            //     .x = (int16_t)(minX - BOUNDS_PADDING),
            //     .y = (int16_t)(minY - BOUNDS_PADDING),
            //     .width = (int16_t)(maxX - minX + 2 * BOUNDS_PADDING),
            //     .height = (int16_t)(maxY - minY + 2 * BOUNDS_PADDING)
            // };

            // static leRect oldSegmentRect = {0, 0, 0, 0};

            // leRenderer_DamageArea(&oldSegmentRect, 0);
            // leRenderer_DamageArea(&segmentRect, 0);

            // oldSegmentRect = segmentRect;
        }

        // Calculate bounding rectangles for joint intersecting lines and damage those areas
        for (int32_t offset = -ADJACENT_SEGMENTS; offset <= ADJACENT_SEGMENTS; offset++)
        {
            int32_t idx = (int32_t)navState.currentSegment + offset;

            // Wrap around for continuous loop
            while (idx < 0)
                idx += numWaypoints;
            while (idx >= (int32_t)numWaypoints)
                idx -= numWaypoints;

            // Get next segment index (wrapping)
            int32_t nextIdx = idx + 1;
            if (nextIdx >= (int32_t)numWaypoints)
                nextIdx = 0;

            // Get the joint position (end of this segment = start of next), scaled by zoom
            float jx = ((float)waypoints[idx].endx - navState.curPosX) * navState.zoomFactor;
            float jy = ((float)waypoints[idx].endy - navState.curPosY) * navState.zoomFactor;

            // Current segment direction (normalized)
            float dx1 = (float)(waypoints[idx].endx - waypoints[idx].startx);
            float dy1 = (float)(waypoints[idx].endy - waypoints[idx].starty);
            float len1 = sqrtf(dx1 * dx1 + dy1 * dy1);
            if (len1 < 0.001f) continue;
            dx1 /= len1;
            dy1 /= len1;

            // Next segment direction (normalized)
            float dx2 = (float)(waypoints[nextIdx].endx - waypoints[nextIdx].startx);
            float dy2 = (float)(waypoints[nextIdx].endy - waypoints[nextIdx].starty);
            float len2 = sqrtf(dx2 * dx2 + dy2 * dy2);
            if (len2 < 0.001f) continue;
            dx2 /= len2;
            dy2 /= len2;

            // Angle bisector direction
            float bisectX = dx1 + dx2;
            float bisectY = dy1 + dy2;
            float bisectLen = sqrtf(bisectX * bisectX + bisectY * bisectY);
            if (bisectLen < 0.001f) {
                bisectX = -dy1;
                bisectY = dx1;
            } else {
                bisectX /= bisectLen;
                bisectY /= bisectLen;
            }

            // Perpendicular to bisector
            float perpX = -bisectY;
            float perpY = bisectX;

            // Calculate both joint lines (two lines per joint), scaled by zoom
            float halfSpacing = (JOINT_LINE_SPACING / 2.0f) * navState.zoomFactor;
            float jointLen = JOINT_LINE_LENGTH * navState.zoomFactor;

            for (int line = 0; line < 2; line++)
            {
                float offsetDir = (line == 0) ? halfSpacing : -halfSpacing;
                float offsetJx = jx + bisectX * offsetDir;
                float offsetJy = jy + bisectY * offsetDir;

                // Joint line endpoints
                float jx0 = offsetJx + perpX * jointLen;
                float jy0 = offsetJy + perpY * jointLen;
                float jx1 = offsetJx - perpX * jointLen;
                float jy1 = offsetJy - perpY * jointLen;

                // Rotate joint line using cached sin/cos
                float rjx0 = jx0 * navState.cosAngle - jy0 * navState.sinAngle + widgetCenterX;
                float rjy0 = jx0 * navState.sinAngle + jy0 * navState.cosAngle + widgetCenterY;
                float rjx1 = jx1 * navState.cosAngle - jy1 * navState.sinAngle + widgetCenterX;
                float rjy1 = jx1 * navState.sinAngle + jy1 * navState.cosAngle + widgetCenterY;

                // Calculate bounding rectangle for this joint line
                float minX = (rjx0 < rjx1) ? rjx0 : rjx1;
                float maxX = (rjx0 > rjx1) ? rjx0 : rjx1;
                float minY = (rjy0 < rjy1) ? rjy0 : rjy1;
                float maxY = (rjy0 > rjy1) ? rjy0 : rjy1;

                // Create damage rect with padding
                // leRect jointRect = {
                //     .x = (int16_t)(minX - BOUNDS_PADDING),
                //     .y = (int16_t)(minY - BOUNDS_PADDING),
                //     .width = (int16_t)(maxX - minX + 2 * BOUNDS_PADDING),
                //     .height = (int16_t)(maxY - minY + 2 * BOUNDS_PADDING)
                // };

                // static leRect oldJointRect = {0, 0, 0, 0};

                // leRenderer_DamageArea(&oldJointRect, 0);
                // leRenderer_DamageArea(&jointRect, 0);

                // oldJointRect = jointRect;
            }
        }

        // Calculate remaining distance to next turn (end of current segment)
        float segLen = getSegmentLength(&waypoints[navState.currentSegment]);
        float distanceToTurn = segLen * (1.0f - segmentProgress);

        // Convert to miles
        float miles = distanceToTurn * PIXELS_TO_MILES;

        // Format and update distance label
        if (distance != NULL)
        {
            char tempStr[16];
            if (miles >= 1.0f)
            {
                snprintf(tempStr, sizeof(tempStr), "%.1f mi", miles);
            }
            else
            {
                // Show in feet when less than 1 mile (1 mile = 5280 feet)
                int feet = (int)(miles * 5280.0f);
                snprintf(tempStr, sizeof(tempStr), "%d ft", feet);
            }
            distanceFixedStr.fn->setFromCStr(&distanceFixedStr, tempStr);
            distance->fn->setString(distance, (leString*)&distanceFixedStr);
        }

        // Update street label with current street name
        if (street != NULL && navState.currentSegment < numWaypoints)
        {
            streetFixedStr.fn->setFromCStr(&streetFixedStr, streetNames[navState.currentSegment]);
            street->fn->setString(street, (leString*)&streetFixedStr);
        }

        // Update direction icon based on next turn
        if (dirIcon != NULL)
        {
            // Show straight icon in first half of segment, turn icon in second half
            if (segmentProgress < 0.5f)
            {
                dirIcon->fn->setImage(dirIcon, &StraightIcon);
            }
            else
            {
                // Get next segment index (wrapping)
                uint32_t nextSegment = (navState.currentSegment + 1) % numWaypoints;

                // Current segment direction
                float dx1 = (float)(waypoints[navState.currentSegment].endx - waypoints[navState.currentSegment].startx);
                float dy1 = (float)(waypoints[navState.currentSegment].endy - waypoints[navState.currentSegment].starty);

                // Next segment direction
                float dx2 = (float)(waypoints[nextSegment].endx - waypoints[nextSegment].startx);
                float dy2 = (float)(waypoints[nextSegment].endy - waypoints[nextSegment].starty);

                // Cross product to determine turn direction (negative = left, positive = right in screen coords)
                float cross = dx1 * dy2 - dy1 * dx2;

                if (cross < 0)
                {
                    dirIcon->fn->setImage(dirIcon, &TurnLeftIcon);
                }
                else
                {
                    dirIcon->fn->setImage(dirIcon, &TurnRightIcon);
                }
            }
        }

        lastTickCounter = appTickCounter;
    }
}


leBool event_NavScreen_surfPath_OnDraw(leDrawSurfaceWidget* sfc, leRect* bounds)
{
    uint32_t numWaypoints = sizeof(waypoints) / sizeof(waypoints[0]);

    // Calculate widget center in screen space using the widget's absolute position
    lePoint widgetOrigin = {0, 0};
    leUtils_PointToScreenSpace((leWidget*)sfc, &widgetOrigin);

    // Apply pan offset to widget center
    float widgetCenterX = (float)widgetOrigin.x + sfc->widget.rect.width / 2.0f + navState.xOffset;
    float widgetCenterY = (float)widgetOrigin.y + sfc->widget.rect.height / 2.0f + navState.yOffset;

    // Line attributes for joint intersecting lines (gray)
    leVectorLineAttr jointAttr = {
        .color = leColorConvert(LE_COLOR_MODE_RGBA_8888, leRenderer_CurrentColorMode(), JOINT_COLOR_RGBA),
        .alpha = 255,
        .width = LE_REAL_I16_FROM_INT(2),
        .hardness = LE_REAL_I16_ONE, //LE_REAL_I16_FROM_FLOAT(0.80f),
        .aaMode = LE_ANTIALIASING_NONE,
        .capStyle = LE_CAPSTYLE_NONE
    };

    // Draw intersecting lines at joints between segments
    for (int32_t offset = -ADJACENT_SEGMENTS; offset <= ADJACENT_SEGMENTS; offset++)
    {
        int32_t idx = (int32_t)navState.currentSegment + offset;

        // Wrap around for continuous loop
        while (idx < 0)
            idx += numWaypoints;
        while (idx >= (int32_t)numWaypoints)
            idx -= numWaypoints;

        // Get next segment index (wrapping)
        int32_t nextIdx = idx + 1;
        if (nextIdx >= (int32_t)numWaypoints)
            nextIdx = 0;

        // Get the joint position (end of this segment = start of next), scaled by zoom
        float jx = ((float)waypoints[idx].endx - navState.curPosX) * navState.zoomFactor;
        float jy = ((float)waypoints[idx].endy - navState.curPosY) * navState.zoomFactor;

        // Current segment direction (normalized)
        float dx1 = (float)(waypoints[idx].endx - waypoints[idx].startx);
        float dy1 = (float)(waypoints[idx].endy - waypoints[idx].starty);
        float len1 = sqrtf(dx1 * dx1 + dy1 * dy1);
        if (len1 < 0.001f) continue;
        dx1 /= len1;
        dy1 /= len1;

        // Next segment direction (normalized)
        float dx2 = (float)(waypoints[nextIdx].endx - waypoints[nextIdx].startx);
        float dy2 = (float)(waypoints[nextIdx].endy - waypoints[nextIdx].starty);
        float len2 = sqrtf(dx2 * dx2 + dy2 * dy2);
        if (len2 < 0.001f) continue;
        dx2 /= len2;
        dy2 /= len2;

        // Angle bisector direction (average of the two directions)
        float bisectX = dx1 + dx2;
        float bisectY = dy1 + dy2;
        float bisectLen = sqrtf(bisectX * bisectX + bisectY * bisectY);
        if (bisectLen < 0.001f) {
            // Segments are opposite directions, use perpendicular to first
            bisectX = -dy1;
            bisectY = dx1;
        } else {
            bisectX /= bisectLen;
            bisectY /= bisectLen;
        }

        // Perpendicular to bisector (rotate 90 degrees)
        float perpX = -bisectY;
        float perpY = bisectX;

        // Draw two joint lines, offset along bisector direction, scaled by zoom
        float halfSpacing = (JOINT_LINE_SPACING / 2.0f) * navState.zoomFactor;
        float jointLen = JOINT_LINE_LENGTH * navState.zoomFactor;

        for (int line = 0; line < 2; line++)
        {
            // Offset along bisector: first line forward, second line backward
            float offsetDir = (line == 0) ? halfSpacing : -halfSpacing;
            float offsetJx = jx + bisectX * offsetDir;
            float offsetJy = jy + bisectY * offsetDir;

            // Joint line endpoints (extend jointLen from offset joint)
            float jx0 = offsetJx + perpX * jointLen;
            float jy0 = offsetJy + perpY * jointLen;
            float jx1 = offsetJx - perpX * jointLen;
            float jy1 = offsetJy - perpY * jointLen;

            // Rotate joint line using cached sin/cos
            float rjx0 = jx0 * navState.cosAngle - jy0 * navState.sinAngle + widgetCenterX;
            float rjy0 = jx0 * navState.sinAngle + jy0 * navState.cosAngle + widgetCenterY;
            float rjx1 = jx1 * navState.cosAngle - jy1 * navState.sinAngle + widgetCenterX;
            float rjy1 = jx1 * navState.sinAngle + jy1 * navState.cosAngle + widgetCenterY;

            // Scale joint line width with zoom
            fix16_t scaledJointWidth = FIX16_FROM_FLOAT(2.0f * navState.zoomFactor);

            // Use optimized AA line drawing for RGBA8888
            drawAALine8888(FIX16_FROM_FLOAT(rjx0), FIX16_FROM_FLOAT(rjy0),
                           FIX16_FROM_FLOAT(rjx1), FIX16_FROM_FLOAT(rjy1),
                           scaledJointWidth, JOINT_COLOR_RGBA, jointAttr.alpha);
        }
    }    

    // Line attributes for all segments (same thickness)
    leVectorLineAttr lineAttr = {
        .color = leColorConvert(LE_COLOR_MODE_RGBA_8888, leRenderer_CurrentColorMode(), PATH_COLOR_RGBA),
        .alpha = 255,
        .width = LE_REAL_I16_FROM_INT(LINE_WIDTH),
        .hardness = LE_REAL_I16_FROM_FLOAT(0.80f), 
        .aaMode = LE_ANTIALIASING_NONE,
        .capStyle = LE_CAPSTYLE_ROUND
    };

    // Draw all visible segments using pre-calculated navState
    for (int32_t offset = -ADJACENT_SEGMENTS; offset <= ADJACENT_SEGMENTS; offset++)
    {
        int32_t idx = (int32_t)navState.currentSegment + offset;

        // Wrap around for continuous loop
        while (idx < 0)
            idx += numWaypoints;
        while (idx >= (int32_t)numWaypoints)
            idx -= numWaypoints;

        // Get segment endpoints relative to current position, scaled by zoom
        float x0 = ((float)waypoints[idx].startx - navState.curPosX) * navState.zoomFactor;
        float y0 = ((float)waypoints[idx].starty - navState.curPosY) * navState.zoomFactor;
        float x1 = ((float)waypoints[idx].endx - navState.curPosX) * navState.zoomFactor;
        float y1 = ((float)waypoints[idx].endy - navState.curPosY) * navState.zoomFactor;

        // Rotate points using cached sin/cos (ensures all points use identical values)
        float rx0 = x0 * navState.cosAngle - y0 * navState.sinAngle + widgetCenterX;
        float ry0 = x0 * navState.sinAngle + y0 * navState.cosAngle + widgetCenterY;
        float rx1 = x1 * navState.cosAngle - y1 * navState.sinAngle + widgetCenterX;
        float ry1 = x1 * navState.sinAngle + y1 * navState.cosAngle + widgetCenterY;

        // Scale line width with zoom
        fix16_t scaledLineWidth = FIX16_FROM_FLOAT(LINE_WIDTH * navState.zoomFactor);

        // Use optimized AA line drawing for RGBA8888
        drawAALine8888(FIX16_FROM_FLOAT(rx0), FIX16_FROM_FLOAT(ry0),
                       FIX16_FROM_FLOAT(rx1), FIX16_FROM_FLOAT(ry1),
                       scaledLineWidth, PATH_COLOR_RGBA, lineAttr.alpha);
    }

    return LE_TRUE;
}