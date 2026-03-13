/*1. Given a structure a specification to store the details of 10 students (rollno, name, marks in five subject, BoD   
    which student's type is Date struct), write a program to input each student's detail using function and perform  
    the following;
Compute average score for each student and print the students’ details in tabular format along with their scores
Determine and print student’s details who scored average mark below 50*/

#include<iostream>
#include <iomanip>
using namespace std;
struct studentRec{
       int rollno;
       char name[10];
       double mark[5];
       double scor;
       struct Date
       {
            int day;
            int month;
            int year;
       };
       Date d;
       
}Rec[2];
// validation functions
void idVerifier(int &rollno){
   while  (true){
    if (cin.fail()){
    cout << "Invalid input! please enter the valid rolle number for the student.";
    cin >> rollno;
    }
    if (!cin.fail()||rollno>=0){
        break;
    }
   } 
   
}
int main(){
   for (int i=0; i<=1; i++){
    cout<< "enter the name of student "<< i+1<< ": ";
    cin>> Rec[i].name;
    cout<< endl;
    cout<< "enter the roll number for student "<< i+1 << ": ";
    cin >> Rec[i].rollno;
    idVerifier(Rec[i].rollno);
    cout<< endl;

    cout << "student DoB"<< endl;
    cout << "the day: ";
    cin >> Rec[i].d.day;
    cout<< "the month: ";
    cin>> Rec[i].d.month;
    cout<< "the year: ";
    cin>> Rec[i].d.year;

    double sum=0;
    for (int j=0; j<=5; j++){
        cout << "enter the marks for subjects "<< j+1 << ": ";
        cin>> Rec[i].mark[j];
        sum +=Rec[i].mark[j];
    }
     Rec[i].scor = sum/5;
    cout << endl;
   }

   // tabular output
   cout<< "----Your student recorde is as follows---"<< endl;
   cout << "student name"<< setw(15)<< " Roll number"<< setw(20)<< " Date of bearth"<<setw(15)<< "score";
   cout<< endl;
   for (int i=0; i<= 1; i++){
    cout<< Rec[i].name<< setw(15)<<Rec[i].rollno<<setw(15)<<Rec[i].d.day<<"/"<< Rec[i].d.month<<"/"<<Rec[i].d.year<<setw(20)<< Rec[i].scor;
    cout<< endl;
   }
   cout << endl;
   // scored average mark below 50
   cout << "---students deteal whose average bellow 50---"<< endl;
   cout << "student name"<< setw(15)<< " Roll number"<< setw(20)<< " Date of bearth"<<setw(15)<< "score";
   cout<< endl;

   for (int i=0; i<= 1; i++){
   if (Rec[i].scor<50){
    
        cout << Rec[i].name<< setw(15)<<Rec[i].rollno<<setw(15)<<Rec[i].d.day<<"/"<< Rec[i].d.month<<"/"<<Rec[i].d.year<< setw(20)<< Rec[i].scor;
       cout << endl;
    }else {
        cout<< "---";
       }
   }

    return 0;
}