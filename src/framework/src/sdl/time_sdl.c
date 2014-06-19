#include "SDL2/SDL.h"
#include "fm_time.h"

unsigned int time_ticks() {
    return SDL_GetTicks();
}
