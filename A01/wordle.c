#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "words.h" // header that defined chooseWord()

int main() {
  srand(time(0));
  const char* word = chooseWord();
 
  char guess[5];
  
  int count = 0;
  while ( count<6){
    printf("Please enter a 5-letter word: ");
    scanf(" %s", guess);

    if (strcmp(guess,word)==0){
      printf("You guessed it! The word is %s ", guess);
      count = 6;
    }

    else if (strcmp(guess,word)!=0){
      for (int i=0; i<5; i++){
        if(guess[i] == word[i]){
            printf("%c is in the word AND in the correct spot!\n", guess[i]);
        }

        else if(strchr(word, guess[i]) != NULL && i!=2){
            printf("%c is in the word (but not in the correct spot)!\n", guess[i]);
        }

        else if(strchr(word, guess[i]) == NULL ){
            printf("%c is NOT in the word.\n", guess[i]);
        }  
      }
    }


    count = count + 1;
  }

  return 0;
}