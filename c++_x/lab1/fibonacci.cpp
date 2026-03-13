#include<iostream>
using namespace std;
int fibonacci(int n=5){
    if (n==1||n==2)
    return 1; //base case
    else
    return fibonacci(n-1)+ fibonacci(n-2);
}
int main()
{
   int num;
   cout << "enther an enteger number: ";
   cin >> num;
   if (num>0){
    cout << "the fibonacci sseres for the number is: ";
    for (int i=1; i<=num;i++)
        cout << fibonacci(i)<< " ";
   }
   else
       cout << "invalid input"<< endl;
   return 0;
}
