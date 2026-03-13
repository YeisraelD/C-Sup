#include <iostream>
#include <iomanip>
#include <iomanip>
using namespace std;

struct date
{
    int BOD;
}D;
struct student_info
{
    int rollnum;
    char name[30];
    double marks[5];
    double ave;
    date D;
}students[2];

void input();
void display();
void below();
double average();
int k=0;

void finalDisplay(student_info students[]){
    cout<< "---final tabular reoresentatioon for students record---"<< endl;
    cout << "student name"<< setw(15)<< " Roll number"<< setw(20)<< " Date of bearth"<<setw(15)<< "score";
    cout<< endl;
    for (int i=0; i<=9; i++){
        cout<< students[i].name<< setw(15)<<students[i].rollnum<<setw(15)<<students[i].D.BOD<<setw(20)<< students[i].ave;
        cout<< endl;
    }
    cout<< endl;
}
int main ()
{
    for(int k=0; k<2; k++)
    {
    input();
    display();
    cout<<endl;
    }
    for(int k=0; k<2; k++)
    {
    cout<<" student information for average below 50";
    below();
    }
    finalDisplay(students);
    return 0;
}

void input()
{
    cout<<"welcome! please enter your name: ";
    cin.ignore();
    cin.getline(students[k].name, 30);
    cout<<"enter your roll number: ";
    cin>>students[k].rollnum;
    cout<<"enter your marks: ";
    for(int j=0; j<5 ;j++)
    {
    cin>>students[k].marks[j];
    }
    cout<<"enter your date of birth: ";
    cin>>students[k].D.BOD;
}
double average(double marks[5])
{
    double sum=0;
    for (int i=0; i<5; i++)
    {
       sum+=marks[i]; 
    }
    double ave= sum/5;
    return ave;
}
void display()
{
    
cout<<"name"<<setw(15)<<"rollnumber"<<setw(10)<<"mark 1"<<setw(10)<<"mark 2"<<setw(10)<<"mark 3"<<setw(10)<<"mark 4"<<setw(10)<<"mark 5"<<setw(20)<<"date of birth"<<endl;

    cout<<students[k].name;
    cout<<setw(10)<<students[k].rollnum;
    for(int j=0;j<5;j++)
    {
    cout<<setw(10)<<students[k].marks[j];
    }
    cout<<setw(10)<<students[k].D.BOD;
}
void below()
{
    if (average(students[k].marks) < 50)
    {
        display();
    }
}