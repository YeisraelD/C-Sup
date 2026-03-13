#include<iostream>
using namespace std;

int add(int, int);
int main()
{
   int sum = add(10, 20);
   cout << " 10 + 20 = "<< sum ;

   return 0;
}
int add(int a, int b){
    return(a + b);
}