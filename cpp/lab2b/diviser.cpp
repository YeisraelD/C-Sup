#include<iostream>
using namespace std;
void calcQuotient(double n1, double n2, double &answer){
    answer = n1/ n2;
}
int main()

{
    double num1,num2,quotient;
    cout << "enter the dividend and diviser respectively: ";
    cin >> num1>>num2;
    calcQuotient(num1, num2, quotient);
    cout << "the quotient for your input is: "<< quotient;
   return 0;
}