/*******************************************************************************
  USB Camera Capture Header

  Company:
    Microchip Technology Inc.

  File Name:
    cam_capture.h

  Summary:
    V4L2 uncompressed (YUYV) frame capture interface for USB UVC cameras.

  Description:
    This module owns the V4L2 side of the camera application and nothing else.
    It knows how to open a UVC device, negotiate an uncompressed YUY2/YUYV
    format, set up memory-mapped streaming buffers, and hand out frames that
    point directly at the driver's mapped memory. There is no copy on the
    capture path.

    The module is deliberately free of any display, Legato or DRM knowledge so
    it can be reused by any front end. Frames are consumed through the
    Cam_Capture_Acquire()/Cam_Capture_Release() pair, and the sink layer
    (cam_sink.h) decides what to do with them.

    Acquire is non-blocking. It is safe to call it from a polled main loop such
    as Legato's SYS_Tasks()/OnUpdate() without stalling rendering: when no
    frame has arrived yet it returns CAM_AGAIN and the caller simply carries on.

  Remarks:
    Only uncompressed YUYV (V4L2_PIX_FMT_YUYV, 4:2:2 packed) is accepted.
    Compressed formats such as MJPEG and H.264 are rejected explicitly rather
    than silently negotiated, so a camera that cannot deliver raw frames fails
    loudly at open time.
 *******************************************************************************/

#ifndef CAM_CAPTURE_H
#define CAM_CAPTURE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Configuration Limits
 ******************************************************************************/
#define CAM_MAX_BUFFERS     8       // Upper bound on mmap'd streaming buffers
#define CAM_MAX_PATH        64      // Device node path length

#define CAM_DEFAULT_DEVICE  "/dev/video0"
#define CAM_DEFAULT_WIDTH   640
#define CAM_DEFAULT_HEIGHT  480
#define CAM_DEFAULT_FPS     30
#define CAM_DEFAULT_BUFFERS 4

/* FourCC of the only pixel format this module accepts, mirrored here so
   callers (and the sink layer) can reason about it without pulling in
   linux/videodev2.h. Matches V4L2_PIX_FMT_YUYV and DRM_FORMAT_YUYV. */
#define CAM_FOURCC_YUYV     0x56595559u     /* 'Y' 'U' 'Y' 'V' */

/*******************************************************************************
 * Result Codes
 ******************************************************************************/
typedef enum
{
    CAM_AGAIN         =  1,     // No frame ready yet (not an error)
    CAM_OK            =  0,
    CAM_ERR_PARAM     = -1,     // Bad argument from the caller
    CAM_ERR_DEVICE    = -2,     // Could not open the device node
    CAM_ERR_CAPS      = -3,     // Not a streaming video-capture device
    CAM_ERR_FORMAT    = -4,     // Device cannot deliver uncompressed YUYV
    CAM_ERR_BUFFERS   = -5,     // Buffer request or mmap failed
    CAM_ERR_STREAM    = -6,     // STREAMON/STREAMOFF failed
    CAM_ERR_IO        = -7,     // Dequeue/queue failed
    CAM_ERR_STATE     = -8,     // Called in the wrong order
    CAM_ERR_UNSUPPORTED = -9    // No backend compiled in for this platform
} camResult;

/*******************************************************************************
 * camFrame
 * A borrowed reference to one captured frame. The data pointer aliases the
 * driver's memory-mapped buffer and stays valid only until the frame is handed
 * back with Cam_Capture_Release().
 ******************************************************************************/
typedef struct
{
    const uint8_t* data;        // YUYV pixel data (borrowed, do not free)
    size_t         size;        // Bytes of valid payload
    uint32_t       width;
    uint32_t       height;
    uint32_t       stride;      // Bytes per row (width * 2 for YUYV)
    uint32_t       sequence;    // Driver frame counter, gaps mean dropped frames
    uint32_t       index;       // Internal buffer index, used by Release()
} camFrame;

/*******************************************************************************
 * camCaptureConfig
 * Requested capture parameters. The driver is allowed to adjust width/height
 * to something it supports; the negotiated values end up in camCapture.
 ******************************************************************************/
typedef struct
{
    const char* devicePath;
    uint32_t    width;
    uint32_t    height;
    uint32_t    fps;            // 0 leaves the driver's default frame interval
    uint32_t    bufferCount;    // Clamped to CAM_MAX_BUFFERS
} camCaptureConfig;

/*******************************************************************************
 * camCapture
 * Capture state. Exposed so it can live in static storage rather than the heap,
 * matching the allocation style used elsewhere in this application.
 ******************************************************************************/
typedef struct
{
    int      fd;
    bool     streaming;

    uint32_t width;             // Negotiated frame width
    uint32_t height;            // Negotiated frame height
    uint32_t stride;            // Negotiated bytes per row
    uint32_t sizeImage;         // Negotiated bytes per frame

    uint32_t bufferCount;
    void*    bufferStart[CAM_MAX_BUFFERS];
    size_t   bufferLength[CAM_MAX_BUFFERS];

    uint32_t framesCaptured;
    uint32_t framesDropped;     // Inferred from gaps in the driver sequence
    uint32_t lastSequence;
    bool     haveLastSequence;

    char     devicePath[CAM_MAX_PATH];
} camCapture;

/*******************************************************************************
 * API
 ******************************************************************************/

/* Fill cfg with the module defaults (CAM_DEFAULT_*). */
void Cam_Capture_ConfigDefault(camCaptureConfig* cfg);

/* Open the device and negotiate uncompressed YUYV. Does not start streaming.
   On success cam->width/height/stride hold the values the driver settled on. */
camResult Cam_Capture_Open(camCapture* cam, const camCaptureConfig* cfg);

/* Map the streaming buffers, queue them and start the stream. */
camResult Cam_Capture_Start(camCapture* cam);

/* Stop the stream and unmap the buffers. The device stays open. */
camResult Cam_Capture_Stop(camCapture* cam);

/* Stop if needed, then close the device and reset all state. */
void Cam_Capture_Close(camCapture* cam);

/* Try to take the next completed frame. Returns CAM_OK and fills frame, or
   CAM_AGAIN when nothing is ready. Never blocks. Every CAM_OK must be paired
   with a Cam_Capture_Release() or the driver will run out of buffers. */
camResult Cam_Capture_Acquire(camCapture* cam, camFrame* frame);

/* Give a frame acquired above back to the driver. */
camResult Cam_Capture_Release(camCapture* cam, const camFrame* frame);

/* True once Start() has succeeded. */
bool Cam_Capture_IsStreaming(const camCapture* cam);

/* Human-readable text for a result code, for logging. */
const char* Cam_Result_ToString(camResult result);

#ifdef __cplusplus
}
#endif

#endif /* CAM_CAPTURE_H */
