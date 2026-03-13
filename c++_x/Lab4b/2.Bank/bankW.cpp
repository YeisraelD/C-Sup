#include "B.h"
#include<iostream>
#include <iomanip>
using namespace std;
void getRec(Bank customer[]){
    ofstream file("record.txt");
    file <<"First name"<< setw(14)
         << "Last name"<<setw(20)
         << "Account number"<< setw(20)
         << "Current Balance"<<endl;
    for (int i=0; i<custNum; i++){
        cout << "--- Customer "<< i +1<< " ---"<< endl;
        cout << "First name: ";
        cin >> customer[i].Fname;
        cout << "Last name: ";
        cin >> customer[i].Lname;
        cout << "Account number: ";
        cin>> customer[i].account_num;
        cout<< "Current Balance: ";
        cin >> customer[i].balance;
        file << customer[i].Fname<<setw(15)
             << customer[i].Lname<<setw(15)
             << customer[i].account_num<<setw(17)
             <<customer[i].balance<< endl;
    }
    file.close();
}
int main(){
    getRec(customer);
   return 0;
}