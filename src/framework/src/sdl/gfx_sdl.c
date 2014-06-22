
#include "gfx.h"

#include "gl.h"
#include "time.h"
#include "../gl_internal.h"

#include "SDL2/SDL.h"

SDL_Window * g_gfx_window;
SDL_GLContext * g_gfx_gl_context;

int gfx_createWindow(int width, int height) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_DEBUG_FLAG, 1);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    
    g_gfx_window = SDL_CreateWindow("fridge-magnet", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    g_gfx_gl_context = SDL_GL_CreateContext(g_gfx_window);
    
    SDL_GL_SetSwapInterval(1);
    
    gl_setup(width, height);

    printf("grr\n");
    
    return 0;
}

void gfx_dispose() {
    SDL_GL_DeleteContext(g_gfx_gl_context);
    g_gfx_gl_context = NULL;
    
    SDL_DestroyWindow(g_gfx_window);
    g_gfx_window = NULL;
    
    SDL_Quit();
}

void gfx_swapBuffers() {
    SDL_GL_SwapWindow(g_gfx_window);
}

void gfx_handleWindowEvents(int * b_end) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            *b_end = 1;
        }
    }
}
