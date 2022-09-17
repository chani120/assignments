#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "words.h" // header that defined chooseWord()

int wordle(const char* w){
char guess[5];
  
  int count = 0;
  while ( count<6){
    printf("Please enter a 5-letter word: ");
    scanf(" %s", guess);

    if (strcmp(guess,w)==0){
      printf("You guessed it! The word is %s ", guess);
      count = 6;
    }

    else if (strcmp(guess,w)!=0){
      for (int i=0; i<5; i++){
        if(guess[i] == w[i]){
            printf("%c is in the word AND in the correct spot!\n", guess[i]);
        }

        else if(strchr(w, guess[i]) != NULL){
            printf("%c is in the word (but not in the correct spot)!\n", guess[i]);
        }

        else if(strchr(w, guess[i]) == NULL ){
            printf("%c is NOT in the word.\n", guess[i]);
        }  
      }
    }


    count = count + 1;
  }

  if (strcmp(guess,w)!=0){
  printf("You Lost! The word was:%s ", w);
  }
   return 0;
}

int main() {
  srand(time(0));
  const char* word = chooseWord();
  wordle(word);
  return 0;
}