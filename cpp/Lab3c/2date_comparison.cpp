/*Write a C++ function named larger() that returns the later date of any two dates passed to it. 
For example, if the dates 10/9/2005 and 11/3/2005 are passed to larger(), the second date is 
returned and Store the Date structure returned by larger() in a separate Date structure and 
display the member values of the returned Date. Use pointer as a variable of the structure.*/
#include<iostream>
using namespace std;
const int dateNum=2;
struct date_comparison
{
   int year;
   int month;
   int day;
}date[dateNum];
date_comparison* larger(date_comparison* date1, date_comparison* date2){
    /*larger() function is supposed to return a pointer to a date_comparison object ,
    the parameters passed to the function need to be pointers as well.*/ 
    
        if (date1->year>date2->year){
            return date1;
        }else if (date1->year<date2->year){
            return date2;
        }
        if (date1->month>date2->month){
            return date1;
        }else if (date1->month<date2->month){
            return date2;
        }
        if (date1->day>date2->day){
            return date1;
        }else if (date1->day<date2->day){
            return date2;
        }

        cout << "The dates are equal";
    return date2;
}
int main(){
    for(int i= 0; i<dateNum; i++){
        cout << "Enter the year for date "<< i+1<< ":";
        cin >> date[i].year;
        cout << "Enter the month for date "<< i+1<< ":";
        cin >> date[i].month;
        cout << "Enter the day for date "<< i+1<< ":";
        cin >> date[i].day;
    }
    date_comparison* laterDate = larger(&date[0], &date[1]);
    /*date[0] doesn't work for the function call*date[0] or *date[1], 
    we're dereferencing those elements, which means we're passing the object itself,*/
    cout << "The later date is: "
    << laterDate->day<< "/"
    <<laterDate->month<<"/"
    <<laterDate->year;

   return 0;
}
