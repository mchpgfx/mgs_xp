/*******************************************************************************
  Camera Pixel Format Conversion Header

  Company:
    Microchip Technology Inc.

  File Name:
    cam_convert.h

  Summary:
    YUYV to RGB colour conversion with optional nearest-neighbour scaling.

  Description:
    The preferred camera path on this platform pushes YUYV straight to a display
    overlay plane and lets the LCD controller do the colour-space conversion and
    scaling for free. This module is the software fallback used when the plane
    cannot accept YUYV, and by the fbdev sink where no hardware CSC exists.

    Conversion uses fixed-point BT.601 coefficients. Scaling is nearest
    neighbour with a fixed-point step, chosen because it costs no multiplies or
    divides per pixel and needs no intermediate buffer -- the relevant tradeoff
    on a Cortex-A class part with no GPU in this path.

  Remarks:
    All destination writes are bounds-checked against the destination geometry,
    so a mismatched stride cannot walk off the end of a framebuffer.
 *******************************************************************************/

#ifndef CAM_CONVERT_H
#define CAM_CONVERT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * camConvertRect
 * Describes one side of a conversion: where the pixels live and how big they
 * are. stride is in bytes so callers can hand over a framebuffer row pitch
 * directly without assuming it equals width * bytes-per-pixel.
 ******************************************************************************/
typedef struct
{
    uint8_t* data;
    uint32_t width;
    uint32_t height;
    uint32_t stride;    // Bytes per row
} camConvertDest;

typedef struct
{
    const uint8_t* data;
    uint32_t       width;
    uint32_t       height;
    uint32_t       stride;  // Bytes per row
} camConvertSource;

/*******************************************************************************
 * Cam_Convert_YUYVToRGB565
 * Converts a YUYV 4:2:2 source into a 16-bit RGB565 destination, scaling to
 * the destination geometry when it differs from the source.
 ******************************************************************************/
void Cam_Convert_YUYVToRGB565(const camConvertSource* src, const camConvertDest* dst);

/*******************************************************************************
 * Cam_Convert_YUYVToARGB8888
 * Converts a YUYV 4:2:2 source into a 32-bit ARGB8888 destination (alpha forced
 * opaque), scaling to the destination geometry when it differs from the source.
 ******************************************************************************/
void Cam_Convert_YUYVToARGB8888(const camConvertSource* src, const camConvertDest* dst);

/*******************************************************************************
 * Cam_Convert_YUYVCopy
 * Straight YUYV passthrough with stride correction and clipping, for sinks
 * whose plane consumes YUYV natively but whose row pitch differs from the
 * camera's. No colour conversion happens.
 ******************************************************************************/
void Cam_Convert_YUYVCopy(const camConvertSource* src, const camConvertDest* dst);

#ifdef __cplusplus
}
#endif

#endif /* CAM_CONVERT_H */
