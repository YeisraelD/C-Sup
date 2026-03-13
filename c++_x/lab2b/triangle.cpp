#include<iostream>
#include <cmath>
using namespace std;
void tringle(float s1, float s2, float &s3){
      s1= 4.5;
      s2= 3.3;
      
      s3= sqrt((s1*s1) + (s2*s2));
}
int main()
{
    float h1,h2,h3;
    cout << "enter the two sides of the triangl: ";
    cin >>h1>>h2;
  tringle(h1, h2, h3);
    cout << "the thired side lengh of the triangle is: "<< h3;
   return 0;
}