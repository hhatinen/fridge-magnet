
#include "gfx_internal.h"
#include "gfx.h"
#include "time.h"

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

