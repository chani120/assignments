#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  // load feep-raw and print out the grid of pixels
  int w;
  int h;
  struct ppm_pixel* image = read_ppm("feep-raw.ppm", &w,&h);
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      printf("( %hhu %hhu %hhu )", image[i*(w)+j].red, image[i*(w)+j].green, image[i*(w)+j].blue);
   }
   printf("\n");
  } 


  free(image);
  return 0;
}

