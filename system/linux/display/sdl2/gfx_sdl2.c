/*******************************************************************************
* Copyright (C) 2025 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#include "gfx_sdl2.h"

#include "gfx/legato/legato.h"
#include "gfx/legato/legato_config.h"

#include <SDL2/SDL.h>

/* SDL2 Virtual HWC Driver Configuration Options */
/* SDL2 Timer Subsystem Config */
#define SDL_TIMER_RESOLUTION_MS (1U)

/* SDL2 Video Subsystem Config */
#define SDL_HOR_RES LE_DEFAULT_SCREEN_WIDTH
#define SDL_VER_RES LE_DEFAULT_SCREEN_HEIGHT

#define SDL_DEF_FB_PTR_TYPE uint32_t *

#define SDL_VIRTUAL_LAYERS  LE_LAYER_COUNT

#define SDL_BUFFERS_PER_LAYER 1

/* Check layer parity */
#if LE_DRIVER_LAYER_MODE == 1 && LE_LAYER_COUNT != SDL_VIRTUAL_LAYERS
#error "Simulator and Composer layer counts must match in Driver Layer Mode!"
#endif

/* SDL2 Event Subsystem Config */
#define SDL_TOUCH_HOR_RES SDL_HOR_RES
#define SDL_TOUCH_VER_RES SDL_VER_RES

/* Event Subsystem */
static SDL_Event sdl_event;

#if 0
/* Timer Subsystem */
static SDL_TimerID sdl_timer_id;
SYS_TIME_PLIB_CALLBACK sys_time_plib_cb;

uint32_t GFX_SDL2_TimerCallback(uint32_t interval, void *param)
{
    if (sys_time_plib_cb != NULL)
        sys_time_plib_cb(0, 0);
    return (interval);
}

void GFX_SDL2_TimerStart(void)
{
    sdl_timer_id = SDL_AddTimer(SDL_TIMER_RESOLUTION_MS, GFX_SDL2_TimerCallback, 0);
}

void GFX_SDL2_TimerStop(void)
{
    SDL_RemoveTimer(sdl_timer_id);
}

uint32_t GFX_SDL2_TimerGetFreqHz(void)
{
    return 1000U;
}

void GFX_SDL2_TimerStubCompareSet(uint32_t dummy)
{
}

uint32_t GFX_SDL2_TimerCounterGet(void)
{
    return SDL_GetTicks();
}

void GFX_SDL2_TimerRegisterCallback(SYS_TIME_PLIB_CALLBACK callback, uintptr_t context)
{
    sys_time_plib_cb = callback;
}

const SYS_TIME_PLIB_INTERFACE sdlc_timer_bindings = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)GFX_SDL2_TimerRegisterCallback,
    .timerStart = (SYS_TIME_PLIB_START)GFX_SDL2_TimerStart,
    .timerStop = (SYS_TIME_PLIB_STOP)GFX_SDL2_TimerStop,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)GFX_SDL2_TimerGetFreqHz,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)NULL,
    .timerCompareSet = (SYS_TIME_PLIB_COMPARE_SET)GFX_SDL2_TimerStubCompareSet,
    .timerCounterGet = (SYS_TIME_PLIB_COUNTER_GET)GFX_SDL2_TimerCounterGet,
};

const SYS_TIME_INIT sys_time_init_data =
{
        .timePlib = &sdlc_timer_bindings,
        .hwTimerIntNum = 0,
};

#endif

