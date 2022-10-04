#include <stdio.h>
#include <stdlib.h>


struct restaurants{
    char name[64];
    int opening_hour;
    int closing_hour;
    float rating;
};

struct node {
    struct restaurants res_list;
    struct restaurants data;           
    struct node *next;
} ;


struct node* insert_front(struct restaurants res_list, struct node* head){
    struct node* n = malloc(sizeof(struct node));
    if(n == NULL){
        printf("ERROR:OUt of space!\n");
        exit(1);
    }
    n->res_list = res_list;
    n->next = head;
    return n;
};


void print(struct node*list)
{
   for(struct node* n = list; n!=NULL; n=n->next){
    printf("%s open: %d:00 close: %d:00 stars: %g\n",
    n->res_list.name, n->res_list.opening_hour, n->res_list.closing_hour, n->res_list.rating);
   }
}

struct data{
    printf("Whats the name of the restaurant?\n");
    scanf("%s", restaurants.name);
    printf("How well liked is this restaurant?(rating)\n");
    scanf("%g", restaurants.rating);
    printf("When does the restaurant open?\n");
    scanf("%d", restaurants.opening_hour);
    printf("When does the restaurant close?\n");
    scanf("%d",restaurants.closing_hour);
};

int main(){
    struct node* head = NULL;
    int num_res;
    printf("How many restuaraunts?\n");
    scanf("%d",&num_res);
    struct restaurants data;
    for(int i=0; i<=num_res; i++){
    head = insert_front(data,head);
    }
    printf(head);
    return 0;
 }