#pragma once

void gfx_createWindow(int w, int h);
void gfx_dispose();
void gfx_loop(int target_frame_rate, void (*render_func)(unsigned int));
