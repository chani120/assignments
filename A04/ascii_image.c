#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: ascii_image <file.ppm>\n");
    return 0;
  }


  FILE* fp = fopen(argv[1], "rb");
  int width, height; 
  char str[100];
 
  fgets(str, 100, fp);
  sscanf(str, "%d %d", width,height);
    // allocate place for array[width][length][3]
    int a, b;
    int array;
    array = malloc(width*sizeof(int*));
    for(a = 0; a < width; a++){
        array[a] = malloc(height*sizeof(int *));
        for(b = 0; b < height; b++){
            array[a][b] = malloc(3*sizeof(int));
        }
    }
  
 
    for (int y = 0; y < height;y++){ 
        for(int x=0; x < width; x++){
            array[x][y][0] = fgetc(argv[1]); //red
            array[x][y][1] = fgetc(argv[1]); //green
            array[x][y][2] = fgetc(argv[1]); //blue
}}

char outputFile[100];
FILE *output = fopen(outputFile, "w"); 

char c;
int I;

for (int y = 0; y < height;y++){ 
  for(int x=0; x < width; x++){
    I = (array[x][y][0] + array[x][y][1] + array[x][y][2])/3;
    if(I >= 0 && I <= 25){
      char c = '@';
      fprintf(output,"%c ",c);
    }     

    else if(I >= 26 && I <= 50){
      char c = '#';
      fprintf(output,"%c ",c);
    }

    else if(I >= 51 && I <= 75){
      char c = '%';
      fprintf(output,"%c ",c);
    }

    else if(I >= 76 && I <= 10){
      char c = '*';
      fprintf(output,"%c ",c);
    }

    else if(I >= 101 && I <= 125){
      char c = 'o';
      fprintf(output,"%c ",c);
    }

    else if(I >= 126 && I <= 150){
      char c = ';';
      fprintf(output,"%c ",c);
    }

    else if(I >= 151 && I <= 175){
      char c = ':';
      fprintf(output,"%c ",c);
    }

    else if(I >= 176 && I <= 200){
      char c = ',';
      fprintf(output,"%c ",c);
    }

    else if(I >= 201 && I <= 225){
      char c = '.';
      fprintf(output,"%c ",c);
    }

    else if(I >= 226 && I <= 255){
      char c = ' ';
      fprintf(output,"%c ",c);
    }

  free(array);
  fclose(output);
  return 0;
}

