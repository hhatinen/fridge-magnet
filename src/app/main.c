
#include <math.h>

#include "gfx.h"
#include "gl.h"

#include <ft2build.h>
#include FT_FREETYPE_H

void render(unsigned int dt);

const char * g_vertex_src =
    "\
    attribute vec4 p;\
    varying vec2 v_tex;\
    void main() {\
        v_tex = vec2(0,1) + vec2(1,-1) * vec2(p.xy) + 0.5;\
        gl_Position = vec4(p.xyz * 2.0, 1.0);\
    }";

const char * g_fragment_src =
    "\
    uniform sampler2D txt;\
    varying vec2 v_tex;\
    void main()	{\
        vec3 txtcol = texture2D(txt, v_tex).rgb;\
        gl_FragColor = vec4(txtcol.rgb, 1.0);\
    }";


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
    
    GL(glEnable(GL_TEXTURE_2D));
    
    GLfloat verts[] = {-0.5f,-0.5f, 0.0f, 1.0f,
                       -0.5f, 0.5f, 0.0f, 1.0f,
                        0.5f,-0.5f, 0.0f, 1.0f,
                        0.5f, 0.5f, 0.0f, 1.0f };
    
    
    GL(glUseProgram(g_shaderprogram));
    
    GL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, verts));
    GL(glEnableVertexAttribArray(0));
    
    GL(glActiveTexture(GL_TEXTURE0));
    GL(glBindTexture(GL_TEXTURE_2D, g_txt.gl_handle));
    GL(glUniform1i(glGetUniformLocation(g_shaderprogram, "txt"), 0));
    
    GL(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    
}

