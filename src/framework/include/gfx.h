#pragma once

typedef struct {
    int width;
    int height;
    int depth;

    unsigned char * data;
} image;

int gfx_createWindow(int w, int h);
void gfx_dispose();
void gfx_loop(int target_frame_rate, void (*render_func)(unsigned int));

void gfx_createNoiseImage(int width, int height, int depth, image * out_image);

int gfx_loadJPG(const char * filename, image * out_image);