#include<iostream>
#include <cstring>
using namespace std;
int const max_patient= 3;
class patient{
    public:
    int patientID;
    char name[15];
    int age;
    char diagnosis[150];

    void setdata(int id, char* n, int a, char* d){
        patientID=id;
        strcpy(name, n);
        age  = a;
        strcpy(diagnosis, d);
    }
    void display(){
        cout<< "Patient ID: "<< patientID
            << ", Name: "<< name
            << ", Age: "<< age
            << ", Diagnosis: "<< diagnosis
            << endl;
    }
};
class server : public patient{
    public:
    patient data[max_patient];
    int count=0;
    void stordata(int id, char* n, int a, char* d){
        if (count< max_patient){
            data[count].setdata(id, n, a,  d);
            count++;
        }else {
            cout << "Server storage Full"<< endl;
        }
    }
    int getcount(){
        return count;
    }
    patient* getdata(){
        return data;
    }

};
class cliant : public patient{

    public:
    void prossesdata(patient* data, int size){
        cout<< "[cliant]prossesing data...."<< endl;
        for(int i=0; i<size;i++){
            data[i].display();
        }
    }

};
int main(){
    server cloudserver;
    int patientID;
    char name[15];
    int age;
    char diagnosis[150];
    for (int i=0; i<max_patient;i++){
        cout << "--- patient "<< i+1<< "----"<< endl;
        cout << "Enter patient ID: ";
        cin>> patientID;
        cin.ignore();
        cout << "enter patient name: ";
        cin.getline(name,15,'\n');
        cout<< "Enter patient age: ";
        cin >> age;
        cin.ignore();
        cout<< "Enter patient diagnosis type: ";
        cin.getline(diagnosis,150,'\n');
        cin.ignore();
        cloudserver.stordata(patientID,name,age,diagnosis);
    }
    cout << endl;
    
    patient* datafromserver = cloudserver.getdata();
    cliant cliantcomputer;
    int total = cloudserver.getcount();
    cliantcomputer.prossesdata( datafromserver,total);
   return 0;
}