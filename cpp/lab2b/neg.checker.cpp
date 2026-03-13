#include<iostream>
#include <cmath>
using namespace std;
int checker(int n){

    if (n>0){
        return (n*n);
    }else{
        return sqrt(n);
    }
}
int main()
{
    int num;
    cout << "enter an integer number: ";
    cin >> num;
    if (!(cin)){
        cout << "invalid input";
    }else{
        cout << checker(num);
    }
    

   return 0;
}