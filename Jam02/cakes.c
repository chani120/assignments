//chandini ragobar and abigail marmer-adams

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct flavor {
  float calories;
  char name[32];
};

struct cupcake {
  struct flavor* cake;
  struct flavor* frosting;
};

struct flavor* makeFlavor(const char* name, float cals) {
  struct flavor* c = malloc(sizeof(struct flavor));
  if (c == NULL) {
    printf("ERROR: Out of memory!\n");
    exit(1);
  }

  strcpy(c->name, name);
  c->calories = cals;
  return c;
}

void printCalories(struct cupcake* cakes, int n) {
  int total =0;
  int frosting = 0;
  int cake = 0;
  int most =0;
  struct cupcake highcal;
  for(int i = 0; i <n; i++){
      frosting = cakes[i].frosting->calories;
      cake = cakes[i].cake->calories;
      total = frosting + cake;
      if(total > most){
        most = total;
        highcal = cakes[i];
      }
      printf("Cupcake %d) %s with %s frosting (calores: %d)", i, cakes[i].cake->name, cakes[i].frosting->name, total);
  }
  printf("the cupcake with the most calories is: %s cake with %s frosting", highcal.cake->name, highcal.frosting->name);
}

int main() {
  struct flavor* redVelvet = makeFlavor("red velvet", 200);
  struct flavor* chocolate = makeFlavor("chocolate", 175);
  struct flavor* strawberry = makeFlavor("strawberry", 100);
  struct flavor* creamcheese = makeFlavor("cream cheese", 400);
  
  struct cupcake cakes[3];
  cakes[0].cake = redVelvet;
  cakes[0].frosting = creamcheese; 
  cakes[1].cake = strawberry;
  cakes[1].frosting = chocolate; 
  cakes[2].cake = creamcheese;
  cakes[2].frosting = strawberry; 

  printCalories(cakes, 3);
  free(redVelvet);
  free(chocolate);
  free(strawberry);
  free(creamcheese);
}