static int32_t sanitize_mouse(int32_t value, int32_t min, int32_t max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

static void GFX_SDL2_ProcessInput(SDL_Event *sdl_event)
{
    static bool clicked = false;

    switch (sdl_event->type)
    {
    case SDL_MOUSEBUTTONUP:
        if (sdl_event->button.button == SDL_BUTTON_LEFT)
        {
            //SYS_INP_InjectTouchUp(0,
            leInput_InjectTouchUp(0,
                                  sanitize_mouse(sdl_event->motion.x, 0, SDL_TOUCH_HOR_RES),
                                  sanitize_mouse(sdl_event->motion.y, 0, SDL_TOUCH_VER_RES));
            clicked = false;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (sdl_event->button.button == SDL_BUTTON_LEFT)
        {
            //SYS_INP_InjectTouchDown(0,
            leInput_InjectTouchDown(0,
                                  sanitize_mouse(sdl_event->motion.x, 0, SDL_TOUCH_HOR_RES),
                                  sanitize_mouse(sdl_event->motion.y, 0, SDL_TOUCH_VER_RES));
            clicked = true;
        }
        break;
    case SDL_MOUSEMOTION:
        if (clicked)
            //SYS_INP_InjectTouchMove(0,
            leInput_InjectTouchMoved(0,
                                  sanitize_mouse(sdl_event->motion.x, 0, SDL_TOUCH_HOR_RES),
                                  sanitize_mouse(sdl_event->motion.y, 0, SDL_TOUCH_VER_RES));
        break;
    case SDL_FINGERUP:
        //SYS_INP_InjectTouchUp(sdl_event->tfinger.touchId, sdl_event->tfinger.x * SDL_TOUCH_HOR_RES, sdl_event->tfinger.y * SDL_TOUCH_VER_RES);
        leInput_InjectTouchUp(sdl_event->tfinger.touchId, sdl_event->tfinger.x * SDL_TOUCH_HOR_RES, sdl_event->tfinger.y * SDL_TOUCH_VER_RES);
        break;
    case SDL_FINGERDOWN:
        //SYS_INP_InjectTouchDown(sdl_event->tfinger.touchId, sdl_event->tfinger.x * SDL_TOUCH_HOR_RES, sdl_event->tfinger.y * SDL_TOUCH_VER_RES);
        leInput_InjectTouchDown(sdl_event->tfinger.touchId, sdl_event->tfinger.x * SDL_TOUCH_HOR_RES, sdl_event->tfinger.y * SDL_TOUCH_VER_RES);
        break;
    case SDL_FINGERMOTION:
        //SYS_INP_InjectTouchMove(sdl_event->tfinger.touchId, sdl_event->tfinger.x * SDL_TOUCH_HOR_RES, sdl_event->tfinger.y * SDL_TOUCH_VER_RES);
        leInput_InjectTouchMoved(sdl_event->tfinger.touchId, sdl_event->tfinger.x * SDL_TOUCH_HOR_RES, sdl_event->tfinger.y * SDL_TOUCH_VER_RES);
        break;
    case SDL_QUIT:
        exit(0);
    }
}

/* Video Subsystem */
static SDL_Window *sdl_window;
static SDL_Renderer *sdl_renderer;
static SDL_Texture *sdl_texture[SDL_VIRTUAL_LAYERS];
static SDL_Rect texture_rect[SDL_VIRTUAL_LAYERS], render_rect[SDL_VIRTUAL_LAYERS];
uint32_t frame_buffer[SDL_VIRTUAL_LAYERS][SDL_HOR_RES * SDL_VER_RES];

typedef enum
{
    LAYER_UNLOCKED,
    LAYER_LOCKED,
    LAYER_LOCKED_PENDING,
} LAYER_LOCK_STATUS;

typedef enum
{
    INIT = 0,
    DRAW,
    FREEZE
} DRV_STATE;

const char *DRIVER_NAME = "SDL2 Virtual HWC";
static volatile DRV_STATE state;
static gfxRect srcRect, destRect;
static unsigned int vsyncCount = 0;
static unsigned int activeLayer = 0;
static bool vblankSync = false;
volatile int32_t waitForAlphaSetting[SDL_VIRTUAL_LAYERS] = {0};

typedef struct __display_layer
{
    SDL_DEF_FB_PTR_TYPE baseaddr[SDL_BUFFERS_PER_LAYER];
    uint32_t resx;
    uint32_t resy;
    uint32_t startx;
    uint32_t starty;
    uint32_t sizex;
    uint32_t sizey;
    uint32_t stride;
    uint32_t alpha;
    uint32_t pixelformat;
    SDL_BlendMode blendmode;
    bool enabled;
    volatile LAYER_LOCK_STATUS updateLock;
    gfxPixelBuffer pixelBuffer[SDL_BUFFERS_PER_LAYER];
    volatile uint32_t bufferIdx;
} DISPLAY_LAYER;
static DISPLAY_LAYER drvLayer[SDL_VIRTUAL_LAYERS];

static uint32_t getPixelFormatStrideBytes(uint32_t format)
{
    switch (format)
    {
    case SDL_PIXELFORMAT_INDEX1LSB:
    case SDL_PIXELFORMAT_INDEX4LSB:
    case SDL_PIXELFORMAT_INDEX8:
        return sizeof(uint8_t);
        break;
    case SDL_PIXELFORMAT_RGB332:
        return sizeof(uint8_t);
        break;
    case SDL_PIXELFORMAT_RGB565:
    case SDL_PIXELFORMAT_RGBA5551:
        return sizeof(uint16_t);
        break;
    case SDL_PIXELFORMAT_RGB888:
    case SDL_PIXELFORMAT_ARGB8888:
    case SDL_PIXELFORMAT_RGBA8888:
        return sizeof(uint32_t);
        break;
    default:
        return sizeof(uint32_t);
        break;
    }
}

static gfxColorMode getGFXColorModeFromSDLPixelFormat(uint32_t format)
{
    switch (format)
    {
        case SDL_PIXELFORMAT_INDEX8:
            return GFX_COLOR_MODE_GS_8;
        case SDL_PIXELFORMAT_RGB332:
            return GFX_COLOR_MODE_RGB_332;
        case SDL_PIXELFORMAT_RGB565:
            return GFX_COLOR_MODE_RGB_565;
        case SDL_PIXELFORMAT_RGBA5551:
            return GFX_COLOR_MODE_RGBA_5551;
        case SDL_PIXELFORMAT_RGB888:
            return GFX_COLOR_MODE_RGB_888;
        case SDL_PIXELFORMAT_ARGB8888:
            return GFX_COLOR_MODE_ARGB_8888;
        case SDL_PIXELFORMAT_RGBA8888:
        default:
            return GFX_COLOR_MODE_RGBA_8888;
    }
}

static uint32_t getSDLPixelFormatFromGFXColorMode(gfxColorMode mode)
{
    switch (mode)
    {
        case GFX_COLOR_MODE_GS_8:
            return SDL_PIXELFORMAT_INDEX8;
        case GFX_COLOR_MODE_RGB_332:
            return SDL_PIXELFORMAT_RGB332;
        case GFX_COLOR_MODE_RGB_565:
            return SDL_PIXELFORMAT_RGB565;
        case GFX_COLOR_MODE_RGBA_5551:
            return SDL_PIXELFORMAT_RGBA5551;
        case GFX_COLOR_MODE_RGB_888:
            return SDL_PIXELFORMAT_RGB888;
        case GFX_COLOR_MODE_ARGB_8888:
            return SDL_PIXELFORMAT_ARGB8888;
        case GFX_COLOR_MODE_RGBA_8888:
        default:
            return SDL_PIXELFORMAT_RGBA8888;
    }
}

static gfxResult GFX_SDL2_BufferBlit(const gfxPixelBuffer *source,
                                     const gfxRect *rectSrc,
                                     const gfxPixelBuffer *dest,
                                     const gfxRect *rectDest)
{
    void *srcPtr;
    void *destPtr;
    uint32_t row, rowSize;
    unsigned int width, height;
    width = (rectSrc->width < rectDest->width) ? rectSrc->width : rectDest->width;
    height = (rectSrc->height < rectDest->height) ? rectSrc->height : rectDest->height;
    rowSize = width * gfxColorInfoTable[dest->mode].size;

    for (row = 0; row < height; row++)
    {
        srcPtr = gfxPixelBufferOffsetGet(source, rectSrc->x, rectSrc->y + row);
        destPtr = gfxPixelBufferOffsetGet(dest, rectDest->x, rectDest->y + row);

        memcpy(destPtr, srcPtr, rowSize);
    }

    return GFX_SUCCESS;
}

void GFX_SDL2_Update()
{
    switch (state)
    {
    case INIT:
    {
        state = DRAW;
        break;
    }
    case DRAW:
    {
        SDL_RenderClear(sdl_renderer);

        for (uint32_t layerCount = 0; layerCount < SDL_VIRTUAL_LAYERS; layerCount++)
        {
            if (drvLayer[layerCount].enabled == true && drvLayer[layerCount].updateLock != LAYER_LOCKED)
            {
                if (drvLayer[layerCount].updateLock == LAYER_LOCKED_PENDING)
                {
                    drvLayer[layerCount].stride = drvLayer[layerCount].resx * getPixelFormatStrideBytes(drvLayer[layerCount].pixelformat);

                    texture_rect[layerCount].x = drvLayer[layerCount].startx;
                    texture_rect[layerCount].y = drvLayer[layerCount].starty;
                    texture_rect[layerCount].w = drvLayer[layerCount].sizex;
                    texture_rect[layerCount].h = drvLayer[layerCount].sizey;

                    render_rect[layerCount].x = drvLayer[layerCount].startx;
                    render_rect[layerCount].y = drvLayer[layerCount].starty;
                    render_rect[layerCount].w = drvLayer[layerCount].sizex;
                    render_rect[layerCount].h = drvLayer[layerCount].sizey;

                    drvLayer[layerCount].updateLock = LAYER_UNLOCKED;
                }
                SDL_SetTextureAlphaMod(sdl_texture[layerCount], (uint8_t)(drvLayer[layerCount].alpha & 0xff));
                SDL_UpdateTexture(sdl_texture[layerCount], &texture_rect[layerCount], drvLayer[layerCount].baseaddr[0], drvLayer[layerCount].stride);
                SDL_RenderCopy(sdl_renderer, sdl_texture[layerCount], &texture_rect[layerCount], &render_rect[layerCount]);
            }
        }

        SDL_RenderPresent(sdl_renderer);

        while (SDL_PollEvent(&sdl_event))
        {
            GFX_SDL2_ProcessInput(&sdl_event);
        }

        break;
    }
    case FREEZE:
    default:
        break;
    }
}

bool GFX_SDL2_Initialize()
{
   	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) 
	{
		printf("SDL_Init Failed \n");
		return false;
	}

    //SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sys_time_init_data);

    sdl_window = SDL_CreateWindow("Microchip Graphics Suite",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_HOR_RES,
                                  SDL_VER_RES,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
	if(sdl_window == NULL)
	{
		printf("SDL_CreateWindow Failed \n");
		return false;
	}

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if(sdl_renderer == NULL)
	{
		printf("SDL_CreateWindow Failed \n");
		return false;
	}

    for (uint32_t layerCount = 0; layerCount < SDL_VIRTUAL_LAYERS; layerCount++)
    {
        drvLayer[layerCount].resx = SDL_HOR_RES;
        drvLayer[layerCount].resy = SDL_VER_RES;
        drvLayer[layerCount].startx = 0;
        drvLayer[layerCount].starty = 0;
        drvLayer[layerCount].sizex = drvLayer[layerCount].resx;
        drvLayer[layerCount].sizey = drvLayer[layerCount].resy;
        drvLayer[layerCount].alpha = 255;
        drvLayer[layerCount].blendmode = SDL_BLENDMODE_BLEND;
        drvLayer[layerCount].enabled = true;
        drvLayer[layerCount].updateLock = LAYER_UNLOCKED;
        drvLayer[layerCount].bufferIdx = SDL_BUFFERS_PER_LAYER - 1;

        if (LE_DEFAULT_COLOR_MODE == LE_COLOR_MODE_RGB_565)
        {
            drvLayer[layerCount].pixelformat = SDL_PIXELFORMAT_RGB565;
            drvLayer[layerCount].baseaddr[0] = (uint16_t *) frame_buffer[layerCount];
            drvLayer[layerCount].stride = SDL_HOR_RES * sizeof(uint16_t);
        }
        else
        {
            drvLayer[layerCount].pixelformat = SDL_PIXELFORMAT_RGBA8888;
            drvLayer[layerCount].baseaddr[0] = (uint32_t *)frame_buffer[layerCount];
            drvLayer[layerCount].stride = SDL_HOR_RES * sizeof(uint32_t);
        }

        texture_rect[layerCount].x = drvLayer[layerCount].startx;
        texture_rect[layerCount].y = drvLayer[layerCount].starty;
        texture_rect[layerCount].w = drvLayer[layerCount].sizex;
        texture_rect[layerCount].h = drvLayer[layerCount].sizey;

        render_rect[layerCount].x = drvLayer[layerCount].startx;
        render_rect[layerCount].y = drvLayer[layerCount].starty;
        render_rect[layerCount].w = drvLayer[layerCount].sizex;
        render_rect[layerCount].h = drvLayer[layerCount].sizey;

        for (uint32_t bufferCount = 0; bufferCount < SDL_BUFFERS_PER_LAYER; ++bufferCount)
        {
            if (LE_DEFAULT_COLOR_MODE == LE_COLOR_MODE_RGB_565)
            {
                memset(drvLayer[layerCount].baseaddr[bufferCount], 0x00, SDL_HOR_RES * SDL_VER_RES * sizeof(uint16_t));
            }
            else
            {
                memset(drvLayer[layerCount].baseaddr[bufferCount], 0x00, SDL_HOR_RES * SDL_VER_RES * sizeof(uint32_t));
            }            
            
        }

        gfxPixelBufferCreate(SDL_HOR_RES,
                             SDL_VER_RES,
                             getGFXColorModeFromSDLPixelFormat(drvLayer[layerCount].pixelformat),
                             drvLayer[layerCount].baseaddr[0],
                             &drvLayer[layerCount].pixelBuffer[drvLayer[layerCount].bufferIdx]);

        sdl_texture[layerCount] = SDL_CreateTexture(sdl_renderer,
                                                    drvLayer[layerCount].pixelformat,
                                                    SDL_TEXTUREACCESS_STREAMING,
                                                    drvLayer[layerCount].resx,
                                                    drvLayer[layerCount].resy);

        SDL_SetTextureBlendMode(sdl_texture[layerCount], drvLayer[layerCount].blendmode);
        SDL_SetTextureAlphaMod(sdl_texture[layerCount], (uint8_t)(drvLayer[layerCount].alpha & 0xff));
        SDL_UpdateTexture(sdl_texture[layerCount], &texture_rect[layerCount], drvLayer[layerCount].baseaddr[0], drvLayer[layerCount].stride);
        SDL_RenderCopy(sdl_renderer, sdl_texture[layerCount], &texture_rect[layerCount], &render_rect[layerCount]);
    }

    SDL_RenderPresent(sdl_renderer);

	    // initialize hardware layer
    if(leInitialize(&gfxDriverInterface, NULL) == LE_FAILURE)
    {
        //ToDo Add drm device deinitialize
        return -1;
    }

    legato_initializeScreenState();

	return true;
}

gfxResult GFX_SDL2_BlitBuffer(int32_t x,
                              int32_t y,
                              gfxPixelBuffer *buf)
{
    if (state != DRAW)
        return GFX_FAILURE;

    gfxPixelBuffer_SetLocked(buf, GFX_TRUE);

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.height = buf->size.height;
    srcRect.width = buf->size.width;

    destRect.x = x;
    destRect.y = y;
    destRect.height = buf->size.height;
    destRect.width = buf->size.width;

    GFX_SDL2_BufferBlit(buf, &srcRect, &drvLayer[activeLayer].pixelBuffer[drvLayer[activeLayer].bufferIdx], &destRect);

    gfxPixelBuffer_SetLocked(buf, GFX_FALSE);

    return GFX_SUCCESS;
}

static gfxDriverIOCTLResponse GFX_SDL2_LayerConfig(gfxDriverIOCTLRequest request,
                                                   gfxIOCTLArg_LayerArg *arg)
{
    gfxIOCTLArg_LayerValue *val;
    gfxIOCTLArg_LayerPosition *pos;
    gfxIOCTLArg_LayerSize *sz;

    // make sure layer is locked before accepting changes
    if (arg->id >= SDL_VIRTUAL_LAYERS)
        return GFX_IOCTL_ERROR_UNKNOWN;

    // attempt to lock
    if (request == GFX_IOCTL_SET_LAYER_LOCK)
    {
        drvLayer[arg->id].updateLock = LAYER_LOCKED;

        return GFX_IOCTL_OK;
    }

    // layer should be locked
    if (drvLayer[arg->id].updateLock != LAYER_LOCKED)
        return GFX_IOCTL_ERROR_UNKNOWN;

    if (request == GFX_IOCTL_SET_LAYER_UNLOCK)
    {
        drvLayer[arg->id].updateLock = LAYER_LOCKED_PENDING;

        return GFX_IOCTL_OK;
    }

    switch (request)
    {
    case GFX_IOCTL_SET_LAYER_ALPHA:
    {
        val = (gfxIOCTLArg_LayerValue *)arg;

        drvLayer[arg->id].alpha = val->value.v_uint;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_SET_LAYER_SIZE:
    {
        sz = (gfxIOCTLArg_LayerSize *)arg;

        drvLayer[arg->id].resx = sz->width;
        drvLayer[arg->id].resy = sz->height;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_SET_LAYER_POSITION:
    {
        pos = (gfxIOCTLArg_LayerPosition *)arg;

        drvLayer[arg->id].startx = pos->x;
        drvLayer[arg->id].starty = pos->y;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_SET_LAYER_WINDOW_SIZE:
    {
        sz = (gfxIOCTLArg_LayerSize *)arg;

        drvLayer[arg->id].sizex = sz->width;
        drvLayer[arg->id].sizey = sz->height;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_SET_LAYER_BASE_ADDRESS:
    {
        val = (gfxIOCTLArg_LayerValue *)arg;

        drvLayer[arg->id].baseaddr[0] = val->value.v_pointer;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_SET_LAYER_COLOR_MODE:
    {
        val = (gfxIOCTLArg_LayerValue *)arg;
        drvLayer[arg->id].pixelformat = getSDLPixelFormatFromGFXColorMode(val->value.v_colormode);
        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_GET_LAYER_ENABLED:
    {
        val = (gfxIOCTLArg_LayerValue *)arg;

        val->value.v_bool = drvLayer[arg->id].enabled;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_SET_LAYER_ENABLED:
    {
        val = (gfxIOCTLArg_LayerValue *)arg;

        drvLayer[arg->id].enabled = val->value.v_bool;

        return GFX_IOCTL_OK;
    }
    default:
        break;
    }

    return GFX_IOCTL_UNSUPPORTED;
}

gfxDriverIOCTLResponse GFX_SDL2_SetPalette(gfxIOCTLArg_Palette *pal)
{
    return GFX_IOCTL_UNSUPPORTED;
}

gfxDriverIOCTLResponse GFX_SDL2_IOCTL(gfxDriverIOCTLRequest request,
                                      void *arg)
{
    gfxIOCTLArg_Value *val;
    gfxIOCTLArg_DisplaySize *disp;
    gfxIOCTLArg_LayerRect *rect;

    switch (request)
    {
    case GFX_IOCTL_LAYER_SWAP:
    {
        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_FRAME_END:
    {

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_GET_BUFFER_COUNT:
    {
        val = (gfxIOCTLArg_Value *)arg;

        val->value.v_uint = SDL_BUFFERS_PER_LAYER;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_GET_DISPLAY_SIZE:
    {
        disp = (gfxIOCTLArg_DisplaySize *)arg;

        disp->width = SDL_HOR_RES;
        disp->height = SDL_VER_RES;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_GET_LAYER_COUNT:
    {
        val = (gfxIOCTLArg_Value *)arg;

        val->value.v_uint = SDL_VIRTUAL_LAYERS;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_GET_ACTIVE_LAYER:
    {
        val = (gfxIOCTLArg_Value *)arg;

        val->value.v_uint = activeLayer;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_SET_ACTIVE_LAYER:
    {
        val = (gfxIOCTLArg_Value *)arg;

        if (val->value.v_uint >= SDL_VIRTUAL_LAYERS)
        {
            return GFX_IOCTL_ERROR_UNKNOWN;
        }
        else
        {
            activeLayer = val->value.v_uint;

            return GFX_IOCTL_OK;
        }
    }
    case GFX_IOCTL_GET_LAYER_RECT:
    {
        rect = (gfxIOCTLArg_LayerRect *)arg;

        if (rect->layer.id >= SDL_VIRTUAL_LAYERS)
            return GFX_IOCTL_ERROR_UNKNOWN;

        rect->x = drvLayer[rect->layer.id].startx;
        rect->y = drvLayer[rect->layer.id].starty;
        rect->width = drvLayer[rect->layer.id].sizex;
        rect->height = drvLayer[rect->layer.id].sizey;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_GET_VSYNC_COUNT:
    {
        val = (gfxIOCTLArg_Value *)arg;

        val->value.v_uint = vsyncCount;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_GET_FRAMEBUFFER:
    {
        val = (gfxIOCTLArg_Value *)arg;

        val->value.v_pbuffer = &drvLayer[activeLayer].pixelBuffer[drvLayer[activeLayer].bufferIdx];

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_SET_PALETTE:
    {
        return GFX_SDL2_SetPalette((gfxIOCTLArg_Palette *)arg);
    }
    case GFX_IOCTL_SET_VBLANK_SYNC:
    {
        vblankSync = ((gfxIOCTLArg_Value *)arg)->value.v_bool;

        return GFX_IOCTL_OK;
    }
    case GFX_IOCTL_GET_STATUS:
    {
        unsigned int i;
        val = (gfxIOCTLArg_Value *)arg;

        val->value.v_uint = 0;

        for (i = 0; i < SDL_VIRTUAL_LAYERS; i++)
        {
            if (drvLayer[i].updateLock != LAYER_UNLOCKED)
            {
                val->value.v_uint = 1;

                break;
            }
        }

        return GFX_IOCTL_OK;
    }
    default:
    {
        if (request >= GFX_IOCTL_LAYER_REQ_START &&
            request <= GFX_IOCTL_LAYER_REQ_END)
        {
            return GFX_SDL2_LayerConfig(request, (gfxIOCTLArg_LayerArg *)arg);
        }
    }
    }

    return GFX_IOCTL_UNSUPPORTED;
}
