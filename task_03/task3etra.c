#include <stdio.h>

int main(){
    char first[20];
    char last[20];

    printf("enter ur fist name: ");
    scanf("%s", &first);
    printf("enter ur last name: ");
    scanf("%s", &last);

    printf("hey %s, then %s is ur dada...cool", first, last);
    return 0;
}