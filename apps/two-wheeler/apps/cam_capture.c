/*******************************************************************************
  USB Camera Capture Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    cam_capture.c

  Summary:
    V4L2 uncompressed (YUYV) frame capture for USB UVC cameras.

  Description:
    Implements the capture half of the camera application:

    - Open: opens the device node non-blocking, verifies it is a streaming
      video-capture device, enumerates the offered pixel formats and insists on
      uncompressed YUYV. If the camera only offers compressed formats the
      failure is reported rather than worked around.

    - Start: requests V4L2_MEMORY_MMAP buffers, maps each one, queues them all
      and turns the stream on.

    - Acquire/Release: a non-blocking dequeue/queue pair. Frames are borrowed
      references into the mapped buffers, so nothing is copied here.

    Dropped frames are inferred from gaps in the driver's sequence counter,
    which is a useful signal that the consumer is not keeping up.
 *******************************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <linux/videodev2.h>

#include "cam_capture.h"

/*******************************************************************************
 * Local Helpers
 ******************************************************************************/

/*******************************************************************************
 * camIoctl
 * ioctl() wrapper that retries when interrupted by a signal. The application
 * runs a 1 ms periodic timer, so EINTR is common enough to matter here.
 ******************************************************************************/
static int camIoctl(int fd, unsigned long request, void* arg)
{
    int result;

    do
    {
        result = ioctl(fd, request, arg);
    }
    while ((result == -1) && (errno == EINTR));

    return result;
}

/*******************************************************************************
 * camFourCCToString
 * Renders a V4L2/DRM FourCC into a caller-supplied 5-byte buffer for logging.
 ******************************************************************************/
static void camFourCCToString(uint32_t fourcc, char* out)
{
    out[0] = (char)((fourcc >>  0) & 0xFF);
    out[1] = (char)((fourcc >>  8) & 0xFF);
    out[2] = (char)((fourcc >> 16) & 0xFF);
    out[3] = (char)((fourcc >> 24) & 0xFF);
    out[4] = '\0';
}

/*******************************************************************************
 * camCheckYUYVOffered
 * Walks VIDIOC_ENUM_FMT looking for uncompressed YUYV. Logs everything the
 * device offers when YUYV is missing, which is the information needed to work
 * out whether the camera is MJPEG-only.
 ******************************************************************************/
static bool camCheckYUYVOffered(int fd)
{
    struct v4l2_fmtdesc desc;
    char fourcc[5];
    bool found = false;

    memset(&desc, 0, sizeof(desc));
    desc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    while (camIoctl(fd, VIDIOC_ENUM_FMT, &desc) == 0)
    {
        if (desc.pixelformat == V4L2_PIX_FMT_YUYV)
        {
            found = true;
        }

        desc.index++;
    }

    if (!found)
    {
        /* Re-walk the list so the log shows what the camera can actually do. */
        memset(&desc, 0, sizeof(desc));
        desc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

        printf("camera: device does not offer uncompressed YUYV. Offered:\n");

        while (camIoctl(fd, VIDIOC_ENUM_FMT, &desc) == 0)
        {
            camFourCCToString(desc.pixelformat, fourcc);
            printf("camera:   [%u] %s%s\n",
                   desc.index,
                   fourcc,
                   (desc.flags & V4L2_FMT_FLAG_COMPRESSED) ? " (compressed)" : "");
            desc.index++;
        }
    }

    return found;
}

/*******************************************************************************
 * camUnmapBuffers
 * Unmaps every buffer that is currently mapped. Safe to call repeatedly.
 ******************************************************************************/
static void camUnmapBuffers(camCapture* cam)
{
    uint32_t i;

    for (i = 0; i < CAM_MAX_BUFFERS; i++)
    {
        if (cam->bufferStart[i] != NULL)
        {
            munmap(cam->bufferStart[i], cam->bufferLength[i]);
            cam->bufferStart[i] = NULL;
            cam->bufferLength[i] = 0;
        }
    }

    cam->bufferCount = 0;
}

/*******************************************************************************
 * Public API
 ******************************************************************************/

void Cam_Capture_ConfigDefault(camCaptureConfig* cfg)
{
    if (cfg == NULL)
    {
        return;
    }

    cfg->devicePath  = CAM_DEFAULT_DEVICE;
    cfg->width       = CAM_DEFAULT_WIDTH;
    cfg->height      = CAM_DEFAULT_HEIGHT;
    cfg->fps         = CAM_DEFAULT_FPS;
    cfg->bufferCount = CAM_DEFAULT_BUFFERS;
}

