
#include "gfx.h"
#include "gl.h"
#include "gl_internal.h"
#include "vec.h"

void gl_drawTexture2(const texture * texture, vec2 img_scale, vec2 img_offset, vec2 img_pos);

const char * drawtex_srcvert =
"\
uniform vec2 img_scale;\
uniform vec2 img_offset;\
uniform vec2 img_pos;\
attribute vec4 p;\
varying vec2 v_tex;\
\
void main() {\
    v_tex = vec2(0,1) + vec2(1,-1) * vec2(p.xy) + 0.5;\
    gl_Position = vec4((p.xy + img_offset * 0.5) * img_scale + img_pos, 0.0, 1.0);\
}";

const char * drawtex_srcfrag =
"\
uniform sampler2D txt;\
varying vec2 v_tex;\
\
void main()	{\
    vec3 txtcol = texture2D(txt, v_tex).rgb;\
    gl_FragColor = vec4(txtcol.rgb, 1.0);\
}";

GLuint drawtex_shaderprogram;

int drawtex_initialized = 0;

void gl_initDrawTex() {
    drawtex_shaderprogram = gl_createProgram(drawtex_srcvert, drawtex_srcfrag);
    if (!drawtex_shaderprogram) {
    }
}

void gl_drawTexture(const texture * texture, float x, float y, int align, float scale) {
    vec2 img_pos = {x / gfx_getScrAspect(),y};
    vec2 img_offset = {
        (float)ALIGN_HORIZ(align),
        (float)ALIGN_VERT(align)
    };
    
    int scr_width = gfx_getScreenWidth();
    int scr_height = gfx_getScreenHeight();
    
    vec2 img_scale = {
        scale * (float)(texture->image_width) / scr_width,
        scale * (float)(texture->image_height) / scr_height
    };
    
    gl_drawTexture2(texture, img_scale, img_offset, img_pos);
}

void gl_drawTexture2(const texture * texture, vec2 img_scale, vec2 img_offset, vec2 img_pos) {
    if (!drawtex_initialized) {
        gl_initDrawTex();
        drawtex_initialized = 1;
    }
    
    GL(glEnable(GL_TEXTURE_2D));
    
    static GLfloat verts[] = {
        -0.5f,-0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f,
         0.5f,-0.5f, 0.0f, 1.0f,
         0.5f, 0.5f, 0.0f, 1.0f };
    
    GL(glUseProgram(drawtex_shaderprogram));
    GL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, verts));
    GL(glEnableVertexAttribArray(0));
    GL(glActiveTexture(GL_TEXTURE0));
    GL(glBindTexture(GL_TEXTURE_2D, texture->gl_handle));
    GL(glUniform2f(glGetUniformLocation(drawtex_shaderprogram, "img_scale"), img_scale.x, img_scale.y));
    GL(glUniform2f(glGetUniformLocation(drawtex_shaderprogram, "img_offset"), img_offset.x, img_offset.y));
    GL(glUniform2f(glGetUniformLocation(drawtex_shaderprogram, "img_pos"), img_pos.x, img_pos.y));
    GL(glUniform1i(glGetUniformLocation(drawtex_shaderprogram, "txt"), 0));
    GL(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
 
    
}

