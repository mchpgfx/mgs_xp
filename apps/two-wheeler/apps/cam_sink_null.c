/*******************************************************************************
  Camera Frame Sink - Null

  Company:
    Microchip Technology Inc.

  File Name:
    cam_sink_null.c

  Summary:
    Discards frames while keeping capture statistics.

  Description:
    The sink of last resort. It accepts every frame and throws it away, which
    makes the whole capture path -- device negotiation, buffer setup, streaming,
    dequeue and requeue -- exercisable on a build with no display target, such
    as the host SDL2 simulator build where there is no DRM overlay plane and no
    framebuffer to write into.

    It also serves as the reference for what a sink has to do: implement
    present() and close(), and nothing else.

  Remarks:
    Because it does no per-pixel work, the frame rate it reports is an upper
    bound on what the capture layer can deliver, which is useful for telling a
    slow camera apart from a slow conversion.
 *******************************************************************************/

#include <stdio.h>
#include <string.h>

#include "cam_sink.h"

/*******************************************************************************
 * Backend State
 ******************************************************************************/
typedef struct
{
    uint32_t srcWidth;
    uint32_t srcHeight;
    uint32_t lastReportFrame;    // Frame count at the last log line
} camNullSink;

static camNullSink nullSink;

/* Log a line every this many frames so the output stays readable. */
#define CAM_NULL_REPORT_INTERVAL 120u

static camResult camNullPresent(camSink* sink, const camFrame* frame)
{
    camNullSink* state;

    if ((sink == NULL) || (frame == NULL) || (sink->impl == NULL))
    {
        return CAM_ERR_PARAM;
    }

    state = (camNullSink*)sink->impl;

    sink->framesPresented++;

    if ((sink->framesPresented - state->lastReportFrame) >= CAM_NULL_REPORT_INTERVAL)
    {
        state->lastReportFrame = sink->framesPresented;
        printf("camera: null sink discarded %u frames (%ux%u, seq %u)\n",
               sink->framesPresented, frame->width, frame->height, frame->sequence);
    }

    return CAM_OK;
}

static void camNullClose(camSink* sink)
{
    if ((sink == NULL) || (sink->impl == NULL))
    {
        return;
    }

    memset(sink->impl, 0, sizeof(camNullSink));

    sink->impl = NULL;
    sink->fn   = NULL;
    sink->open = false;
}

static const camSinkVTable camNullVTable =
{
    "null",
    camNullPresent,
    camNullClose
};

camResult Cam_Sink_Null_Open(camSink* sink, const camSinkConfig* cfg)
{
    if ((sink == NULL) || (cfg == NULL))
    {
        return CAM_ERR_PARAM;
    }

    memset(&nullSink, 0, sizeof(nullSink));

    nullSink.srcWidth  = cfg->srcWidth;
    nullSink.srcHeight = cfg->srcHeight;

    sink->fn         = &camNullVTable;
    sink->impl       = &nullSink;
    sink->nativeYUYV = false;

    return CAM_OK;
}
