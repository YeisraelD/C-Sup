#include<iostream>
#include <cmath>
#include "quadratic.h"
using namespace std;

void findRoots(double a, double b, double c){
    double discriminant = b*b -4*a*c;
    double root1, root2;
    if (discriminant>0){
        root1 = (-b + sqrt(discriminant))/(2*a);
        root2 = (-b - sqrt(discriminant))/(2*a);
        cout<< "the roots are real and distnict:\n";
        cout<< "root1: "<< root1<< "root2"<< root2<< endl;
    }else if (discriminant==0){
        root1 = -b / (2*a);
        cout << "the roots are real and equal: "<< root1<< endl;
    }else{
        double realPart = -b/(2*a);
        double imaginaryPart = sqrt(-discriminant)/(2*a);
        cout << "the roots are a complex number: "<< endl;
        cout << "root1: "<< realPart<< "+"<< imaginaryPart<< endl;
        cout << "root2: "<< realPart<< "-"<< imaginaryPart<< endl;
    }
}
