
#pragma once

#include "gfx.h"

#ifdef FM_GL
    #ifdef __APPLE__
        #include <OpenGL/glu.h>
        #include <OpenGL/OpenGL.h>
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

#define GL(...) __VA_ARGS__; if (glGetError() != GL_NO_ERROR) { printf("GL Error for %s!\n", #__VA_ARGS__ ); }

typedef struct {
    GLuint gl_handle;
    int image_width, image_height;
    int texture_width, texture_height;
} texture;


GLuint gl_createProgram(const char * vertex_shader_data, const char * fragment_shader_data);
int gl_createTexture(const image * image, texture * out_texture);

