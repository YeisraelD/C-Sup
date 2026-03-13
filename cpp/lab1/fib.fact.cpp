#include<iostream>
using namespace std;
int fibonacci(int n=5){
    if (n==1||n==2)
    return 1; //base case
    else
    return fibonacci(n-1)+ fibonacci(n-2);
}
int fact(int x=5){
    if (x>1)
      return x*fact(x-1);
      else
      return 1;
}
int main()
{
   int num;
   cout << "enther an enteger number: ";
   cin >> num;
   if (num>0){
    cout << "the fibonacci sseres for the number is: ";
    for (int i=1; i<=num;i++)
        cout << fibonacci(i)<< " "<< endl;
   }
   else
       cout << "invalid input"<< endl;
       
    cout << "the factorial value: ";
    cout<< fact(num);
   return 0;
}