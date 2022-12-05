#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"
#include "write_ppm.h"

void mandelbrot(struct ppm_pixel *pixels, int col1 , int col2, int row1, int row2, struct ppm_pixel *palette, int size, int maxIterations, float x_min, float y_min, float x_max, float y_max){
  for(int i= row1; i<row2; i++){
    for(int j=col1; j<col2; j++){
      float x = 0.0;
      float y = 0.0;
      int count = 0;

      float x_var = ((float) (j))/size;
      float y_var = ((float) (i))/size;
      float x0 = x_min + x_var * (x_max - x_min);
      float y0 = y_min + y_var * (y_max - y_min);
  
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
}


int main(int argc, char* argv[]) {
  int size = 480;
  float x_min = -2.0;
  float x_max = 0.47;
  float y_min = -1.12;
  float y_max = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;
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

int mem_id;

mem_id= shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) * maxIterations, 0644 | IPC_CREAT);
if (mem_id == -1) {
  perror("Error: cannot initialize shared memory\n");
  exit(1);
}

struct ppm_pixel *palette = shmat(mem_id, NULL, 0);
for(int i=0; i<maxIterations; i++){
  palette[i].red = rand() % 255;
  palette[i].green = rand() %255;
  palette[i].blue = rand()% 255;
}

int shared_mem_id;
shared_mem_id= shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) * size * size, 0644 | IPC_CREAT);
if (shared_mem_id == -1) {
  perror("Error: cannot initialize shared memory\n");
  exit(1);
}

struct ppm_pixel *pixels = shmat(shared_mem_id, NULL, 0);
if(pixels ==(void*)-1){
  perror("Error: cannot access shared memory\n");
    exit(1);
}
/* creates timer to calculate the number of seconds needed to compute the image */
double timer;
struct timeval tstart, tend; 
gettimeofday(&tstart, NULL);

/* for loop that cretes the 4 children */
for (int i= 0; i <4; i++){
  fflush(stdout);
  int pid =  fork();
  if (pid == 0){
    if ( i == 0){
      printf("%d)Sub-image block: cols (0, 240) to rows (0,240)\n", getpid());
      fflush(stdout);
      mandelbrot(pixels, 0, 240, 0, 240,  palette, size,maxIterations, x_min, y_min, x_max,  y_max);
    }

    else if(i == 1){
      printf("%d)Sub-image block: cols (240, 480) to rows (0,240)\n", getpid());
      fflush(stdout);
      mandelbrot(pixels, 240, 480, 0, 240,  palette, size,maxIterations, x_min, y_min, x_max,  y_max);
    }

    else if(i == 2){
      printf("%d)Sub-image block: cols (0, 240) to rows (240,480)\n", getpid());
      fflush(stdout);
      mandelbrot(pixels, 0, 240, 240, 480,  palette, size,maxIterations, x_min, y_min, x_max,  y_max);
    }

    else if(i == 3){
      printf("%d)Sub-image block: cols (240, 480) to rows (240,480)\n", getpid()); 
      fflush(stdout);
      mandelbrot(pixels, 240, 480, 240, 480,  palette, size,maxIterations, x_min, y_min, x_max,  y_max);
    }
     exit(0);
  }
  else{
    printf("Launched child process: %d\n", pid);
  }
}
  /* for loop that makes the children process wait for all to finish */
  for (int i = 0; i < 4; i++) {
    int status;
    int pid = wait(&status);
    printf("Child process complete: %d\n", pid);
  }
gettimeofday(&tend, NULL);

timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec-tstart.tv_usec)/1.e6;
int timestamp = time(0);
printf("Computed mandelbrot set (%dx%d) in %f seconds\n", size, size,timer);

/* outputs the file with the image */
  char fp[100];
  sprintf(fp, "multi-mandelbrot-%d-%d.ppm", size, timestamp);
  printf("Writing file: %s\n", fp);
  write_ppm(fp, pixels, size, size);


/* cleans the shared memory */
  if (shmdt(pixels) == -1) {
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }

  if (shmctl(shared_mem_id, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  } 

  if (shmdt(palette) == -1) {
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }

  if (shmctl(mem_id, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  } 
}  

