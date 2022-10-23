#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: glitch <file.ppm>\n");
    return 0;
  }
  int w, h;
  struct ppm_pixel* pixels = read_ppm(argv[1],&w,&h);
  
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      pixels[i*(w)+j].red = (pixels[i*(w)+j].red) << (rand() % 2);
      pixels[i*(w)+j].green = (pixels[i*(w)+j].green) << (rand() % 2);
      pixels[i*(w)+j].blue = (pixels[i*(w)+j].blue) << (rand() % 2);
   } 
  } 
 
 //FILE *fp
 //fp = fopen(<argv[1]>"glitch.ppm","wb")
 
  char* new_file = malloc(strlen(argv[1])+10);
  strcpy(new_file,argv[1]);
  strcat(new_file,"-glitch.ppm");

  write_ppm(new_file, pixels, w, h);
  
  free(pixels);
  free(new_file);
  return 0;
}

