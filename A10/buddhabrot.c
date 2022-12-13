#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

hread mutex_t mutex,
pthread barrier_t barrier;

struct thread_data{
int col1;
int col2;
int row1;
int row2;
struct ppm_pixel *pal;
int size;
int maxIterations;
float x_min;
float y_min;
float x_max;
float y_max;
int *mem;
int *count;
int *con;
};

void mandelbrot(struct ppm_pixel *pixels, int col1 , int col2, int row1, int row2, struct ppm_pixel *pal, int size, int maxIterations, float x_min, float y_min, float x_max, float y_max, int *mem, int *inter, int *con){
  for(int i= row1; i<row2; i++){
    for(int j=col1; j<col2; j++){
      float x = 0.0;
      float y = 0.0;
      int c = 0;

      float x_var = ((float) (i))/size;
      float y_var = ((float) (j))/size;
      float x0 = x_min + x_var * (x_max - x_min);
      float y0 = y_min + y_var * (y_max - y_min);
  
      while (count < maxIterations && x*x + y*y < 2*2){
        float temp_x = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = temp_x;
        c++;
      }
    }
    }
  }

 void formula2(int id, struct ppm_pixel *pix, int col1 , int col2, int row1, int row2, struct ppm_pixel *pal, int size, int maxIterations, float x_min, float y_min, float x_max, float y_max, int *mem, int *count, int *con){
  for(int i= row1; i<row2; i++){
    for(int j=col1; j<col2; j++){
      float x = 0.0;
      float y = 0.0;

      float x_var = ((float) (i))/size;
      float y_var = ((float) (j))/size;
      float x0 = x_min + x_var * (x_max - x_min);
      float y0 = y_min + y_var * (y_max - y_min);
  
      while (x*x + y*y < 2*2){
        float temp_x = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = temp_x;

        int yrow = round(size * (y - y_min)/(y_max - y_min));
        int xcol = round(size * (x - x_min)/(x_max - x_min));
        if(yrow<0 || yrow>=size){
          continue;
        }
        if(xcol<0 || xcol>=size){
          continue;
        }
        
        pthread_mutex_lock(&mutex);
        count(yrow * size + xcol) += 1;
        if(count[yrow * size + xcol]> *con){
          *con = count[yrow * size + xcol];
        }
        pthread_mutex_unlock(&mutex);
      }
    }
  }
 }

void formula3(int id, struct ppm_pixel *pix, int col1 , int col2, int row1, int row2, struct ppm_pixel *pal, int size, int maxIterations, float x_min, float y_min, float x_max, float y_max, int *mem, int *count, int *con){
  float gamma = 0.681;
  float factor = 1.0/gamma;
  for(int i= row1; i<row2; i++){
    for(int j=col1; j<col2; j++){
      float val = 0.0;
      
      if(count[i * size +j]>0){
        val = log(count[i * size +j])/log(*con);
        val = pow(val,factor);
      }
      pix[i * size + j].red = val * 255;
      pix[i * size + j].green = val * 255;
      pix[i * size + j].blue = val * 255;
      }
    }
  }
 


