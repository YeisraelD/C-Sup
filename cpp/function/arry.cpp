#include<iostream>
using namespace std;
void readarry(int arry[5]){
    for (int i=0; i<5; i++){
        cout << "enter the "<< i+1<< "element: ";
        cin >> arry[i];
    }
}
void display(int arry[5]){
    for(int i= 0; i< 5; i++){
        cout << "element "<< i+1 << " "<<arry[i]<< endl;
    }
}
double avrg(int arry[5]){
    int sum=0;
    for(int i =0; i<5; i++){
        sum+=arry[i];
    }
 
    return(double(sum)/5);
}
int main()
{
    int balance[5];
    readarry(balance);
    display(balance);
    double avg=avrg(balance);
    cout << "Average: "<< avg;
   return 0;
}