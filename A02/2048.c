#include <stdio.h>


int main(){
  int matrix[4][4];
  int val;
  for(int i =0; i<4; i++){
    for(int j = 0; j<4; j++){
      scanf("%d",&val);
      matrix[i][j] = val;
    }
  }

  int shift[16];
  int index = 0;

  //char left[] = 'left';
  //char right[] = 'right';
  //char up[] = 'up';
  //char down[] = 'down';
  int move;

  printf("Please enter move");
  scanf("%d", &move);

  if (move == 1){  
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
  }

  else if (move == 2){  
    for(int i = 0; i<=3; i++){
      for(int j = 0; j<=2; j++){
        if (matrix[i][j] == matrix[i][j+1]){
          shift[index] = matrix[i][j] + matrix[i][j+1];
          printf("%d\n",shift[index]);
          index = index + 1;
        }
        else if (matrix[i][0]== matrix[i][3] && matrix[i][1] == 0 && matrix[i][2] == 0){
          shift[index] = matrix[i][0] + matrix[i][3];
          printf("%d\n",shift[index]);
          index = index + 1;
        }
        else if (matrix[i][0]== matrix[i][2] && matrix[i][1] == 0){
          shift[index] = matrix[i][0] + matrix[i][2];
          printf("%d\n",shift[index]);
          index = index + 1;
        }
        else if (matrix[i][1]== matrix[i][3] && matrix[i][2] == 0){
          shift[index] = matrix[i][1] + matrix[i][3];
          printf("%d\n",shift[index]);
          index = index + 1;
        }
      }
    }
  }

  else if (move == 3){  
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
  }

  else if (move == 4){  
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
  }
  
  //printf("%d 1: ,%d 2: ,%d 3: ,%d 4: ",shift[0],shift[1],shift[2],shift[3]);

  int largest = 0;
  for (int i = 0; i<index; i++){
    if (shift[i] > largest){
      largest = shift[i];
      printf("%d/n",shift[i]);
    }
  }

  if (largest == 0){
    for(int i = 0; i<4; i++){
      for(int j = 0; j<4; j++){
        if(matrix[i][j]> largest){
          largest = matrix[i][j];
        }
      }
    }
  }

 printf("The largest value is %d", largest);
  

  return 0;
}

  