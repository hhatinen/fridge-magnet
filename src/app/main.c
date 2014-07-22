
#include <math.h>

#include "gfx.h"
#include "gl.h"

#include <ft2build.h>
#include FT_FREETYPE_H

void render(unsigned int dt);

FT_Library g_ft_lib;
FT_Face g_ft_face;

texture g_txt;

GLuint g_shaderprogram;

int main(int argc, char *argv[]) {
    
//    FT_Init_FreeType(&g_ft_lib);
//    FT_New_Face(g_ft_lib, "data/HelveticaNeue-Medium.ttf", 0, &g_ft_face);
//    FT_Set_Char_Size(g_ft_face, 0, 16*64, 1024, 576);
//    int glyph_index = FT_Get_Char_Index(g_ft_face, 'A');
//    FT_Load_Glyph(g_ft_face, glyph_index, 0);
//    FT_Render_Glyph(g_ft_face->glyph, FT_RENDER_MODE_NORMAL);
    
    image img;
    //gfx_createNoiseImage(256, 256, 3, &img);
    gfx_loadJPG("data/pictures/IMG_1909.jpg", &img);

#if FM_EGL
    int w = 1360, h = 768;
#else
    int w = 1360>>1, h = 768>>1;
#endif
    
    int err = 0;
    if((err = gfx_createWindow(w, h))) {
        printf("fuck %d\n", err);
    } else {
        gl_createTexture(&img, &g_txt);
  
        gfx_loop(60, render);
        gfx_dispose();
    }
    
    return 0;
}

float a = 0.0f;
void render(unsigned int dt) {
    a += (float)dt * 0.004f;
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    gl_drawTexture(&g_txt, 0, 0, ALIGN_HCVC, 2.0f);
    
}

