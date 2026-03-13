#include<iostream>
using namespace std;
void fun(int);
int m2= 66;

int main()
{
    int m1= 1, m2=21;
    fun(m1);
    cout << m1<< " "<< ::m2 << endl;
   return 0;
}
void fun(int a){
    int m2;
    m2 = a +9, a++;
    cout << a << " "<< m2<< ", ";
}