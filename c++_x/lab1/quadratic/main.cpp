#include<iostream>
#include "quadratic.h"
using namespace std;

int main()
{
    double a,b,c;
    cout << "enter the coefficients a,b, and c: ";
    cin>>a>>b>>c;

    findRoots(a,b,c);
   return 0;
}