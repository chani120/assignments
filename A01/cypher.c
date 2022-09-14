#include <stdlib.h> //includes rand() function
#include <stdio.h> //includes printf
#include <string.h>

int main() {
  char word[10];
  int shift;
  
  printf("Please enter a word: ");
  scanf("%s", word);
  printf("Please enter a shift: ");
  scanf(" %d", &shift);

  for (int i=0; i<strlen(word); i++){
      int ascii = word[i]+shift;
      word[i] = ascii;
  }

  printf("Your cypher is: %s ",word );
  return 0;
}
