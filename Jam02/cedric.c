//chandini ragobar and abigail marmer-adams

#include <stdio.h>
#include <stdlib.h>

int main(){
    int n = 10;
    int *values = malloc(sizeof(int) * n);
    for (int j =0; j < n; j++){
        values[j] = j;
    }
    for (int i =0; i < n; i++){
        printf("%d ", values[i]);
    }
    free(values);
    printf("\n");
    return 0;
}