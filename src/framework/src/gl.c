
#include <stdlib.h>
#include <stdio.h>

#include "gl.h"
#include "gl_internal.h"

#include "gfx_internal.h"

void gl_setup(int scr_width, int scr_height) {
    glViewport(0, 0, scr_width, scr_height);
}

GLuint gl_compileShader(GLuint type, const char * data) {
    GLuint shader;
    GLint b_compiled;
    
    shader = GL(glCreateShader(type));
   
    if (!shader) {
        return 0;
    }
    
    GL(glShaderSource(shader, 1, &data, NULL));
    GL(glCompileShader(shader));

    GL(glGetShaderiv(shader, GL_COMPILE_STATUS, &b_compiled));
    if (!b_compiled) {
        GLint infoLen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char * info = (char*)malloc(infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, info);
            printf("Shader compile error: %s\n", info);
            free(info);
        } else {
            printf("Shader compile error\n");
        }
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

GLuint gl_createProgram(const char * vertex_shader_data, const char * fragment_shader_data) {
    GLuint program;
    
    
    GLuint vertex_shader, fragment_shader;
    
    vertex_shader = gl_compileShader(GL_VERTEX_SHADER, vertex_shader_data);
    if (!vertex_shader) {
        return 0;
    }
    
    fragment_shader = gl_compileShader(GL_FRAGMENT_SHADER, fragment_shader_data);
    if (!fragment_shader) {
        return 0;
    }
    
    program = GL(glCreateProgram());
    if (!program)
    {
        return 0;
    }
 
    GL(glAttachShader(program, vertex_shader));
    GL(glAttachShader(program, fragment_shader));

    //glBindAttribLocation(program, 0, "pos");
    
    GL(glLinkProgram(program));
    
    GLint b_linked;
    glGetProgramiv(program, GL_LINK_STATUS, &b_linked);
    if (!b_linked) {
        GLint info_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1) {
            char * info_str = (char*)malloc(info_len);
            glGetProgramInfoLog(program, info_len, NULL, info_str);
            printf("Error linking shader program: %s\n", info_str);
            free(info_str);
        } else {
            printf("Error linking shader program\n");
        }
        return 0;
    }
    
    return program;
    
}

int gl_createTexture(const image * in_image, texture * out_texture) {
    GLuint tex;
    
    int W = 1;
    int H = 1;
    while (W < in_image->width) W <<= 1;
    while (H < in_image->height) H <<= 1;
    
    image image;
    if (W != in_image->width || H != in_image->height) {
//        gfx_crop(in_image, W, H, &image);
        image = *in_image;
        W = in_image->width;
        H = in_image->height;
    } else {
        image = *in_image;
    }
    
    GL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    GL(glGenTextures(1, &tex));
    GL(glBindTexture(GL_TEXTURE_2D, tex));
    GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data));
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 
    out_texture->gl_handle = tex;
    out_texture->image_width = in_image->width;
    out_texture->image_height = in_image->height;
    out_texture->texture_width = W;
    out_texture->texture_height = H;
    
    return 1;
}
















