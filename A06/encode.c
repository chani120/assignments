#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int* bin(char* arr, int width, int height){
  int* binary = (int*)malloc(8*sizeof(arr)*width*height);
  int num =0;
  for (int i = 0; i < 8*(sizeof(arr)); i+=8){
    num = arr[i/8];
    binary[i+7] = num%2;
    num = num/2;
    binary[i+6] = num%2;
    num = num/2;
    binary[i+5] = num%2;
    num = num/2;
    binary[i+4] = num%2;
    num = num/2;
    binary[i+3] = num%2;
    num = num/2;
    binary[i+2] = num%2;
    num = num/2;
    binary[i+1] = num%2;
    num = num/2;
    binary[i] = num%2;
  }
return binary;
}


int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }

  int w, h;
  struct ppm_pixel* pixels = read_ppm(argv[1],&w,&h);

  int max = (3*w*h)/8;
  char * message = (char*)malloc(max*sizeof(char*));
  printf("Please enter a secret message: ");
  scanf("%s", message);
  
  //int * array = (int*)malloc(message*(sizeof(int*))*w*h)
  
  int *num = bin(message, w, h);
  
  int y = 0;
   for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      pixels[i*(w)+j].red = (pixels[i*(w)+j].red & 0b11111110) | num[y] ;
      y = y +1;
      pixels[i*(w)+j].green = (pixels[i*(w)+j].green & 0b11111110) | num[y];
      y = y +1;
      pixels[i*(w)+j].blue = (pixels[i*(w)+j].blue & 0b11111110) | num[y];
      y = y +1;
    }
  }
  
  char* new_file = malloc(strlen(argv[1])+8);
  strcpy(new_file,argv[1]);
  new_file[strlen(new_file)-4] = '\0';
  strcat(new_file,"-new.ppm");

  write_ppm(new_file, pixels, w, h);

  free(pixels);
  free(new_file);
  return 0;
}

