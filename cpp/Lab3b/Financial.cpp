#include<iostream>
using namespace std;
/*(Financial) Write a C++program that uses a structure for storing a stock name, 
its estimated earnings per share, and its estimated price-to-earnings ratio. 
Have the program prompt the user to enter these items for three different stocks, 
each time using the same structure to store the entered data. When data has been entered for a particular stock,
 have the program compute and display the anticipated stock price based on the entered earnings and 
 price-per-earnings values. For example, if a user enters the data XYZ, 1.56, 12, 
 the anticipated price for a share of XYZ stock is (1.56) × (12) = $18.72. (use pointer structure variable)*/

struct stock
{
   string name;
   float earningsPerShare;
   float priceToearnings;
};

int main() {
    stock *stocks= new stock[3];
    for (int i=0; i< 3; i++){
        cout << "Enter the stock name: ";
        cin >> (stocks+i)->name; 
        //stocks.[i] is equvalent with (stocks+i)->name, since arry and pointers are closely related, but for single object use only pointer notation
        cout << "Enter the estimated earnings per share: ";
        cin >> (stocks+i)->earningsPerShare;
        cout << "Enter the estimated price-to-earnings ratio: ";
        cin >> (stocks+i)->priceToearnings;
        float anticipatedPrice= (stocks+i)->earningsPerShare*(stocks+i)->priceToearnings;

        cout << "Anticipated price for "<< (stocks+i)->name<< ": $"<<anticipatedPrice<< endl;
        
    }
    delete[] stocks;// free memory allocation, to privent memory leak

   return 0;
}