void *do_formula(void *userdata){
  struct thread_data *data = (struct thread_data *) userdata;
  formula1(data->id, data->pix, data->col1, data->col2, data->row1, data->row2, data->pal, data->size, data->maxIterations, data->x_min, data->x_max, data->y_max, data->y_min, data->mem, data->count, data ->con);
  formula2(data->id, data->pix, data->col1, data->col2, data->row1, data->row2, data->pal, data->size, data->maxIterations, data->x_min, data->x_max, data->y_max, data->y_min, data->mem, data->count, data ->con);
  pthread_barrier_wait(&barrier);
  formula3(data->id, data->pix, data->col1, data->col2, data->row1, data->row2, data->pal, data->size, data->maxIterations, data->x_min, data->x_max, data->y_max, data->y_min, data->mem, data->count, data ->con);
return (void*) NULL;
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
  srand(time(0));
  struct ppm_pixel *pal=malloc(sizeof(struct ppm_pixel)*maxIterations);
  for(int i=0;i<maxIterations; i++){
    pal[i].red=rand() %255;
    pal[i].green=rand() %255;
    pal[i].blue=rand() %255;
  }
  struct ppm_pixel *pix=malloc(sizeof(struct ppm_pixel)*size*size);
  int *mem,*count=malloc(sizeof(int)*size*size);
  for(int i=0;i<size;i++;){
    for(int i=0;i<size;i++;){
      count[i][j]=0
    }
  }
  int con=0;
  double t;
  struct timeval tstart,tend;
  gettimepfday(&tstart,NULL);
  pthread_t threads[4];
  pthread_mutex_init(&mutex, NULL);
  pthread_barrier_init(&barrier,NULL,4);
  struct thread_data data[4];
  for(int i=0;i<4;i++){
    if(i=0){
      printf("%d. Sub image block: collumns 0,240 to rows 0,240")
      data[i].id=1;
      data[i].pix=pix;
      data[i].col1=0;
      data[i].col2=240;
      data[i].row1=0;
      data[i].row2=240;
      data[i].pal=pal;
      data[i].maxIterations=maxIterations;
      data[i].x_min=x_min;
      data[i].y_min=y_min;
      data[i].x_max=x_max;
      data[i].y_max=y_max;
      data[i].mem=mem;
      data[i].count=count;
      data[i].con=&con;
      pthread_create(&threads[i],NULL,do_formula,(void*)&data[i])
    }
    if(i=1){
      printf("%d. Sub image block: collumns 240,480 to rows 0,240")
      data[i].id=i;
      data[i].pix=pix;
      data[i].col1=0;
      data[i].col2=240;
      data[i].row1=0;
      data[i].row2=240;
      data[i].pal=pal;
      data[i].maxIterations=maxIterations;
      data[i].x_min=x_min;
      data[i].y_min=y_min;
      data[i].x_max=x_max;
      data[i].y_max=y_max;
      data[i].mem=mem;
      data[i].count=count;
      data[i].con=&con;
      pthread_create(&threads[i],NULL,do_formula,(void*)&data[i])
    }
if(i=2){
      printf("%d. Sub image block: collumns 0,240 to rows 0,240")
      data[i].id=i;
      data[i].pix=pix;
      data[i].col1=0;
      data[i].col2=240;
      data[i].row1=240;
      data[i].row2=480;
      data[i].pal=pal;
      data[i].maxIterations=maxIterations;
      data[i].x_min=x_min;
      data[i].y_min=y_min;
      data[i].x_max=x_max;
      data[i].y_max=y_max;
      data[i].mem=mem;
      data[i].count=count;
      data[i].con=&con;
      pthread_create(&threads[i],NULL,do_formula,(void*)&data[i])
    }
if(i=3){
      printf("%d. Sub image block: collumns 0,240 to rows 0,240")
      data[i].id=i;
      data[i].pix=pix;
      data[i].col1=240;
      data[i].col2=480;
      data[i].row1=240;
      data[i].row2=480;
      data[i].pal=pal;
      data[i].maxIterations=maxIterations;
      data[i].x_min=x_min;
      data[i].y_min=y_min;
      data[i].x_max=x_max;
      data[i].y_max=y_max;
      data[i].mem=mem;
      data[i].count=count;
      data[i].con=&con;
      pthread_create(&threads[i],NULL,do_formula,(void*)&data[i])
    }
  }
  for(int i=0;i<4;){
    pthread_join(threads[i],NULL);
  }
  gettimeofday(&tend,NULL);
  t=tend.tv_sec-tstart.tv_sec+(tend.tv_usec-tstart.tv_usec)/1.e6;
  int timestamp=time(0)
  printf("Buddahbrot set %dx%d computed!It took %f seconds\n",size,size,t)
  write_ppm(fp,pix,size,size);
  pthread_mutex_destroy(&mutex);
  pthread_barrier_destroy(&barrier);
  free(pix);
  free(pal);
  free(mem);
  free(count);

}