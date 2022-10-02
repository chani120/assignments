#include <stdio.h>
#include <stdlib.h>


/* Structure to pass multiple values onto stack */
typedef struct restaurants{
    char name[64];
    int opening_hour;
    int closing_hour;
    float rating;
}restaurants;

 typedef struct node {
    struct restaurants data;           /*  --> Changes done here */
    struct node *pNext; /* Reference to the next node address */
} NODE;

/*Structure declares pointers for front and back of the list*/
typedef struct LIST {
    NODE *front;
    NODE *back;
} LIST;


void func(restaurants *q)
{
    NODE *p = malloc(sizeof(NODE));
    p->data.name[] = q->name[];
    p->data.opening_hour = q->opening_hour;
    p->data.closing_hour = q->closing_hour;
    p->data.rating = q->rating;

    printf("%s %d %d %g",p->data.name,p->data.opening_hour,p->data.closing_hour, p->data.rating);
    free(p);
}

int main(){
  int nres;
  printf("How many restuaraunts?\n");
  scanf("%d",nres);
  restaurants *q = malloc(sizeof(restaurants));
  node* h=NULL;
  h=list(nres);
  for(int i=1; i<=nres; i++){
    printf("Whats the name of the restaurant?\n");
    q->name[64]= scanf("%s",restaurants.name);
    printf("How well liked is this restaurant?(rating)\n");
    q->rating = scanf("%g",rating);
    printf("When does the restaurant open?\n");
    q->opening_hour = scanf("%d",restaurants.opening_hour);
    printf("When does the restaurant close?\n");
    q->closing_hour = scanf("%d",restaurants.closing_hour);
    func(q);
    }
    free(p);
    return 0;
 }