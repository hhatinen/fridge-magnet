#pragma once

#include "gl.h"

void gl_setup(int scr_width, int scr_height);
GLuint gl_compileShader(GLuint type, const char * data);
