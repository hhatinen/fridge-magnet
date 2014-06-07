
#include <math.h>

#include "gfx.h"
#include "gl.h"

void render(unsigned int dt);

int main(int argc, char *argv[]) {

    gfx_createWindow(1024, 576);

    gfx_loop(60, render);
    
    gfx_dispose();
    
    return 0;
}

float a = 0.0f;
void render(unsigned int dt) {
    a += (float)dt * 0.004f;
    glClearColor((sinf(a) + 1.0f) * 0.5f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

