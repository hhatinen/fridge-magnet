#pragma once

#ifdef FM_GL
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
#elif FM_EGL
    #include <sys/time.h>

    #include <GLES2/gl2.h>
    #include <EGL/egl.h>
#else
    #error You must define either FM_GL or FM_EGL
#endif

GLuint gl_createProgram(const char * vertex_shader_data, const char * fragment_shader_data);
