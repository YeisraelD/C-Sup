#include<iostream>
#include <iomanip>
#include "company.h"
using namespace std;
void totalMonthlyPay(Company employee[]){
    ifstream file("record.txt");
     string line;
     getline(file, line);

    for (int i= 0; i< empNum; i++){
        cout << "---Employee " << i+1<< "---"<< endl;
        file>>employee[i].id>>employee[i].Sex >>employee[i].Hourly_Wage >>employee[i].Years_with_the_Company;
        cout<< "Hours worked per month: ";
        cin>> employee[i].hrsPerMonth;
        employee[i].monthlyPay = employee[i].hrsPerMonth*employee[i].Hourly_Wage;
        cout<< "Total payment per month: "<<employee[i].monthlyPay << endl;
    }
    file.close();
}
int main()
{
    totalMonthlyPay(employee);
   return 0;
}