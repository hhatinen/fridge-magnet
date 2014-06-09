#pragma once

#ifdef GL
    #ifdef __APPLE__
        #include <OpenGL/glu.h>
        #include <OpenGL/glext.h>
    #else
        #include <GL/glu.h>
        #include <GL/glext.h>
        #include <GL/glx.h>
        #include <GL/glxext.h>
        #define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)
    #endif
#elif EGL
    #include <GLES2/gl2.h>
    #include <EGL/egl.h>
#else
    #error You must define either GL or EGL
#endif

