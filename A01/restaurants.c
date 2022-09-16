#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct restaurant{
char name[64];
int opening_hour;
int closing_hour;
float rating;
};

int main() {
struct restaurant restaurant1, restaurant2, restaurant3;

strcpy(restaurant1.name, "Red Lobster");  
restaurant1.opening_hour = 10;                
restaurant1.closing_hour = 19;                   
restaurant1.rating = 4.7;               

strcpy(restaurant2.name, "Olive Garden");  
restaurant2.opening_hour = 12;                
restaurant2.closing_hour = 23;                   
restaurant2.rating = 4.5; 

strcpy(restaurant3.name, "Outback Steakhouse");  
restaurant3.opening_hour = 10;                
restaurant3.closing_hour = 1;                   
restaurant3.rating = 4.3; 

printf("Welcome to Chandini Struct's Restarant List!\nWhat hour is it (24 hr clock)? ");

int current_time;
scanf("%d", &current_time);

printf("(0) %s  open: %d:00  close: %d:00  stars: %g\n(1) %s  open: %d:00  close: %d:00  stars: %g\n(2) %s  open: %d:00  close: %d:00  stars: %g\n",
        restaurant1.name, restaurant1.opening_hour, restaurant1.closing_hour, restaurant1.rating,
        restaurant2.name, restaurant2.opening_hour, restaurant2.closing_hour, restaurant2.rating,
        restaurant3.name, restaurant3.opening_hour, restaurant3.closing_hour, restaurant3.rating);

int arr[] = {0,1,2};
int option;
printf("What restaurant do you want to visit? ");
scanf(" %d", &option );

  if (option == 0){
    if (current_time>=restaurant1.opening_hour && current_time<restaurant1.closing_hour){  
      printf("Red Lobster is an excellent choice! It will be open for %d more hours", abs(restaurant1.closing_hour-current_time));
    }
    else if (current_time<restaurant1.opening_hour){
      printf("Red Lobster is not open until %d:00", restaurant1.opening_hour);
    }
    else if (current_time>restaurant1.closing_hour){
      printf("Red Lobster closed at %d:))", restaurant1.closing_hour);
    }
  }

  else if (option == 1){
    if (current_time>=restaurant2.opening_hour && current_time<restaurant2.closing_hour){  
      printf("Olive Garden is an excellent choice! It will be open for %d more hours", abs(restaurant2.closing_hour-current_time));
    }
    else if (current_time<restaurant2.opening_hour){
      printf("Olive Garden is not open until %d:00", restaurant2.opening_hour);
    }
    else if (current_time>restaurant2.closing_hour){
      printf("Olive Garden closed at %d:00", restaurant2.closing_hour);
    }
  }


  else if (option == 2){
    if (current_time>=restaurant3.opening_hour && current_time<restaurant3.closing_hour){  
      printf("Outback Steakhouse is an excellent choice! It will be open for %d more hours", abs(restaurant3.closing_hour-current_time));
    }
    else if (current_time<restaurant3.opening_hour){
      printf("Outback Steakhouse is not open until %d:00", restaurant3.opening_hour);
    }
    else if (current_time>restaurant3.closing_hour){
      printf("Outback Steakhouse closed at %d:00", restaurant3.closing_hour);
    }  
  }

return 0;
}


