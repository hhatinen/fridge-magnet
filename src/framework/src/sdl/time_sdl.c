#include "SDL2/SDL.h"
#include "time.h"

unsigned int time_ticks() {
    return SDL_GetTicks();
}
