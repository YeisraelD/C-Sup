/*Write a structure to store the name, account number and balance of two customers and store their information.
a - Write a function to print the names of all the customers having balance less than $200.
b - Write a function to add $100 in the balance of all the customers having more than $1000 
in their balance and then print the incremented value of their balance. Use pointer as a variable of the structure*/
#include<iostream>
#include<iomanip>
using namespace std;
const int custNum=2;
struct Bank
{ int custNum;
  char name[15];
  long long unsigned int account_num;
  float current_balance;
   
 }customer[custNum];
void lowBalance(Bank* customer[]){
  cout<< "---list of customers with < 200$ balance---"<< endl;
  for (int i=0; i < custNum; i++){
    if (customer[i]->current_balance<200){
      cout << customer[i]->name<< setw(15)<<customer[i]->account_num<< endl;;
    }
  }
}
void addbonus(Bank* customer[]){
  cout << "---Incrementing balance for customers with more than $1000---"<< endl;
  for (int i= 0; i<custNum; i ++){
    if (customer[i]->current_balance >1000){
      customer[i]->current_balance +=100;
      cout<< "Customer name: "<< customer[i]->name<< setw(15)<< customer[i]->current_balance<< endl;;
    } else{
      cout<<"---";
    }
       }

}
int main()
{
  
   for (int i=0; i< custNum; i++){
    cout << "Enter customer "<< i+1<< " name: ";
    cin >> customer[i].name;
    cout << "Enter customer "<< i+1<< " account number: ";
    cin >> customer[i].account_num;
    cout << "Enter customer "<< i+1<< " balance: ";
    cin >> customer[i].current_balance;
   
   }
   lowBalance(&customer);
   cout << endl;
   addbonus(&customer);

 
  cout << "---full current customers detil---"<< endl;
  cout << "Customer Name"<<setw(8)<<"Account number "<< setw(8)<< " Current balance"<< endl;
  for(int i =0; i< custNum; i++){
    cout << customer[i].name<< setw(15)<< customer[i].account_num<<setw(15)<<customer[i].current_balance<< endl;
  }

   return 0;
}
