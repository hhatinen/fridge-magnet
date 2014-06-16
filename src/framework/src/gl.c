
#include <stdlib.h>
#include <stdio.h>

#include "gl.h"
#include "gl_internal.h"

void gl_setup(int scr_width, int scr_height) {
    glViewport(0, 0, scr_width, scr_height);
}

GLuint gl_compileShader(GLuint type, const char * data) {
    GLuint shader;
    GLint b_compiled;
    
    shader = glCreateShader(type);
   
    if (!shader) {
        return 0;
    }
    
    glShaderSource(shader, 1, &data, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &b_compiled);
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
    
    program = glCreateProgram();
    if (!program) {
        return 0;
    }
    
    GLuint vertex_shader, fragment_shader;
    
    vertex_shader = gl_compileShader(GL_VERTEX_SHADER, vertex_shader_data);
    if (!vertex_shader) {
        return 0;
    }
    
    fragment_shader = gl_compileShader(GL_FRAGMENT_SHADER, fragment_shader_data);
    if (!fragment_shader) {
        return 0;
    }
    
    glAttachShader(GL_VERTEX_SHADER, vertex_shader);
    glAttachShader(GL_FRAGMENT_SHADER, fragment_shader);
    
    glLinkProgram(program);
    
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



