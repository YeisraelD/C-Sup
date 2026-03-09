#include <stdio.h>

int main(){
    float seconds;

    //get the sec from the user
    printf("enter the amount the second: ");
    scanf("%f",  &seconds);

    //init our arithmetic vars
    float hrs;
    float mins;
    float remaining_seconds;

    //make sure the hours value is a whole number that doesn't consider the decimal by using the (int) operation. 
    //for instance, 1.2 hours will be stored in hours as 1.0 here
    hrs = (int)(seconds / 3600);

    //repeat for mins
    mins = (int)((seconds - (hrs * 3600))/60);

   //remaining_seconds is simply what's leftover
   remaining_seconds = (seconds - (hrs * 3600) - (mins * 60));
    printf("%0.0f seconds is equal to %0.0f hours, %0.0f minutes, and %0.0f seconds.", seconds, hrs, mins, remaining_seconds);

    return 0;
}