#include <iostream>
using namespace std;
int squre(int &x);
double squre(double &y);
int main (){
    int num1 = 5;
    double num2 =5.5;
    cout<< "integer squre: "<<squre(num1);
    cout << endl;
    cout << "double squre: "<<squre(num2);
    return 0;
}
int squre(int &x){
    return (x*x);
}
double squre(float &y){
    return (y*y);
}
