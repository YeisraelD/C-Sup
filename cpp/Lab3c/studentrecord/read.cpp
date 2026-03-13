#include "record.h"
#include <iomanip>
const int max_stunum = 3;

void readrecord(student record[]){
    ifstream file("Test.txt");
    if (!file) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }
     string line;
     getline(file, line);  // Skip "---- student record ----"
     getline(file, line);  // Skip the header line
    for(int i=0;i<max_stunum;i++){
        file >> record[i].studentID >> record[i].name >> record[i].grade;        // reads from the file into the array
        cout<<"--- Record "<< i+1<< " ---"<< endl;
        cout<<"Student ID: "<<record[i].studentID<< endl;
        cout<<"Student name: "<<record[i].name<<endl;
        cout<<"Student grade: "<<record[i].grade<<endl;
        cout<<endl;
    }
    file.close();
}

int main()
{
    student record[max_stunum];
    readrecord(record);
 return 0;
}