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

struct node* insert_middle(struct restaurants res_list, struct node* head){
    struct node* m = malloc(sizeof(struct node));
    m-> res_list=res_list;
    m->next=NULL;
    struct node* temp = head;
    while(temp->next != NULL) { 
        if (temp->next->res_list.rating < m->res_list.rating) {
           m->next=temp->next;// insert new node between temp and temp->next
           temp->next=m;
           break;
        }
        temp=temp->next;
    }
    if (temp->next == NULL) {
        temp->next=m;
        m->next=NULL;
       // new node add at end
    }
    return m;
}

void print(struct node*list)
{
   for(struct node* n = list; n!=NULL; n=n->next){
    printf("%s open: %d:00 close: %d:00 stars: %g\n",
    n->res_list.name, n->res_list.opening_hour, n->res_list.closing_hour, n->res_list.rating);
   }
}


int main(){
    struct node* head = NULL;
    int num_res;
    printf("How many restuaraunts?\n");
    scanf("%d",&num_res);
    struct restaurants *data;
    data = malloc(sizeof(struct restaurants)*num_res);

    for(int i=0; i<num_res; i++){
    printf("Whats the name of the restaurant?\n");
    scanf("%s", data[i].name);
    printf("How well liked is this restaurant?(rating)\n");
    scanf("%g", &data[i].rating);
    printf("When does the restaurant open?\n");
    scanf("%d", &data[i].opening_hour);
    printf("When does the restaurant close?\n");
    scanf("%d",&data[i].closing_hour);
    }
    

    head = insert_front(data[0], head);
    for(int i=1; i<num_res; i++){
        if (data[i].rating < head->res_list.rating) { 
            insert_middle(data[i],head);
        }
        else{
        head=insert_front(data[i],head);
        }
    }
 

    print(head);
    struct node* current;//from sep 13 slides
    struct node* to_delete;
    current = head;
    to_delete = head;
    while(current!=NULL){
        current=current->next;
        free(to_delete);
        to_delete=current;
    }
    
    free(data);
    return 0;
 }