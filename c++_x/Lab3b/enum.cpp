//Show how to declare the following constants using an enum statement: WINTER =1, SPRING = 2, SUMMER = 3 and FALL = 4.

#include<iostream>
using namespace std;
enum season{WINTER =1, SPRING, SUMMER , FALL};
int main()
{
    season current_season= SPRING;
    cout<< "The current season is: "<< current_season<< endl;
   return 0;
}