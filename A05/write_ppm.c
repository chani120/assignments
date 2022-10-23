#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement one

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
 FILE* fp = fopen(filename, "wb");
 fprintf(fp, "P6\n# Created by GIMP version 2.10.24 PNM plug-in\n%d %d\n225\n",w,h);
 
 for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
       fwrite(&pixels[i*w +j].red, 1, 1, fp );
       fwrite(&pixels[i*w +j].blue, 1, 1, fp );
       fwrite(&pixels[i*w +j].green, 1, 1, fp );
    }
 }
 fclose(fp);

}
