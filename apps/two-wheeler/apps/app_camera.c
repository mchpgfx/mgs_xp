/*******************************************************************************
  Camera Application Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    app_camera.c

  Summary:
    Camera preview state machine joining V4L2 capture to a display sink.

  Description:
    Implements the application layer described in app_camera.h. The whole frame
    path is one function, Camera_Tasks(), which does at most one frame of work
    per call:

        acquire (non-blocking)  ->  sink present  ->  release

    Release happens whether or not present succeeded, because a buffer that is
    not requeued is a buffer the driver never gets back -- starve the queue and
    capture stops permanently. That is the one ordering rule that matters here.

    Failures are recoverable by design. Anything that goes wrong parks the
    module in CAMERA_STATE_ERROR with a retry deadline instead of giving up, so
    a camera that is unplugged and plugged back in resumes on its own.
 *******************************************************************************/

#include <stdio.h>
#include <string.h>

#include "app_camera.h"

/*******************************************************************************
 * Module Variables
 ******************************************************************************/
static cameraConfig cameraCfg;
static camCapture   cameraCapture;
static camSink      cameraSink;
static cameraState  cameraCurrentState = CAMERA_STATE_IDLE;

static uint32_t cameraRetryDeadline = 0;    // tickCountMS value to retry at
static uint32_t cameraStatsAnchor = 0;      // tickCountMS at the last FPS window
static uint32_t cameraStatsAnchorFrames = 0;
static uint32_t cameraFps = 0;

/* 1 ms tick maintained by the Home screen's periodic timer. Shared the same
   way app_metrics.c consumes it. */
extern volatile unsigned int tickCountMS;

/*******************************************************************************
 * Local Functions
 ******************************************************************************/

/*******************************************************************************
 * cameraReleaseResources
 * Closes the sink and the capture device. Safe at any point.
 ******************************************************************************/
static void cameraReleaseResources(void)
{
    if ((cameraSink.fn != NULL) && (cameraSink.fn->close != NULL))
    {
        cameraSink.fn->close(&cameraSink);
    }

    memset(&cameraSink, 0, sizeof(cameraSink));

    Cam_Capture_Close(&cameraCapture);
}

/*******************************************************************************
 * cameraEnterError
 * Releases everything and schedules a retry.
 ******************************************************************************/
static void cameraEnterError(const char* what, camResult result)
{
    printf("camera: %s failed: %s, retrying in %u ms\n",
           what, Cam_Result_ToString(result), CAMERA_RETRY_INTERVAL_MS);

    cameraReleaseResources();

    cameraCurrentState  = CAMERA_STATE_ERROR;
    cameraRetryDeadline = (uint32_t)tickCountMS + CAMERA_RETRY_INTERVAL_MS;
}

/*******************************************************************************
 * cameraOpen
 * One attempt at bringing the whole path up: device, then sink, then stream.
 * The sink is bound after the device so it can be sized from the geometry the
 * driver actually settled on rather than the geometry we asked for.
 ******************************************************************************/
static void cameraOpen(void)
{
    camCaptureConfig capCfg;
    camSinkConfig sinkCfg;
    camResult result;

    Cam_Capture_ConfigDefault(&capCfg);
    capCfg.devicePath  = cameraCfg.devicePath;
    capCfg.width       = cameraCfg.width;
    capCfg.height      = cameraCfg.height;
    capCfg.fps         = cameraCfg.fps;
    capCfg.bufferCount = cameraCfg.bufferCount;

    result = Cam_Capture_Open(&cameraCapture, &capCfg);
    if (result != CAM_OK)
    {
        cameraEnterError("capture open", result);
        return;
    }

    memset(&sinkCfg, 0, sizeof(sinkCfg));
    sinkCfg.srcWidth   = cameraCapture.width;
    sinkCfg.srcHeight  = cameraCapture.height;
    sinkCfg.destX      = cameraCfg.destX;
    sinkCfg.destY      = cameraCfg.destY;
    sinkCfg.destWidth  = cameraCfg.destWidth;
    sinkCfg.destHeight = cameraCfg.destHeight;
    sinkCfg.alpha      = cameraCfg.alpha;

    result = Cam_Sink_Open(&cameraSink, cameraCfg.sinkType, &sinkCfg);
    if (result != CAM_OK)
    {
        cameraEnterError("sink open", result);
        return;
    }

    result = Cam_Capture_Start(&cameraCapture);
    if (result != CAM_OK)
    {
        cameraEnterError("capture start", result);
        return;
    }

    cameraCurrentState      = CAMERA_STATE_STREAMING;
    cameraStatsAnchor       = (uint32_t)tickCountMS;
    cameraStatsAnchorFrames = 0;
    cameraFps               = 0;

    printf("camera: streaming %ux%u via '%s' sink\n",
           cameraCapture.width, cameraCapture.height,
           Cam_Sink_TypeToString(cameraSink.type));
}

/*******************************************************************************
 * cameraPumpFrame
 * Moves at most one frame from the driver to the sink.
 ******************************************************************************/
