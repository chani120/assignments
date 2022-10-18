#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char*argv[]) {
  FILE* txt;
  if (argc>2){
    for(int i=0;i<sizeof(&argv);i++){
    printf("%s",argv[i]);
    exit(1);
    }
  }
  txt=fopen(argv[1],"r");
  char stack[sizeof(txt)];
  char data;
  int top=-1;
  char c;
  if (txt==NULL){
    printf("\nCannot Open!");
  }

  int psh(char x);{
    top=top+1;
    data=stack[top];
  }

  int pop(char x);{
    data=stack[top];
    top=top-1;
    return data;
  }

char open = '{';
char close = '}';
int opencol = 0;
int openline = 0;
int closecol =0;
int closecol = 0;

  while((c=fgetc(txt))!=EOF){
    if(strcmp(&c,&open)==0){
      psh(c);
    }
    
    if(strcmp(&c,&close)==0){
      pop(c);
    }
    
  }
  fclose(txt);
  return 0;
}
