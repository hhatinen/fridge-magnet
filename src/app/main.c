
#include <math.h>

#include "gfx.h"
#include "gl.h"

#include <ft2build.h>
#include FT_FREETYPE_H

void render(unsigned int dt);

FT_Library g_ft_lib;
FT_Face g_ft_face;

int main(int argc, char *argv[]) {
    
    FT_Init_FreeType(&g_ft_lib);
    
    FT_New_Face(g_ft_lib, "data/HelveticaNeue-Medium.ttf", 0, &g_ft_face);
    FT_Set_Char_Size(g_ft_face, 0, 16*64, 1024, 576);

    int glyph_index = FT_Get_Char_Index(g_ft_face, 'A');
    FT_Load_Glyph(g_ft_face, glyph_index, 0);
    FT_Render_Glyph(g_ft_face->glyph, FT_RENDER_MODE_NORMAL);
    
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

