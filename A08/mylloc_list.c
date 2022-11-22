#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int used; //amount of memory in use
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  // TODO: Implement malloc with a free list (See reading for details)
  if(size ==0){
    return NULL;
  }
  
  struct chunk *prev = NULL;
  struct chunk *next = flist;
  
  while(next != NULL){
    if(next->size >= size){
      if(prev != NULL){
        prev->next= next->next;

      }
      else{
        flist = next->next;
      }

      next->used = size;
      return (void*)(next +1);
    }
    else{
      prev = next;
      next = next->next;

    }
  }
  
 void *memory = sbrk(size + sizeof(struct chunk));
  if(memory == (void *)-1){
    return NULL;
  }
  else{
    struct chunk *c = (struct chunk*)memory;
    c->size = size;
    c->used = size;

    return (void*)(c +1);
  }

 }
  

void free(void *memory) {
  
  // TODO: Implement malloc with a free list (See reading for details)
  if(memory!= NULL){

    struct chunk *c= (struct chunk *)((struct chunk *) memory -1);
    c->next = flist;
    flist = c;
  
  return;
  }
}