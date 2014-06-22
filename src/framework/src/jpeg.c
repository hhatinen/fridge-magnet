
#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <string.h>

#include "gfx.h"

int gfx_loadJPG(const char * filename, image * out_image) {
    struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
    JSAMPROW row;
    
    FILE * f = fopen(filename, "rb");
    if (!f) {
        return 0;
    }
    
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, f);
    jpeg_read_header(&cinfo, TRUE);
 
    out_image->width = cinfo.image_width;
    out_image->height = cinfo.image_height;
    
    out_image->depth = cinfo.num_components;
    
    if (cinfo.out_color_space != JCS_RGB && cinfo.out_color_space != JCS_GRAYSCALE && cinfo.out_color_space != JCS_YCbCr) {
        printf("Unknown color_space for %s: %d\n", filename, cinfo.jpeg_color_space);
        return 0;
    } else {
        out_image->data = (unsigned char*)malloc(out_image->width * out_image->height * out_image->depth);

        jpeg_start_decompress(&cinfo);
        
        row = (unsigned char*)malloc(cinfo.output_width * cinfo.output_components);
        unsigned int n = 0;
        while (cinfo.output_scanline < cinfo.image_height) {
            int pitch = cinfo.output_width * cinfo.output_components;
            jpeg_read_scanlines(&cinfo, &row, 1);
            memcpy(out_image->data + n, row, pitch);
            n += pitch;
        }
        
        if (cinfo.out_color_space == JCS_YCbCr) {
            for (int i = 0; i < cinfo.image_width * cinfo.image_height; i++) {
                float Y  = (float)out_image->data[i * out_image->depth+0];
                float Cb = (float)out_image->data[i * out_image->depth+1];
                float Cr = (float)out_image->data[i * out_image->depth+2];
                float R = Y + 1.402f * (Cr - 128.0f);
                float G = Y - 0.34414f * (Cb - 128.0f) - 0.71414f * (Cr - 128.0f);
                float B = Y + 1.772f * (Cb - 128.0f);
                out_image->data[i * out_image->depth+0] = (unsigned char)R;
                out_image->data[i * out_image->depth+1] = (unsigned char)G;
                out_image->data[i * out_image->depth+2] = (unsigned char)B;
            }
        }
        
        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        free(row);
        fclose(f);
        
        return 1;
    }
    
    
}