camResult Cam_Capture_Open(camCapture* cam, const camCaptureConfig* cfg)
{
    struct v4l2_capability caps;
    struct v4l2_format fmt;
    struct v4l2_streamparm parm;
    const char* path;
    char fourcc[5];

    if ((cam == NULL) || (cfg == NULL))
    {
        return CAM_ERR_PARAM;
    }

    memset(cam, 0, sizeof(*cam));
    cam->fd = -1;

    path = (cfg->devicePath != NULL) ? cfg->devicePath : CAM_DEFAULT_DEVICE;
    snprintf(cam->devicePath, sizeof(cam->devicePath), "%s", path);

    /* O_NONBLOCK keeps VIDIOC_DQBUF from stalling the Legato main loop. */
    cam->fd = open(cam->devicePath, O_RDWR | O_NONBLOCK);
    if (cam->fd < 0)
    {
        printf("camera: open('%s') failed: %s\n", cam->devicePath, strerror(errno));
        return CAM_ERR_DEVICE;
    }

    memset(&caps, 0, sizeof(caps));
    if (camIoctl(cam->fd, VIDIOC_QUERYCAP, &caps) < 0)
    {
        printf("camera: VIDIOC_QUERYCAP failed: %s\n", strerror(errno));
        close(cam->fd);
        cam->fd = -1;
        return CAM_ERR_CAPS;
    }

    if ((caps.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0)
    {
        printf("camera: '%s' is not a video capture device\n", cam->devicePath);
        close(cam->fd);
        cam->fd = -1;
        return CAM_ERR_CAPS;
    }

    if ((caps.capabilities & V4L2_CAP_STREAMING) == 0)
    {
        printf("camera: '%s' does not support streaming I/O\n", cam->devicePath);
        close(cam->fd);
        cam->fd = -1;
        return CAM_ERR_CAPS;
    }

    printf("camera: '%s' driver=%s card=%s\n",
           cam->devicePath, (const char*)caps.driver, (const char*)caps.card);

    /* Insist on an uncompressed format before trying to set one, so the
       diagnostic names the real problem on MJPEG-only cameras. */
    if (!camCheckYUYVOffered(cam->fd))
    {
        close(cam->fd);
        cam->fd = -1;
        return CAM_ERR_FORMAT;
    }

    memset(&fmt, 0, sizeof(fmt));
    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = cfg->width;
    fmt.fmt.pix.height      = cfg->height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.field       = V4L2_FIELD_ANY;

    if (camIoctl(cam->fd, VIDIOC_S_FMT, &fmt) < 0)
    {
        printf("camera: VIDIOC_S_FMT failed: %s\n", strerror(errno));
        close(cam->fd);
        cam->fd = -1;
        return CAM_ERR_FORMAT;
    }

    /* The driver may adjust the geometry, but it must not change the format
       out from under us -- that would hand us compressed data. */
    if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_YUYV)
    {
        camFourCCToString(fmt.fmt.pix.pixelformat, fourcc);
        printf("camera: driver substituted format %s for YUYV\n", fourcc);
        close(cam->fd);
        cam->fd = -1;
        return CAM_ERR_FORMAT;
    }

    cam->width     = fmt.fmt.pix.width;
    cam->height    = fmt.fmt.pix.height;
    cam->stride    = fmt.fmt.pix.bytesperline;
    cam->sizeImage = fmt.fmt.pix.sizeimage;

    /* Some drivers leave bytesperline at zero for packed formats. */
    if (cam->stride == 0)
    {
        cam->stride = cam->width * 2u;
    }

    if (cam->sizeImage == 0)
    {
        cam->sizeImage = cam->stride * cam->height;
    }

    if ((cfg->width != cam->width) || (cfg->height != cam->height))
    {
        printf("camera: requested %ux%u, driver chose %ux%u\n",
               cfg->width, cfg->height, cam->width, cam->height);
    }

    /* Frame rate is best-effort: not every UVC device implements S_PARM. */
    if (cfg->fps > 0)
    {
        memset(&parm, 0, sizeof(parm));
        parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        parm.parm.capture.timeperframe.numerator   = 1;
        parm.parm.capture.timeperframe.denominator = cfg->fps;

        if (camIoctl(cam->fd, VIDIOC_S_PARM, &parm) < 0)
        {
            printf("camera: VIDIOC_S_PARM (%u fps) not honoured: %s\n",
                   cfg->fps, strerror(errno));
        }
    }

    cam->bufferCount = (cfg->bufferCount > 0) ? cfg->bufferCount : CAM_DEFAULT_BUFFERS;
    if (cam->bufferCount > CAM_MAX_BUFFERS)
    {
        cam->bufferCount = CAM_MAX_BUFFERS;
    }

    printf("camera: YUYV %ux%u stride=%u size=%u\n",
           cam->width, cam->height, cam->stride, cam->sizeImage);

    return CAM_OK;
}

