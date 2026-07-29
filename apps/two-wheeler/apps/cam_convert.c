/*******************************************************************************
  Camera Pixel Format Conversion Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    cam_convert.c

  Summary:
    YUYV to RGB colour conversion with nearest-neighbour scaling.

  Description:
    YUYV (also called YUY2) packs two pixels into four bytes as Y0 U Y1 V, so a
    chroma pair is shared between each horizontal pixel pair. Conversion walks
    the destination, maps each destination pixel back to a source pixel with a
    fixed-point step, and reads the luma for that pixel together with the chroma
    of its containing pair.

    Colour conversion uses the ITU-R BT.601 limited-range coefficients, which is
    what UVC cameras actually emit (luma 16..235). Using the full-range formula
    here would produce a visibly washed-out picture.

    Coefficients, scaled by 256:

        c = Y - 16, d = U - 128, e = V - 128
        R = (298*c           + 409*e + 128) >> 8
        G = (298*c - 100*d   - 208*e + 128) >> 8
        B = (298*c + 516*d           + 128) >> 8
 *******************************************************************************/

#include <string.h>

#include "cam_convert.h"

/*******************************************************************************
 * Fixed-Point Scaling
 * Source coordinates are tracked in 16.16 fixed point so the inner loop needs
 * only an add and a shift per pixel.
 ******************************************************************************/
#define CAM_FP_SHIFT 16
#define CAM_FP_ONE   (1u << CAM_FP_SHIFT)

/*******************************************************************************
 * camClamp8
 * Saturates a signed intermediate to the 0..255 range.
 ******************************************************************************/
static uint8_t camClamp8(int32_t value)
{
    if (value < 0)
    {
        return 0;
    }

    if (value > 255)
    {
        return 255;
    }

    return (uint8_t)value;
}

/*******************************************************************************
 * camYUVToRGB
 * Converts one YUV triplet to 8-bit R, G and B components.
 ******************************************************************************/
static void camYUVToRGB(int32_t y, int32_t u, int32_t v,
                        uint8_t* r, uint8_t* g, uint8_t* b)
{
    int32_t c = y - 16;
    int32_t d = u - 128;
    int32_t e = v - 128;

    *r = camClamp8((298 * c + 409 * e + 128) >> 8);
    *g = camClamp8((298 * c - 100 * d - 208 * e + 128) >> 8);
    *b = camClamp8((298 * c + 516 * d + 128) >> 8);
}

/*******************************************************************************
 * camConvertPrepare
 * Validates both sides of a conversion and computes the fixed-point steps.
 * Returns 0 when there is nothing safe to convert.
 ******************************************************************************/
static int camConvertPrepare(const camConvertSource* src,
                             const camConvertDest* dst,
                             uint32_t* xStep,
                             uint32_t* yStep)
{
    if ((src == NULL) || (dst == NULL))
    {
        return 0;
    }

    if ((src->data == NULL) || (dst->data == NULL))
    {
        return 0;
    }

    if ((src->width == 0) || (src->height == 0) ||
        (dst->width == 0) || (dst->height == 0))
    {
        return 0;
    }

    *xStep = (uint32_t)(((uint64_t)src->width  << CAM_FP_SHIFT) / dst->width);
    *yStep = (uint32_t)(((uint64_t)src->height << CAM_FP_SHIFT) / dst->height);

    return 1;
}

/*******************************************************************************
 * camSampleYUYVRow
 * Reads the luma and shared chroma for source pixel sx from a YUYV row.
 ******************************************************************************/
static void camSampleYUYVRow(const uint8_t* row, uint32_t sx,
                             int32_t* y, int32_t* u, int32_t* v)
{
    /* Each 4-byte group covers pixels 2n and 2n+1: Y0 U Y1 V. */
    const uint8_t* pair = row + ((sx >> 1) * 4u);

    *y = (int32_t)((sx & 1u) ? pair[2] : pair[0]);
    *u = (int32_t)pair[1];
    *v = (int32_t)pair[3];
}

