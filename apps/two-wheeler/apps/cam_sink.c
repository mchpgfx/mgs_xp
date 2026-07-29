/*******************************************************************************
  Camera Frame Sink Selection

  Company:
    Microchip Technology Inc.

  File Name:
    cam_sink.c

  Summary:
    Runtime selection of the camera frame sink backend.

  Description:
    Holds only the factory. Each backend lives in its own translation unit and
    reports whether it can run, so adding a target means adding a file and one
    entry to the candidate list below -- no changes to the capture layer or the
    application layer.

    Order matters: DRM first because an overlay plane gives hardware colour
    conversion and scaling at no CPU cost, fbdev next as the software fallback,
    and null last so the application still runs where neither exists.
 *******************************************************************************/

#include <stdio.h>
#include <string.h>

#include "cam_sink.h"

const char* Cam_Sink_TypeToString(camSinkType type)
{
    switch (type)
    {
        case CAM_SINK_AUTO:  return "auto";
        case CAM_SINK_DRM:   return "drm";
        case CAM_SINK_FBDEV: return "fbdev";
        case CAM_SINK_NULL:  return "null";
        default:             return "unknown";
    }
}

camResult Cam_Sink_Open(camSink* sink, camSinkType type, const camSinkConfig* cfg)
{
    /* Candidate order for CAM_SINK_AUTO. */
    static const camSinkType candidates[] =
    {
        CAM_SINK_DRM,
        CAM_SINK_FBDEV,
        CAM_SINK_NULL
    };

    const camSinkType* tryList;
    unsigned int tryCount;
    unsigned int i;

    if ((sink == NULL) || (cfg == NULL))
    {
        return CAM_ERR_PARAM;
    }

    if ((cfg->srcWidth == 0) || (cfg->srcHeight == 0))
    {
        return CAM_ERR_PARAM;
    }

    memset(sink, 0, sizeof(*sink));

    if (type == CAM_SINK_AUTO)
    {
        tryList  = candidates;
        tryCount = (unsigned int)(sizeof(candidates) / sizeof(candidates[0]));
    }
    else
    {
        tryList  = &type;
        tryCount = 1u;
    }

    for (i = 0; i < tryCount; i++)
    {
        camResult result;

        switch (tryList[i])
        {
            case CAM_SINK_DRM:
                result = Cam_Sink_DRM_Open(sink, cfg);
                break;

            case CAM_SINK_FBDEV:
                result = Cam_Sink_FBDev_Open(sink, cfg);
                break;

            case CAM_SINK_NULL:
                result = Cam_Sink_Null_Open(sink, cfg);
                break;

            default:
                result = CAM_ERR_PARAM;
                break;
        }

        if (result == CAM_OK)
        {
            sink->type = tryList[i];
            sink->open = true;

            printf("camera: sink '%s' bound, %ux%u -> %ux%u at (%d,%d)%s\n",
                   Cam_Sink_TypeToString(sink->type),
                   cfg->srcWidth, cfg->srcHeight,
                   (cfg->destWidth  != 0) ? cfg->destWidth  : cfg->srcWidth,
                   (cfg->destHeight != 0) ? cfg->destHeight : cfg->srcHeight,
                   cfg->destX, cfg->destY,
                   sink->nativeYUYV ? ", native YUYV (no conversion)" : "");

            return CAM_OK;
        }

        /* Only fall through to the next candidate in AUTO mode. */
        if (type != CAM_SINK_AUTO)
        {
            return result;
        }

        printf("camera: sink '%s' unavailable (%s)\n",
               Cam_Sink_TypeToString(tryList[i]), Cam_Result_ToString(result));
    }

    return CAM_ERR_UNSUPPORTED;
}
