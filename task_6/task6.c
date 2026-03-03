#include <stdio.h>

int main(){
    // init our vars and gete values for them
    int numerator, denominator;
    printf("enter a numerator: ");
    scanf("%d", &numerator);
    printf("enter the denominator: ");
    scanf("%d", &denominator);

    if(numerator % denominator == 0){
        printf("There is no a remainder!");
    }
    else{
        printf("There is a remainder!");
    }
    return 0;

}