void Cam_Convert_YUYVToRGB565(const camConvertSource* src, const camConvertDest* dst)
{
    uint32_t xStep = 0;
    uint32_t yStep = 0;
    uint32_t dy;
    uint32_t srcYFp = 0;

    if (!camConvertPrepare(src, dst, &xStep, &yStep))
    {
        return;
    }

    for (dy = 0; dy < dst->height; dy++, srcYFp += yStep)
    {
        uint32_t sy = srcYFp >> CAM_FP_SHIFT;
        const uint8_t* srcRow;
        uint16_t* dstRow;
        uint32_t srcXFp = 0;
        uint32_t dx;

        if (sy >= src->height)
        {
            sy = src->height - 1u;
        }

        srcRow = src->data + ((size_t)sy * src->stride);
        dstRow = (uint16_t*)(void*)(dst->data + ((size_t)dy * dst->stride));

        for (dx = 0; dx < dst->width; dx++, srcXFp += xStep)
        {
            uint32_t sx = srcXFp >> CAM_FP_SHIFT;
            int32_t y;
            int32_t u;
            int32_t v;
            uint8_t r;
            uint8_t g;
            uint8_t b;

            if (sx >= src->width)
            {
                sx = src->width - 1u;
            }

            camSampleYUYVRow(srcRow, sx, &y, &u, &v);
            camYUVToRGB(y, u, v, &r, &g, &b);

            dstRow[dx] = (uint16_t)(((uint16_t)(r & 0xF8) << 8) |
                                    ((uint16_t)(g & 0xFC) << 3) |
                                    ((uint16_t)(b) >> 3));
        }
    }
}

void Cam_Convert_YUYVToARGB8888(const camConvertSource* src, const camConvertDest* dst)
{
    uint32_t xStep = 0;
    uint32_t yStep = 0;
    uint32_t dy;
    uint32_t srcYFp = 0;

    if (!camConvertPrepare(src, dst, &xStep, &yStep))
    {
        return;
    }

    for (dy = 0; dy < dst->height; dy++, srcYFp += yStep)
    {
        uint32_t sy = srcYFp >> CAM_FP_SHIFT;
        const uint8_t* srcRow;
        uint32_t* dstRow;
        uint32_t srcXFp = 0;
        uint32_t dx;

        if (sy >= src->height)
        {
            sy = src->height - 1u;
        }

        srcRow = src->data + ((size_t)sy * src->stride);
        dstRow = (uint32_t*)(void*)(dst->data + ((size_t)dy * dst->stride));

        for (dx = 0; dx < dst->width; dx++, srcXFp += xStep)
        {
            uint32_t sx = srcXFp >> CAM_FP_SHIFT;
            int32_t y;
            int32_t u;
            int32_t v;
            uint8_t r;
            uint8_t g;
            uint8_t b;

            if (sx >= src->width)
            {
                sx = src->width - 1u;
            }

            camSampleYUYVRow(srcRow, sx, &y, &u, &v);
            camYUVToRGB(y, u, v, &r, &g, &b);

            dstRow[dx] = 0xFF000000u |
                         ((uint32_t)r << 16) |
                         ((uint32_t)g << 8) |
                         ((uint32_t)b);
        }
    }
}

void Cam_Convert_YUYVCopy(const camConvertSource* src, const camConvertDest* dst)
{
    uint32_t rows;
    uint32_t rowBytes;
    uint32_t y;

    if ((src == NULL) || (dst == NULL) ||
        (src->data == NULL) || (dst->data == NULL))
    {
        return;
    }

    /* Passthrough cannot scale, so clip to whichever side is smaller. */
    rows     = (src->height < dst->height) ? src->height : dst->height;
    rowBytes = src->width * 2u;

    if (rowBytes > (dst->width * 2u))
    {
        rowBytes = dst->width * 2u;
    }

    if (rowBytes > dst->stride)
    {
        rowBytes = dst->stride;
    }

    for (y = 0; y < rows; y++)
    {
        memcpy(dst->data + ((size_t)y * dst->stride),
               src->data + ((size_t)y * src->stride),
               rowBytes);
    }
}
