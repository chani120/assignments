#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

void thread_mand((void*)arguments){
  struct args thread_args = (struct args)arguments;
  long double xvar = 0;
  long double yvar = 0;
  long double x1 = 0;
  long double y1 = 0;
  int iteration = 0;
  long double x = 0, 
  long double y = 0;
  long double xtemp = 0;
  double timer = 0;
  struct timeval timestart, timeend;
 
  for (int i = 0; i < thread_args.size; i++){ // row
    for (int j = 0; j <thread_args.size; j++){ //column
      xvar = (float)i / thread_args.size;
      yvar = (float)j / thread_args.size;
      x1 = thread_args.x_min + (xvar * (thread_args.x_max - thread_args.x_min));
      y1 = thread_args.y_min + (yvar * (thread_args.y_max - thread_args.y_min));

      x = 0;
      y = 0;
      iteration = 0;

      while((iteration < thread_args.maxIterations)&&(x*x + y*y < 4)){
        xtemp = x*x - y*y + x1;
        y = 2*x*y + y1;
        x = xtemp;
        iteration++;
      }

      if (iteration < thread_args.maxIterations){
        thread_args.image[i][j] = thread_args.pal[iteration];
      }
      else{
        thread_args.image[i][j].red = 0;
        thread_args.image[i][j].green = 0;
        thread_args.image[i][j].blue = 0;
      }

    }
  }
}

int main(int argc, char* argv[]) {
  int size = 480;
  float x_min = -2.0;
  float x_max = 0.47;
  float y_min = -1.12;
  float y_max = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;
  int col1;
  int col2;
  int row1;
  int row2;
  struct ppm_pixel* pal;
  struct ppm_pixel** image; 

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': x_min = atof(optarg); break;
      case 'r': x_max = atof(optarg); break;
      case 't': y_max = atof(optarg); break;
      case 'b': y_min = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <x_min> -r <x_max> "
        "-b <y_min> -t <y_max> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", x_min, x_max);
  printf("  Y range = [%.4f,%.4f]\n", y_min, y_max);

  struct ppm_pixel** image = (struct ppm_pixel**)malloc(size*size*sizeof(struct ppm_pixel));
  for(int i = 0; i < size; i++){
    image[i] = (struct ppm_pixel*)malloc(size*sizeof(struct ppm_pixel));
  }


  srand(time(0));
  struct ppm_pixel* pal = (struct ppm_pixel*)malloc(maxIterations*sizeof(struct ppm_pixel));

  for (int i = 0; i < maxIterations; i++){
    pal[i].red = 100 + (rand() % 155);
    pal[i].green = rand() % 150;
    pal[i].blue = 100 + (rand() % 155);
  }
  pthread thread1_id;
  struct args args1;
  args1.col1 = 0;
  args1.row1 = 0;
  args1.col2 = 240;
  args1.row2 = 240;
  args1.size = 400;
  args1.maxIterations = 1000;
  args1.pal = pal;
  args1.image = image;
  args1.x_max = x_max;
  args1.y_max = y_max;
  args1.x_min = x_min;
  args1.y_min = y_min;
  pthread_create(&thread1_id, NULL, thread_mand, args1);
  pthread thread2_id;
  struct args args2;
  pthread_create(&thread2_id, NULL, thread_mand, args2);
  pthread thread3_id;
  struct args args3;
  pthread_create(&thread3_id, NULL, thread_mand, args3);
  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);
  pthread_join(thread3_id, NULL);


  printf("Computed mandelbrot set (%d,%d)\n", size, size); \
  const char* outputfile = "testt.ppm\0";
  write_ppm_2d(outputfile, image, size, size);
  printf("Writing to file: %s\n", outputfile);
  for(int i = 0; i < size; i++){
    free(image[i]);
  }
  free(image);
  free(pal);
}

