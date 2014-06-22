#pragma once

#include "gfx.h"

void gfx_swapBuffers();
void gfx_handleWindowEvents(int * b_end);
void gfx_crop(const image * image_in, int dest_width, int dest_height, image * image_out);


