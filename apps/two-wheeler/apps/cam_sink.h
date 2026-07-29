/*******************************************************************************
  Camera Frame Sink Header

  Company:
    Microchip Technology Inc.

  File Name:
    cam_sink.h

  Summary:
    Abstract destination for captured camera frames, plus backend selection.

  Description:
    A sink is where frames go. Keeping this behind a vtable is what lets the
    capture layer stay identical across display targets: the DRM backend hands
    YUYV to an LCD controller overlay plane, the fbdev backend converts to the
    framebuffer's RGB format, and the null backend just counts frames so the
    application still runs on a host build with no display target.

    The interface follows the leWidget convention used throughout this
    application -- call through sink->fn->method(sink, ...) -- so it reads the
    same way as the surrounding Legato code.

    Backend selection is a runtime decision made by Cam_Sink_Open() with
    CAM_SINK_AUTO: it tries DRM, then fbdev, then null, and reports which one
    it bound. Compile-time availability is handled by each backend, so an
    x86 host build without libdrm simply has fewer candidates.

  Remarks:
    One sink instance is supported per process. Each backend keeps its state in
    file-scope storage rather than the heap, matching the allocation style of
    this application; sink->impl points at that state.
 *******************************************************************************/

#ifndef CAM_SINK_H
#define CAM_SINK_H

#include <stdbool.h>
#include <stdint.h>

#include "cam_capture.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * camSinkType
 * Which display backend to use. CAM_SINK_AUTO picks the best available.
 ******************************************************************************/
typedef enum
{
    CAM_SINK_AUTO = 0,
    CAM_SINK_DRM,       // DRM/KMS overlay plane (hardware CSC and scaling)
    CAM_SINK_FBDEV,     // Linux framebuffer, software conversion
    CAM_SINK_NULL       // Discard frames, keep statistics only
} camSinkType;

/*******************************************************************************
 * camSinkConfig
 * Where the preview goes on screen. A zero destWidth/destHeight means "use the
 * camera's native frame size", i.e. no scaling.
 ******************************************************************************/
typedef struct
{
    uint32_t srcWidth;      // Camera frame width
    uint32_t srcHeight;     // Camera frame height

    int32_t  destX;         // Screen position of the preview
    int32_t  destY;
    uint32_t destWidth;     // 0 => srcWidth
    uint32_t destHeight;    // 0 => srcHeight

    uint32_t alpha;         // 0..255, honoured by backends that support it
} camSinkConfig;

/*******************************************************************************
 * camSink
 * A bound sink. Created by Cam_Sink_Open(), used through fn->, released by
 * fn->close().
 ******************************************************************************/
typedef struct camSink camSink;

typedef struct
{
    const char* name;

    /* Present one frame. Frame data stays owned by the capture layer and is
       only valid for the duration of the call. */
    camResult (*present)(camSink* sink, const camFrame* frame);

    /* Release the display resources. Safe to call on a closed sink. */
    void      (*close)(camSink* sink);
} camSinkVTable;

struct camSink
{
    const camSinkVTable* fn;
    void*                impl;       // Backend-private state
    camSinkType          type;
    bool                 open;

    /* True when the backend consumes YUYV directly with no colour conversion,
       which is the zero-CPU path worth knowing about for diagnostics. */
    bool                 nativeYUYV;

    uint32_t             framesPresented;
};

/*******************************************************************************
 * Cam_Sink_Open
 * Binds sink to a backend and prepares it for the given geometry.
 * Pass CAM_SINK_AUTO to let the module choose.
 ******************************************************************************/
camResult Cam_Sink_Open(camSink* sink, camSinkType type, const camSinkConfig* cfg);

/*******************************************************************************
 * Cam_Sink_TypeToString
 * Backend name for logging.
 ******************************************************************************/
const char* Cam_Sink_TypeToString(camSinkType type);

/*******************************************************************************
 * Backend entry points
 * Each returns CAM_ERR_UNSUPPORTED when its backend is not compiled in or the
 * underlying device is unavailable, which is what lets Cam_Sink_Open() fall
 * through to the next candidate.
 ******************************************************************************/
camResult Cam_Sink_DRM_Open(camSink* sink, const camSinkConfig* cfg);
camResult Cam_Sink_FBDev_Open(camSink* sink, const camSinkConfig* cfg);
camResult Cam_Sink_Null_Open(camSink* sink, const camSinkConfig* cfg);

#ifdef __cplusplus
}
#endif

#endif /* CAM_SINK_H */
