#ifndef COMPANY_H
#define COMPANY_H
#include<iostream>
#include<fstream>
using namespace std;
const int empNum = 3;
struct Company{
   int id ;
   char Sex[1];	
   float Hourly_Wage;
   int Years_with_the_Company;
   int hrsPerMonth;
   float monthlyPay;
   
};
Company employee[empNum];
void setInfo(Company employee[]);
void totalMonthlyPay(Company employee[]);
#endif