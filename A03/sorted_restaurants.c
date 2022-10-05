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
    
    float arr[num_res];

    for(int i=0; i < num_res; i++){
        arr[i]= data[i].rating;
    }

 
    int temp = 0;
    for(int i=0; i < num_res; i++){
        for(int j= 1; j < num_res; j++){
            if (arr[i] < arr[j]){
                temp = arr[i];       
                arr[i] = arr[j];     
                arr[j] = temp;
            }    
        }   
    }
    printf("%g",arr);
    
    for(int i=0; i < num_res; i++){
        for(int j= 0; j < num_res; j++){
            if(arr[i]==data[j].rating){
            head = insert_front(data[j],head);
            }
        }
    }


    print(head);
    return 0;
 }