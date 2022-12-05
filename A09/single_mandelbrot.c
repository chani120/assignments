#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char* argv[]) {
  int size = 480;
  float x_min = -2.0;
  float x_max = 0.47;
  float y_min = -1.12;
  float y_max = 1.12;
  int maxIterations = 1000;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': x_min = atof(optarg); break;
      case 'r': x_max = atof(optarg); break;
      case 't': y_max = atof(optarg); break;
      case 'b': y_min = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <x_min> -r <x_max> -b <y_min> -t <y_max>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", x_min, x_max);
  printf("  Y range = [%.4f,%.4f]\n", y_min, y_max);

  // todo: your work here
  // generate pallet
  srand(time(0));

  // compute image

    // generate pallet
struct ppm_pixel *palette = malloc(sizeof(struct ppm_pixel)* maxIterations);

for(int i=0; i<maxIterations; i++){
  palette[i].red = rand() % 255;
  palette[i].green = rand() %255;
  palette[i].blue = rand()% 255;

}

//generate pixels
struct ppm_pixel * pixels = malloc(sizeof(struct ppm_pixel)*size *size);

//compute time
double timer;
struct timeval tstart, tend; 

  gettimeofday(&tstart, NULL);
//generate mandlebrot
for(int i= 0; i<size; i++){
  for(int j=0; j<size; j++){
    float x_var = (float) (i/size);
    float y_var = (float) (j/size);
    float x0 = x_min + x_var * (x_max - x_min);
    float y0 = y_min + y_var * (y_max - y_min);
  
    float x = 0.0;
    float y = 0.0;
    int count = 0;
    while (count < maxIterations && x*x + y*y < 2*2){
      float temp_x = x*x - y*y + x0;
      y = 2*x*y + y0;
      x = temp_x;
      count++;
    }
    if(count < maxIterations){
      pixels[i * size + j] = palette[count];
    }
    else{
      pixels[i * size + j].red = 0;
      pixels[i * size + j].green = 0;
      pixels[i * size + j].blue = 0;
    }
  }
}
gettimeofday(&tend, NULL);

timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec-tstart.tv_usec)/1.e6;
int timestamp = time(0);

printf("Computed mandelbrot set (%dx%d) in %f seconds\n", size, size,timer);

  // output file
  char fp[100];
  sprintf(fp, "mandelbrot-%d-%d.ppm", size, timestamp);
  printf("Writing file: %s\n", fp);
  write_ppm(fp, pixels, size, size);

  free(pixels);
  free(palette);

}