#include<iostream>
using namespace std;
void swap(int &first, int &second);

int main()
{
    int x= 10;
    int y= 20;
    cout<< "befor swaping: "<< endl;
    cout << "x: "<< x << endl;
    cout << "y: "<< y<< endl;
    swap(x, y);
    cout<< "after swaping "<< endl;
    cout << "x: "<< x<< endl;
    cout << "y: "<< y<< endl;
   return 0;
}
void swap(int &first, int &second){
    int temp;
    temp = first;
    first = second;
    second= temp;

}