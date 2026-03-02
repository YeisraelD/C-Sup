#include <stdio.h>
#define PIE 3.14

int main(){
    float radius;
    printf("enter the radius of ur circle: ");
    scanf("%f", &radius);

    float area;
    area = PIE * (radius * radius);

    printf("the area of ur circle is:%2.f ", area);
    

}