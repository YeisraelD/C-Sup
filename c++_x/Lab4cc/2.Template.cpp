#include<iostream>
using namespace std;
template <typename T1, typename T2>
double floatPointDivide(T1 x, T2 y){
    return 1.0 * x/ y;
}
int main()
{
   int a= 3;
   int b= 4;
   cout << floatPointDivide(a, b)<< endl;
   float x= 2.2;
   int y = 3;
   cout << floatPointDivide(x,y);
   return 0;
}