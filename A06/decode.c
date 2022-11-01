#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include <math.h>

int dec(int arr[]){
int value = 0;
for (int i = 7; i >= 0; i--){
    value = value + arr[i]*pow(2.0,(double)(7-i));
  }
printf("%c",(char)(value));
return value;
}


int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }

  int w, h;
  int index = 0;
  int binary[1000];
  
  struct ppm_pixel* pixels = read_ppm(argv[1],&w,&h);

  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      binary[index] = (pixels[i*(w)+j].red & 0b1);
      index = index +1;
      binary[index] = (pixels[i*(w)+j].green & 0b1);
      index = index +1;
      binary[index] = (pixels[i*(w)+j].blue & 0b1);
      index = index +1;
    }
  }
  
  for(int x = 0; x < index; x++){
      printf("%d",binary[x]);
  }

int decarr[8];
printf("\n");

for (int x = 0; x < index; x += 8){
  decarr[0] = binary[x];
  decarr[1] = binary[x+1];
  decarr[2] = binary[x+2];
  decarr[3] = binary[x+3];
  decarr[4] = binary[x+4];
  decarr[5] = binary[x+5];
  decarr[6] = binary[x+6];
  decarr[7] = binary[x+7];
  dec(decarr);
  }

  free(pixels);
  return 0;
}
