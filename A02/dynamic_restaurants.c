#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct restaurant{
char name[64];
int opening_hour;
int closing_hour;
float rating;
};

int main(){

struct restaurant *res_list;      
res_list = malloc(sizeof(res_list)*100);   

printf("Enter a number of restaurants:");
int num_res;
scanf("%d", &num_res);

for (int i = 0; i < num_res; i++){
       
        printf("Enter a name:");
        scanf(" %[^\n]%*c", res_list[i].name);
        printf("Open time:");
        scanf(" %d", &res_list[i].opening_hour);
        printf("Close time:");
        scanf(" %d", &res_list[i].closing_hour);     
        printf("Stars:");
        scanf(" %g", &res_list[i].rating);
}

printf("Welcome to Chandini Struct's Restaurant List!\n");

for (int i = 0; i < num_res; i++){
        printf("%d) %s open: %d:00 close: %d:00 stars: %g\n",
        i, res_list[i].name, res_list[i].opening_hour, res_list[i].closing_hour, res_list[i].rating);
   
}

free(res_list);

return 0;
}


