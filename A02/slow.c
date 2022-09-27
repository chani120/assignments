#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

int main() {
  
  int length;
  char phrase[32];

  printf("Please enter pause length: ");
  scanf("%d", &length);
  printf("Please enter a phrase: ");
  scanf(" %s", phrase);

  char *ent = NULL;
  ent = malloc(sizeof(char) * 40);      

  int x = 0;
  int y = 0;

  while (y < strlen(phrase)){
    ent[x] = phrase[y];
    y = y + 1;
    for (int j=1; j<=length; j++){
        ent[x+j]='.'; }
    x = x + length + 1;
    
  }
  ent[x] = '\0';
  printf(" %s ", ent);
  free(ent);
  return 0;
}
