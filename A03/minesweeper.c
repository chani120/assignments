#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
  srand(time(0));
  int m;
  m = atoi(argv[1]);
  int n;
  n = atoi(argv[2]);
  float p;
  p = atof(argv[3]);
  int *board = malloc(m*n*sizeof(int));

  printf("Board:\n");

  srand(time(0));

  for(int i = 0; i<m; i++){
    for(int j = 0; j<n; j++){   
      float mine = (float)rand()/RAND_MAX;
      if (mine <=p){    
        board[i*n + j] = 'X';   
      }
      else {
        board[i*n + j] = '.';      
      }
      printf("%c",board[i*n + j]);
    }   
    printf("\n");     
  }
  

  int *neighbors = malloc(m*n*sizeof(int));
  for(int i = 0; i<m; i++){
    for(int j = 0; j<n; j++){
        neighbors[i*n + j] = '0'; 
    } 
  }
  
char add = '1';

//check below
  for(int i = 0; i<m-1; i++){
    for(int j = 0; j<n; j++){
      if (board[(i*n +1) + j] == 'X'){    
        neighbors[i*n + j] = (int)(neighbors[i*n + j]-'0') + (int)(add-'0'); 
        neighbors[i*n + j] = neighbors[i*n + j] +'0';
      }  
    }
  }

//check above
  for(int i = 1; i<m; i++){
    for(int j = 0; j<n; j++){
      if (board[(i*n -1) + j] == 'X'){    
        neighbors[i*n + j] = (int)(neighbors[i*n + j]-'0') + (int)(add-'0'); 
        neighbors[i*n + j] = neighbors[i*n + j] +'0';
      }  
    }
  }

//check left
  for(int i = 0; i<m; i++){
    for(int j = 1; j<n; j++){     
      if (board[i*n + (j-1)] == 'X'){    
        neighbors[i*n + j] = (int)(neighbors[i*n + j]-'0') + (int)(add-'0');
        neighbors[i*n + j] = neighbors[i*n + j] +'0';
      }  
    }
  }

//check right
  for(int i = 0; i<m; i++){
    for(int j = 0; j<n-1; j++){
      if (board[i*n + (j+1)] == 'X'){    
        neighbors[i*n + j] = (int)(neighbors[i*n + j]-'0') + (int)(add-'0');
        neighbors[i*n + j] = neighbors[i*n + j] +'0';
      }  
    }
  }

//check NW
  for(int i = 1; i<m; i++){
    for(int j = 1; j<n; j++){
      if (board[(i*n -1)+ (j-1)] == 'X'){    
        neighbors[i*n + j] = (int)(neighbors[i*n + j]-'0') + (int)(add-'0');
        neighbors[i*n + j] = neighbors[i*n + j] +'0';
      }  
    }
  }

//check NE
  for(int i = 0; i<m-1; i++){
    for(int j = 1; j<n; j++){
      if (board[(i*n +1) + (j-1)] == 'X'){    
        neighbors[i*n + j] = (int)(neighbors[i*n + j]-'0') + (int)(add-'0');
        neighbors[i*n + j] = neighbors[i*n + j] +'0';
      }  
    }
  }

//check SW
  for(int i = 1; i<m; i++){
    for(int j = 0; j<n-1; j++){
      if (board[(i*n -1) + (j+1)] == 'X'){    
        neighbors[i*n + j] = (int)(neighbors[i*n + j]-'0') + (int)(add-'0');
        neighbors[i*n + j] = neighbors[i*n + j] +'0';
      }  
    }
  }

//check SE
  for(int i = 0; i<m-1; i++){
    for(int j = 0; j<n-1; j++){
      if (board[(i*n +1) + (j+1)] == 'X'){    
        neighbors[i*n + j] = (int)(neighbors[i*n + j]-'0') + (int)(add-'0');
        neighbors[i*n + j] = neighbors[i*n + j] +'0';
      }  
    }
  }


//check bombs
 for(int i = 0; i<m; i++){
    for(int j = 0; j<n; j++){
      if (board[i*n + j] == 'X'){    
        neighbors[i*n + j] = 'X'; 
      }  
   }
 }
  
 
  printf("\nNeighbors:\n");

  for(int i = 0; i<m; i++){
    for(int j = 0; j<n; j++){   
      printf("%c",neighbors[i*n + j]);
    }   
    printf("\n");     
  }

  free(board);
  free(neighbors);
  
}


