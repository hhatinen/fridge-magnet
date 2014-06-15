
#include "bcm_host.h"

#include "gfx.h"
#include "../gfx_internal.h"
#include "gl.h"
#include "time.h"

typedef struct _escontext {
    GLint       width;
    GLint       height;
    
    EGLNativeWindowType  hWnd;
    EGLDisplay  eglDisplay;
    EGLContext  eglContext;
    EGLSurface  eglSurface;
} ESContext;

ESContext g_gfx_context;

EGL_DISPMANX_WINDOW_T * p_gfx_createWindow(ESContext * out_context);
EGLBoolean p_gfx_createEGLContext ( EGLNativeWindowType hWnd, EGLDisplay* eglDisplay, EGLContext* eglContext, EGLSurface* eglSurface, EGLint attribList[]);

void gfx_createWindow(int width, int height) {
    int success;
    
    bcm_host_init();
    
    int display_width;
    int display_height;
    success = graphics_get_display_size(0, &display_width, &display_height);
    if (!success) {
        return;// 0;
    }
    
    // Just override supplied values...
    width = display_width;
    height = display_height;
    
    g_gfx_context.width = width;
    g_gfx_context.height = height;
    g_gfx_context.hWnd = p_gfx_createWindow(g_gfx_context.width, g_gfx_context.height);
    if (!context.hWnd) {
        return;// 0;
    }
    
    if (!p_gfx_createEGLContext(g_gfx_context.hWnd, &g_gfx_context.eglDisplay, &g_gfx_context.eglContext, &g_gfx_context.eglSurface)) {
        return;// 0;
    }
    
    return;// 1;
}

void gfx_swapBuffers() {
    eglSwapBuffers(g_gfx_context->eglDisplay, g_gfx_context->eglSurface);
}

void gfx_handleWindowEvents(int * b_end) {
}

EGL_DISPMANX_WINDOW_T * p_gfx_createWindow(int width, int height) {
    VC_RECT_T dst_rect;
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.width = width;
    dst_rect.height = height;
    
    VC_RECT_T src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = width << 16;
    src_rect.height = height << 16;
    
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    dispman_display = vc_dispmanx_display_open(0);
    dispman_update = vc_dispmanx_update_start(0);
    vc_dispmanx_update_submit_sync( dispman_update );
    
    DISPMANX_ELEMENT_HANDLE_T dispman_element;
    dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0/*layer*/, &dst_rect, 0/*src*/, &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, 0/*transform*/);
    
    
    static EGL_DISPMANX_WINDOW_T nativewindow;
    nativewindow.element = dispman_element;
    nativewindow.width = width;
    nativewindow.height = height;
    return &nativewindow;
    
}

EGLBoolean p_gfx_createEGLContext(EGLNativeWindowType hWnd, EGLDisplay* eglDisplay, EGLContext* eglContext, EGLSurface* eglSurface) {
    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    const int b_alpha = 0;
    const int b_depth = 0;
    const int b_stencil = 0;
    const int b_multisample = 0;
    
    EGLint attribList[] = {
        EGL_RED_SIZE,       5,
        EGL_GREEN_SIZE,     6,
        EGL_BLUE_SIZE,      5,
        EGL_ALPHA_SIZE,     (b_alpha) ? 8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (b_depth) ? 8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (b_stencil) ? 8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (b_multisample) ? 1 : 0,
        EGL_NONE
    };
    
    // Get Display
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        return EGL_FALSE;
    }
    
    // Initialize EGL
    if (!eglInitialize(display, &majorVersion, &minorVersion)) {
        return EGL_FALSE;
    }
    
    // Get configs
    if (!eglGetConfigs(display, NULL, 0, &numConfigs)) {
        return EGL_FALSE;
    }
    
    // Choose config
    if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs)) {
        return EGL_FALSE;
    }
    
    // Create a surface
    surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
    if (surface == EGL_NO_SURFACE) {
        return EGL_FALSE;
    }
    
    // Create a GL context
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
    if (context == EGL_NO_CONTEXT) {
        return EGL_FALSE;
    }
    
    // Make the context current
    if (!eglMakeCurrent(display, surface, surface, context)) {
        return EGL_FALSE;
    }
    
    *eglDisplay = display;
    *eglSurface = surface;
    *eglContext = context;
    return EGL_TRUE;
}

