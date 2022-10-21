#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: ascii_image <file.ppm>\n");
    return 0;
  }

  int w;
  int h;
  struct ppm_pixel* image = read_ppm(argv[1], &w,&h);
  int I;
  char c;

  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      I = ((image[i*(w)+j].red) + (image[i*(w)+j].green) + (image[i*(w)+j].blue))/3;

      if(I >= 0 && I <= 25){
        c = '@';
        printf("%c ",c);
      }     

      else if(I >= 26 && I <= 50){
        c = '#';
        printf("%c ",c);
      }

      else if(I >= 51 && I <= 75){
        c = '%';
        printf("%c ",c);
      }

      else if(I >= 76 && I <= 10){
        c = '*';
        printf("%c ",c);
      }

      else if(I >= 101 && I <= 125){
        c = 'o';
        printf("%c ",c);
      }

      else if(I >= 126 && I <= 150){
        c = ';';
        printf("%c ",c);
      }

      else if(I >= 151 && I <= 175){
        c = ':';
        printf("%c ",c);
      }

      else if(I >= 176 && I <= 200){
        c = ',';
        printf("%c ",c);
      }

      else if(I >= 201 && I <= 225){
        c = '.';
        printf("%c ",c);
      }

      else if(I >= 226 && I <= 255){
        c = ' ';
        printf("%c ",c);
      }   
    }
    printf("\n");
  }
  return 0;}