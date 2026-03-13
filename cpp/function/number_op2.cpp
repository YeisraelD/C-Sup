#include<iostream>
using namespace std;
void numdisplay(int n1, float n2){
    cout << "num1 is : "<< n1<< endl;
    cout << "num2 is : "<< n2<< endl;
}
int main()
{
   int num1 = 5;
   float num2 = 5.5;
   numdisplay(num1, num2);
   return 0;
}