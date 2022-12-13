#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"


struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE* fp = fopen(filename, "rb");
  char str[100];
  char check[2];

  
  if(fp == NULL) {
      perror("Error opening file");
      return(NULL);
   }
  
  fgets(str,100, fp);
  printf("%s",str);
  sscanf(str, "%s", check);
  if( check[0] != 'P' || check[1] != '6') {
      printf("File is not valid");
      return NULL;
   }

  
  
  FILE fppoint = *fp;
  fgets(str, 100, fp);
  printf("%s",str);
   if(str[0] != '#'){
    *fp =fppoint;
   }

  fgets(str, 100, fp);
  sscanf(str, "%d %d",w,h);
  printf("%d %d",*w,*h);
  fgets(str, 100, fp);
  printf("%s",str);

  struct ppm_pixel* arr = malloc(sizeof(struct ppm_pixel)*(*w)*(*h));

  fread(arr, sizeof(struct ppm_pixel),(*w)*(*h), fp);
  fclose(fp);
  return(arr);
}