camResult Cam_Capture_Start(camCapture* cam)
{
    struct v4l2_requestbuffers req;
    struct v4l2_buffer buf;
    enum v4l2_buf_type type;
    uint32_t requested;
    uint32_t i;

    if ((cam == NULL) || (cam->fd < 0))
    {
        return CAM_ERR_STATE;
    }

    if (cam->streaming)
    {
        return CAM_OK;
    }

    requested = cam->bufferCount;

    memset(&req, 0, sizeof(req));
    req.count  = requested;
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (camIoctl(cam->fd, VIDIOC_REQBUFS, &req) < 0)
    {
        printf("camera: VIDIOC_REQBUFS failed: %s\n", strerror(errno));
        return CAM_ERR_BUFFERS;
    }

    if (req.count < 2)
    {
        printf("camera: driver granted only %u buffers, need at least 2\n", req.count);
        return CAM_ERR_BUFFERS;
    }

    cam->bufferCount = (req.count > CAM_MAX_BUFFERS) ? CAM_MAX_BUFFERS : req.count;

    for (i = 0; i < cam->bufferCount; i++)
    {
        memset(&buf, 0, sizeof(buf));
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = i;

        if (camIoctl(cam->fd, VIDIOC_QUERYBUF, &buf) < 0)
        {
            printf("camera: VIDIOC_QUERYBUF(%u) failed: %s\n", i, strerror(errno));
            camUnmapBuffers(cam);
            return CAM_ERR_BUFFERS;
        }

        cam->bufferLength[i] = buf.length;
        cam->bufferStart[i]  = mmap(NULL, buf.length,
                                    PROT_READ | PROT_WRITE, MAP_SHARED,
                                    cam->fd, (off_t)buf.m.offset);

        if (cam->bufferStart[i] == MAP_FAILED)
        {
            printf("camera: mmap(%u) failed: %s\n", i, strerror(errno));
            cam->bufferStart[i] = NULL;
            cam->bufferLength[i] = 0;
            camUnmapBuffers(cam);
            return CAM_ERR_BUFFERS;
        }
    }

    /* Hand every buffer to the driver before turning the stream on. */
    for (i = 0; i < cam->bufferCount; i++)
    {
        memset(&buf, 0, sizeof(buf));
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = i;

        if (camIoctl(cam->fd, VIDIOC_QBUF, &buf) < 0)
        {
            printf("camera: VIDIOC_QBUF(%u) failed: %s\n", i, strerror(errno));
            camUnmapBuffers(cam);
            return CAM_ERR_BUFFERS;
        }
    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (camIoctl(cam->fd, VIDIOC_STREAMON, &type) < 0)
    {
        printf("camera: VIDIOC_STREAMON failed: %s\n", strerror(errno));
        camUnmapBuffers(cam);
        return CAM_ERR_STREAM;
    }

    cam->streaming        = true;
    cam->framesCaptured   = 0;
    cam->framesDropped    = 0;
    cam->haveLastSequence = false;
    cam->lastSequence     = 0;

    printf("camera: streaming with %u buffers\n", cam->bufferCount);

    return CAM_OK;
}

camResult Cam_Capture_Stop(camCapture* cam)
{
    enum v4l2_buf_type type;
    camResult result = CAM_OK;

    if ((cam == NULL) || (cam->fd < 0))
    {
        return CAM_ERR_STATE;
    }

    if (!cam->streaming)
    {
        return CAM_OK;
    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (camIoctl(cam->fd, VIDIOC_STREAMOFF, &type) < 0)
    {
        printf("camera: VIDIOC_STREAMOFF failed: %s\n", strerror(errno));
        result = CAM_ERR_STREAM;
    }

    cam->streaming = false;
    camUnmapBuffers(cam);

    return result;
}

void Cam_Capture_Close(camCapture* cam)
{
    if (cam == NULL)
    {
        return;
    }

    if (cam->fd >= 0)
    {
        (void)Cam_Capture_Stop(cam);
        close(cam->fd);
    }

    memset(cam, 0, sizeof(*cam));
    cam->fd = -1;
}

camResult Cam_Capture_Acquire(camCapture* cam, camFrame* frame)
{
    struct v4l2_buffer buf;
    struct pollfd pfd;

    if ((cam == NULL) || (frame == NULL))
    {
        return CAM_ERR_PARAM;
    }

    if (!cam->streaming)
    {
        return CAM_ERR_STATE;
    }

    /* Zero timeout: ask whether a frame is ready, never wait for one. */
    pfd.fd      = cam->fd;
    pfd.events  = POLLIN;
    pfd.revents = 0;

    if (poll(&pfd, 1, 0) <= 0)
    {
        return CAM_AGAIN;
    }

    if ((pfd.revents & POLLIN) == 0)
    {
        return CAM_AGAIN;
    }

    memset(&buf, 0, sizeof(buf));
    buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (camIoctl(cam->fd, VIDIOC_DQBUF, &buf) < 0)
    {
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
        {
            return CAM_AGAIN;
        }

        printf("camera: VIDIOC_DQBUF failed: %s\n", strerror(errno));
        return CAM_ERR_IO;
    }

    if (buf.index >= cam->bufferCount)
    {
        printf("camera: driver returned out-of-range buffer index %u\n", buf.index);
        return CAM_ERR_IO;
    }

    /* A jump in the driver's sequence counter means frames went by while we
       were busy elsewhere. Worth counting: it is the main symptom of a
       consumer that cannot keep up. */
    if (cam->haveLastSequence && (buf.sequence > (cam->lastSequence + 1u)))
    {
        cam->framesDropped += buf.sequence - cam->lastSequence - 1u;
    }

    cam->lastSequence     = buf.sequence;
    cam->haveLastSequence = true;
    cam->framesCaptured++;

    frame->data     = (const uint8_t*)cam->bufferStart[buf.index];
    frame->size     = (buf.bytesused > 0) ? buf.bytesused : cam->bufferLength[buf.index];
    frame->width    = cam->width;
    frame->height   = cam->height;
    frame->stride   = cam->stride;
    frame->sequence = buf.sequence;
    frame->index    = buf.index;

    return CAM_OK;
}

camResult Cam_Capture_Release(camCapture* cam, const camFrame* frame)
{
    struct v4l2_buffer buf;

    if ((cam == NULL) || (frame == NULL))
    {
        return CAM_ERR_PARAM;
    }

    if (!cam->streaming)
    {
        return CAM_ERR_STATE;
    }

    if (frame->index >= cam->bufferCount)
    {
        return CAM_ERR_PARAM;
    }

    memset(&buf, 0, sizeof(buf));
    buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index  = frame->index;

    if (camIoctl(cam->fd, VIDIOC_QBUF, &buf) < 0)
    {
        printf("camera: VIDIOC_QBUF(%u) failed: %s\n", frame->index, strerror(errno));
        return CAM_ERR_IO;
    }

    return CAM_OK;
}

bool Cam_Capture_IsStreaming(const camCapture* cam)
{
    return (cam != NULL) && cam->streaming;
}

const char* Cam_Result_ToString(camResult result)
{
    switch (result)
    {
        case CAM_AGAIN:           return "no frame ready";
        case CAM_OK:              return "ok";
        case CAM_ERR_PARAM:       return "invalid parameter";
        case CAM_ERR_DEVICE:      return "cannot open device";
        case CAM_ERR_CAPS:        return "unsupported device capabilities";
        case CAM_ERR_FORMAT:      return "no uncompressed YUYV format";
        case CAM_ERR_BUFFERS:     return "buffer setup failed";
        case CAM_ERR_STREAM:      return "stream control failed";
        case CAM_ERR_IO:          return "frame I/O failed";
        case CAM_ERR_STATE:       return "invalid state";
        case CAM_ERR_UNSUPPORTED: return "unsupported on this platform";
        default:                  return "unknown error";
    }
}
