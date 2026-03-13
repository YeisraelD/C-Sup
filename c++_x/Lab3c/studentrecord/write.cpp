#include"record.h"
#include <iomanip>
const int max_stunum = 3;
void getrecord(student record[]){
    ofstream file("Test.txt");
    if (!file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    file <<" ----  student record ----"<< endl;
    file <<"student ID"<< setw(15)<< "student name"<<setw(10)<< "Grade"<< endl;


    for (int i=0; i<max_stunum;i++){
        cout << "--- student "<< i +1<< " ---"<< endl;
        cout<<"Student ID: ";
        cin>>record[i].studentID;
        
        cout<<"Student name: ";
        cin>>record[i].name;
        cout<<"Student grade: ";
        cin>>record[i].grade;
        file << record[i].studentID << setw(15)
             << record[i].name << setw(15)
             << record[i].grade << endl; // save to file

    }
    file.close();
}
int main()
{
    student* record = new student[max_stunum];
    getrecord(record);
    delete[] record;
   return 0;
}