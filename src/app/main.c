
#include <math.h>

#include "gfx.h"
#include "gl.h"

#include <ft2build.h>
#include FT_FREETYPE_H

void render(unsigned int dt);

const char * g_vertex_src =
    "\
    attribute vec4 p;\
    void main() {\
        gl_Position = p;\
    }";

const char * g_fragment_src =
    "\
    void main()	{\
        gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\
    }";


FT_Library g_ft_lib;
FT_Face g_ft_face;

GLuint g_shaderprogram;

int main(int argc, char *argv[]) {
    
    FT_Init_FreeType(&g_ft_lib);
    FT_New_Face(g_ft_lib, "data/HelveticaNeue-Medium.ttf", 0, &g_ft_face);
    FT_Set_Char_Size(g_ft_face, 0, 16*64, 1024, 576);
    int glyph_index = FT_Get_Char_Index(g_ft_face, 'A');
    FT_Load_Glyph(g_ft_face, glyph_index, 0);
    FT_Render_Glyph(g_ft_face->glyph, FT_RENDER_MODE_NORMAL);
    
    
#if FM_EGL
    int w = 1440, h = 900;
#else
    int w = 1440>>1, h = 900>>1;
#endif
    
    int err = 0;
    if((err = gfx_createWindow(w, h))) {
        printf("fuck %d\n", err);
    } else {
        g_shaderprogram = gl_createProgram(g_vertex_src, g_fragment_src);
        if (!g_shaderprogram) {
            return 0;
        }
  
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
    
    GLfloat verts[] = {-0.5f,-0.5f, 0.0f, 1.0f,
                       -0.5f, 0.5f, 0.0f, 1.0f,
                        0.5f,-0.5f, 0.0f, 1.0f,
                        0.5f, 0.5f, 0.0f, 1.0f };
    glBindAttribLocation(g_shaderprogram, 0, "pos");
    glUseProgram(g_shaderprogram);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, verts);
    glEnableVertexAttribArray ( 0 );
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
}

