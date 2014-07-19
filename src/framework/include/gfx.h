#pragma once

#define ALIGN_L  0x00
#define ALIGN_R  0x02
#define ALIGN_HC 0x01
#define ALIGN_B  0x00
#define ALIGN_T  0x08
#define ALIGN_VC 0x04
#define ALIGN_LT (ALIGN_L | ALIGN_T)
#define ALIGN_LVC (ALIGN_L | ALIGN_VC)
#define ALIGN_LB (ALIGN_L | ALIGN_B)
#define ALIGN_HCT (ALIGN_HC | ALIGN_T)
#define ALIGN_HCVC (ALIGN_HC | ALIGN_VC)
#define ALIGN_HCB (ALIGN_HC | ALIGN_B)
#define ALIGN_RT (ALIGN_R | ALIGN_T)
#define ALIGN_RVC (ALIGN_R | ALIGN_VC)
#define ALIGN_RB (ALIGN_R | ALIGN_B)

#define ALIGN_HORIZ(a) (-(((a) & 0x3) - 1))
#define ALIGN_VERT(a) (-((((a) >> 2) & 0x3) - 1))


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

int gfx_getScreenWidth();
int gfx_getScreenHeight();
float gfx_getScrAspect();

