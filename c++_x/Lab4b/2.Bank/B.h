#ifndef B_H
#define B_H
#include <fstream>
#include <iostream>
using namespace std;
const int custNum=2;
struct Bank{
    char Fname[10];
    char Lname[15];
    double balance;
    long long unsigned int account_num;
};
Bank customer[custNum];
void getRec(Bank customer[]);
void serchCustomer(Bank *customer);
#endif