static void cameraPumpFrame(void)
{
    camFrame frame;
    camResult acquired;
    camResult presented;

    acquired = Cam_Capture_Acquire(&cameraCapture, &frame);

    if (acquired == CAM_AGAIN)
    {
        return;     /* Nothing ready. Normal, and cheap. */
    }

    if (acquired != CAM_OK)
    {
        cameraEnterError("frame acquire", acquired);
        return;
    }

    presented = CAM_OK;

    if ((cameraSink.fn != NULL) && (cameraSink.fn->present != NULL))
    {
        presented = cameraSink.fn->present(&cameraSink, &frame);
    }

    /* Requeue unconditionally: holding a buffer back on a present error would
       shrink the driver's queue until capture stalls for good. */
    (void)Cam_Capture_Release(&cameraCapture, &frame);

    if (presented != CAM_OK)
    {
        cameraEnterError("frame present", presented);
    }
}

/*******************************************************************************
 * cameraUpdateStats
 * Recomputes the presented-frames-per-second figure once per second.
 ******************************************************************************/
static void cameraUpdateStats(void)
{
    uint32_t now = (uint32_t)tickCountMS;
    uint32_t elapsed = now - cameraStatsAnchor;

    if (elapsed < CAMERA_STATS_INTERVAL_MS)
    {
        return;
    }

    /* Scale to a per-second rate in case the window overran. */
    cameraFps = ((cameraSink.framesPresented - cameraStatsAnchorFrames) * 1000u) / elapsed;

    cameraStatsAnchor       = now;
    cameraStatsAnchorFrames = cameraSink.framesPresented;
}

/*******************************************************************************
 * Public API
 ******************************************************************************/

void Camera_ConfigDefault(cameraConfig* cfg)
{
    if (cfg == NULL)
    {
        return;
    }

    memset(cfg, 0, sizeof(*cfg));

    cfg->devicePath  = CAM_DEFAULT_DEVICE;
    cfg->width       = CAM_DEFAULT_WIDTH;
    cfg->height      = CAM_DEFAULT_HEIGHT;
    cfg->fps         = CAM_DEFAULT_FPS;
    cfg->bufferCount = CAM_DEFAULT_BUFFERS;

    cfg->sinkType    = CAM_SINK_AUTO;
    cfg->destX       = 0;
    cfg->destY       = 0;
    cfg->destWidth   = 0;      /* Native size, no scaling. */
    cfg->destHeight  = 0;
    cfg->alpha       = 255u;
}

void Camera_Start(const cameraConfig* cfg)
{
    if (cfg == NULL)
    {
        return;
    }

    /* Restart cleanly so a changed geometry or sink type takes effect. */
    Camera_Stop();

    cameraCfg = *cfg;

    if (cameraCfg.devicePath == NULL)
    {
        cameraCfg.devicePath = CAM_DEFAULT_DEVICE;
    }

    cameraCurrentState = CAMERA_STATE_OPENING;
}

void Camera_Stop(void)
{
    if (cameraCurrentState == CAMERA_STATE_IDLE)
    {
        return;
    }

    if (Cam_Capture_IsStreaming(&cameraCapture))
    {
        printf("camera: stopping after %u frames (%u presented, %u dropped)\n",
               cameraCapture.framesCaptured,
               cameraSink.framesPresented,
               cameraCapture.framesDropped);
    }

    cameraReleaseResources();

    cameraCurrentState      = CAMERA_STATE_IDLE;
    cameraFps               = 0;
    cameraStatsAnchorFrames = 0;
}

void Camera_Tasks(void)
{
    switch (cameraCurrentState)
    {
        case CAMERA_STATE_IDLE:
            break;

        case CAMERA_STATE_OPENING:
            cameraOpen();
            break;

        case CAMERA_STATE_STREAMING:
            cameraPumpFrame();
            cameraUpdateStats();
            break;

        case CAMERA_STATE_ERROR:
            /* Unsigned difference handles tick wraparound correctly. */
            if (((uint32_t)tickCountMS - cameraRetryDeadline) < 0x80000000u)
            {
                cameraCurrentState = CAMERA_STATE_OPENING;
            }
            break;

        default:
            cameraCurrentState = CAMERA_STATE_IDLE;
            break;
    }
}

bool Camera_IsStreaming(void)
{
    return (cameraCurrentState == CAMERA_STATE_STREAMING);
}

cameraState Camera_GetState(void)
{
    return cameraCurrentState;
}

void Camera_GetStats(cameraStats* stats)
{
    if (stats == NULL)
    {
        return;
    }

    stats->framesCaptured  = cameraCapture.framesCaptured;
    stats->framesPresented = cameraSink.framesPresented;
    stats->framesDropped   = cameraCapture.framesDropped;
    stats->fps             = cameraFps;
    stats->nativeYUYV      = cameraSink.nativeYUYV;
}

camSinkType Camera_GetSinkType(void)
{
    return cameraSink.type;
}
