/*******************************************************************************
  Camera Application Header

  Company:
    Microchip Technology Inc.

  File Name:
    app_camera.h

  Summary:
    Camera preview application: capture, sink binding and per-frame pumping.

  Description:
    This is the application layer of the camera feature. It owns the state
    machine and joins the two lower modules together:

        cam_capture.c  ->  app_camera.c  ->  cam_sink_*.c
        (V4L2 YUYV)        (this module)     (DRM / fbdev / null)

    Neither lower module knows about the other, and neither knows about Legato.
    That is what makes the feature reusable: a different screen, or a different
    application in this tree, needs only these five entry points.

    The state machine is non-blocking throughout. Camera_Start() returns
    immediately after opening the device; if the device is missing the module
    lands in CAMERA_STATE_ERROR and retries on a timer rather than blocking or
    aborting, so a camera can be plugged in while the cluster is running.

    Camera_Tasks() must be called regularly from the UI loop. It does at most
    one frame's worth of work per call and returns straight away when no frame
    is ready, so it is safe to call every rendered frame.

  Remarks:
    Single instance. The module keeps its state in file-scope storage, matching
    the style of the other app_* modules here.
 *******************************************************************************/

#ifndef APP_CAMERA_H
#define APP_CAMERA_H

#include <stdbool.h>
#include <stdint.h>

#include "cam_capture.h"
#include "cam_sink.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Configuration
 ******************************************************************************/

/* How long to wait before retrying after a failed open, in milliseconds.
   Long enough not to spam a system with no camera attached, short enough that
   hot-plugging one is picked up promptly. */
#define CAMERA_RETRY_INTERVAL_MS 2000

/* Statistics reporting interval, in milliseconds. */
#define CAMERA_STATS_INTERVAL_MS 1000

/*******************************************************************************
 * cameraState
 ******************************************************************************/
typedef enum
{
    CAMERA_STATE_IDLE = 0,      // Not started
    CAMERA_STATE_OPENING,       // Opening device and binding a sink
    CAMERA_STATE_STREAMING,     // Frames flowing
    CAMERA_STATE_ERROR          // Failed; retrying on CAMERA_RETRY_INTERVAL_MS
} cameraState;

/*******************************************************************************
 * cameraConfig
 * Everything the feature needs to know. Fill with Camera_ConfigDefault() and
 * override what matters.
 ******************************************************************************/
typedef struct
{
    /* Capture side */
    const char* devicePath;     // NULL => CAM_DEFAULT_DEVICE
    uint32_t    width;
    uint32_t    height;
    uint32_t    fps;
    uint32_t    bufferCount;

    /* Display side */
    camSinkType sinkType;       // CAM_SINK_AUTO recommended
    int32_t     destX;
    int32_t     destY;
    uint32_t    destWidth;      // 0 => capture width (no scaling)
    uint32_t    destHeight;     // 0 => capture height
    uint32_t    alpha;          // 0..255
} cameraConfig;

/*******************************************************************************
 * cameraStats
 * Snapshot of the frame path, for on-screen or logged diagnostics.
 ******************************************************************************/
typedef struct
{
    uint32_t framesCaptured;
    uint32_t framesPresented;
    uint32_t framesDropped;     // Inferred from driver sequence gaps
    uint32_t fps;               // Presented frames in the last second
    bool     nativeYUYV;        // True when no software conversion is running
} cameraStats;

/*******************************************************************************
 * API
 ******************************************************************************/

/* Populate cfg with sensible defaults for this application. */
void Camera_ConfigDefault(cameraConfig* cfg);

/* Begin bringing the camera up. Non-blocking: the work completes across
   subsequent Camera_Tasks() calls. Safe to call when already running. */
void Camera_Start(const cameraConfig* cfg);

/* Tear the camera down and release the display resources. Safe to call when
   not running. */
void Camera_Stop(void);

/* Drive the state machine. Call from the UI update loop. Moves at most one
   frame from the camera to the sink per call and never blocks. */
void Camera_Tasks(void);

/* True while frames are actively being presented. */
bool Camera_IsStreaming(void);

/* Current state, for UI feedback. */
cameraState Camera_GetState(void);

/* Copy the current statistics into stats. */
void Camera_GetStats(cameraStats* stats);

/* Which sink backend ended up being used, for diagnostics. */
camSinkType Camera_GetSinkType(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_CAMERA_H */
