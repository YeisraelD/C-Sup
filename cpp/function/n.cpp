#include<iostream>
using namespace std;
void cal(double, double, double, double&, double&);

int main()
{
    double first, second, thired, sum, product;
    cout << "enter the first, second and the tired numbers"<< endl;
    cin >> first>>second>> thired;
    cal(first, second, thired, sum, product);
    cout << " the sum: "<< sum<< endl;
    cout << "the pro: "<< product;
   return 0;
}
void cal(double num1, double num2, double num3, double& total, double& product){
    total = num1 + num2 + num3;
    product = num1*num2*num3;
}