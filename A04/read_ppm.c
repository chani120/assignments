#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"


struct ppm_pixel {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
}

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE* fp = fopen(filename, "rb");
  char str[100];
  char check[2];
  
  if(fp == NULL) {
      perror("Error opening file");
      return(NULL);
   }
  
  fgets(str,100, fp);
  sscanf(str, "%s", check);
  if( check[0] != 'P' || check[1] != '6') {
      printf("File is not valid");
      return NULL;
   }
  
  fgets(str, 100, fp);
  sscanf(str, "%d %d", w,h);
  
  struct ppm_pixel* arr = malloc(sizeof(struct ppm_pixel)*(*w)*(*h));
  for(int i = 0; 1 <*h; i++){
    for(int j = 0; 1 <*w; j++){
      fscanf(fp, " %hhu %hhu %hhu", &arr[i*(*h)+j].red, &arr[i*(*h)+j].green, &arr[i*(*h)+j].blue);
    }
  }
  fclose(fp);
  return(arr);
}

