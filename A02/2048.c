#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

int main(){
  int matrix[4][4];
  int value;
  for(int i =0; i<4; i++){
    for(int j = 0; j<4; j++){
      scanf("%d",&value);
      matrix[i][j] = value;
    }
  }

  int shift[16];
  int index = 0;


//shift left
    for(int i = 0; i<=3; i++){
      for(int j = 3; j<=1; j--){

        if (matrix[i][0]== matrix[i][3] && matrix[i][1] == 0 && matrix[i][2] == 0){
          shift[index] = matrix[i][0] + matrix[i][3];
          index = index + 1;
        }
        else if (matrix[i][0]== matrix[i][2] && matrix[i][1] == 0){
          shift[index] = matrix[i][0] + matrix[i][2];
          index = index + 1;
        }
        else if (matrix[i][1]== matrix[i][3] && matrix[i][2] == 0){
          shift[index] = matrix[i][1] + matrix[i][3];
          index = index + 1;
        }        
        else if (matrix[i][j] == matrix[i][j-1]){
          shift[index] = matrix[i][j] + matrix[i][j-1];
          index = index + 1;
        }
      }
    }
  
//shift right
    for(int i = 0; i<=3; i++){
      for(int j = 0; j<=2; j++){
        if (matrix[i][j] == matrix[i][j+1]){
          shift[index] = matrix[i][j] + matrix[i][j+1];
          index = index + 1;
        }
        else if (matrix[i][0]== matrix[i][3] && matrix[i][1] == 0 && matrix[i][2] == 0){
          shift[index] = matrix[i][0] + matrix[i][3];
          index = index + 1;
        }
        else if (matrix[i][0]== matrix[i][2] && matrix[i][1] == 0){
          shift[index] = matrix[i][0] + matrix[i][2];
          index = index + 1;
        }
        else if (matrix[i][1]== matrix[i][3] && matrix[i][2] == 0){
          shift[index] = matrix[i][1] + matrix[i][3];
          index = index + 1;
        }
      }
    }
  
//shift up
    for(int i = 3; i>=1; i--){
      for(int j = 0; j<=3; j++){
        if (matrix[0][j]== matrix[2][j] && matrix[1][j] == 0){
          shift[index] = matrix[0][j] + matrix[2][j];
          index = index + 1;
        }
        else if (matrix[0][j]== matrix[3][j] && matrix[1][j] == 0 && matrix[2][j] == 0){
          shift[index] = matrix[0][j] + matrix[3][j];
          index = index + 1;
        }
        else if (matrix[1][j]== matrix[3][j] && matrix[2][j] == 0){
          shift[index] = matrix[1][j] + matrix[3][j];
          index = index + 1;
        }
        else if (matrix[i][j] == matrix[i-1][j]){
          shift[index] = matrix[i][j] + matrix[i-1][j];
          index = index + 1;
        }
      }
    }

//shift down
    for(int i = 0; i<=2; i++){
      for(int j = 0; j<=3; j++){
        if (matrix[i][j] == matrix[i+1][j]){
          shift[index] = matrix[i][j] + matrix[i+1][j];
          index = index + 1;
        }
        else if (matrix[0][j]== matrix[3][j] && matrix[1][j] == 0 && matrix[2][j] == 0){
          shift[index] = matrix[0][j] + matrix[3][j];
          index = index + 1;
        }
        else if (matrix[0][j]== matrix[2][j] && matrix[1][j] == 0){
          shift[index] = matrix[0][j] + matrix[2][j];
          index = index + 1;
        }
        else if (matrix[1][j]== matrix[3][j] && matrix[2][j] == 0){
          shift[index] = matrix[1][j] + matrix[3][j];
          index = index + 1;
        }
      }
    }
  

  int largest = 0;
  for (int i = 0; i<index; i++){
    if (shift[i] > largest){
      largest = shift[i];
    }
  }

  if(largest == 0){
    for(int i = 0; i<4; i++){
      for(int j = 0; j<4; j++){
        if(matrix[i][j] > largest){
          largest = matrix[i][j];
        }
      }
    }
  }
  
 printf("The largest value is %d ", largest);
  
  return 0;
}

  