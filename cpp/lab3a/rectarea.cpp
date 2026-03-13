/*2. Write a program to print the area of a rectangle by creating a structure named 'Area' having two functions. 
    First function named as 'setDim' takes the length and breadth of the rectangle as parameters and the second  
     function named as 'getArea' returns the area of the rectangle. Length and breadth of the rectangle are entered 
     through keyboard.*/
#include<iostream>
#include <iomanip>
using namespace std;
struct Area
{
    double length;
    double breadth;
    void setDim(){
        cout << "enter the length: ";
        cin >> length;
        cout << "enter the breadth: ";
        cin >> breadth;
    }
    double getArea(){
        return length*breadth;
    }
}rect;
int main (){
    rect.setDim();
    cout<< "the area for the given rectangle is: "<< rect.getArea();

    return 0;
}