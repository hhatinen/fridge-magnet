
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "gfx_internal.h"
#include "gfx.h"
#include "fm_time.h"

void gfx_loop(int target_frame_rate, void (*render_func)(unsigned int)) {
    int b_end = 0;
    
    unsigned int last_render_t = time_ticks();
    
    while(!b_end) {

        gfx_handleWindowEvents(&b_end);
        
        unsigned int current_time = time_ticks();
        if ((current_time - last_render_t) * target_frame_rate >= 1000) {
            render_func(current_time - last_render_t);
            gfx_swapBuffers();
            last_render_t = current_time;
        }
    }
}

void gfx_crop(const image * image_in, int dest_width, int dest_height, image * image_out) {

    image_out->width = dest_width;
    image_out->height = dest_height;
    image_out->depth = image_in->depth;
    
    unsigned char * data = (unsigned char *)malloc(dest_width * dest_height * image_in->depth);
    memset(data, 0, dest_width * dest_height * image_in->depth);
    
    image_out->data = data;
    
    int W = MIN(image_in->width, dest_width);
    int H = MIN(image_in->height, dest_height);
    
    int in_pitch = image_in->width * image_in->depth;
    int out_pitch = image_out->width * image_in->depth;
    
    int out_p = 0;
    int in_p = 0;
    for (int y = 0; y < H; y++) {
        memcpy(&data[out_p], &data[in_p], W * image_out->depth);
        in_p += in_pitch;
        out_p += out_pitch;
    }
}

void gfx_createNoiseImage(int width, int height, int depth, image * out_image) {
    
    out_image->data = (unsigned char*)malloc(width*height*depth);
    
    for (int i = 0; i < width*height*depth; i++) {
        out_image->data[i] = rand()&0xff;
    }
    
    out_image->width = width;
    out_image->height = height;
    out_image->depth = depth;
    
}

float gfx_getScrAspect() {
    return (float)gfx_getScreenWidth() / gfx_getScreenHeight();
}

