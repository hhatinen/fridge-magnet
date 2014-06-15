
#include "gl.h"
#include "gl_internal.h"

void gl_setup(int scr_width, int scr_height) {
    glViewport(0, 0, scr_width, scr_height);
}
