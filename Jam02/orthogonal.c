//chandini ragobar and abigail marmer-adams

#include <stdio.h>
#include <stdlib.h>

int main() {
  float vector1[3];
  float vector2[3];
  float dotvalue = 0;
  float epsilon = 0.000001;
  printf("Enter the first vector: \n");
  scanf("%g %g %g", &vector1[0], &vector1[1], &vector1[2]);
  printf("Enter the second vector: \n");
  scanf("%g %g %g", &vector2[0], &vector2[1], &vector2[2]);
  dotvalue = vector1[0]*vector2[0] + vector1[1]*vector2[1] + vector1[2]*vector2[2];
  printf("the dot product is: %g", dotvalue);
  if((dotvalue > -epsilon) && (dotvalue < epsilon)){
    printf(" The vectors are perpendicular!");
  }
  else{
    printf("The vectors are not perpendicular");
  }
  
  return 0;
}
