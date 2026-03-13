#include"B.h"
#include<iostream>
#include <iomanip>
using namespace std;
void serchCustomer(Bank customer[]){
    long long unsigned int Anum;
    cout << "Serch a customer by their account number."<<endl;
    cout<< "Enter the Account number: ";
    cin>> Anum;
    ifstream file("record.txt");
    string line;
     getline(file, line);
    for (int i =0; i< custNum; i++){
    file>> customer[i].Fname>>customer[i].Lname>>customer[i].account_num>>customer[i].balance;
  }
      file.close();
 
    bool found= false;
    for (int i=0; i< custNum; i++){
        if (Anum == customer[i].account_num){
            cout << "--- Customer "<< i +1<< " ---"<< endl;
            cout << "First name: "<< customer[i].Fname<< endl;
            cout << "Last name: "<<customer[i].Lname<< endl;
            cout<< "Current Balance: "<< customer[i].balance<< endl;
            found= true;
            break;
        }
    }
    if (!found){
        cout << "The customer does not exist." <<endl;
    }
}
int main(){
    serchCustomer(customer);
   return 0;
}