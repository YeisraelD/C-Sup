#include "company.h"
#include<iostream>
#include <iomanip>
using namespace std;

void setInfo(Company employee[]){
    fstream outf;
    outf.open("record.bin", ios::out | ios::binary);
    
    for (int i=0; i< empNum; i++){
        cout << "---Employee "<< i+1<< "---"<< endl;
        cout << " ID: ";
        cin >> employee[i].id;
         cout<< "Sex(M/F): ";
         cin >> employee[i].Sex;
         cout<< "Hourly-Wage: ";
         cin >> employee[i].Hourly_Wage;
         cout<< "Years-with-the-Company: ";
         cin >> employee[i].Years_with_the_Company;
         
    }
    for (int i = 0; i < empNum - 1; i++) {
        for (int j = 0; j < empNum - i - 1; j++) {
            if (employee[j].id > employee[j + 1].id) {
                swap(employee[j], employee[j + 1]);
            }
        }
    }
    for (int i = 0; i < empNum; i++) {
        outf.write((char*)(&employee[i]), sizeof(Company));
    }
    outf.close();
}
int main()
{
   setInfo(employee);
   return 0;
}