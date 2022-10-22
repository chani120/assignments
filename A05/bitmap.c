#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): \n%lx\n", img); 
  unsigned long x;
  for (int i = 63; i >= 0; i--){
    x = (img &(0x1ul << i))>>i;
    if(x > 0){
      printf("@");
    }
    else {
      printf(" ");
    }
    if((i%8)==0){
      printf("\n");
    }
  }
  return 0;
}
