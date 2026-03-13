#include<iostream>
using namespace std;
int fact(int);

int main()
{
    int n;
    cout << "enter the number to be factorized: ";
    cin >> n;
    int result;
    result = fact(n);
    cout << "the result: "<< result;
       return 0;
}
int fact(int n){
    if (n>1)
    return n*fact(n-1);
    else
    return 1;
}