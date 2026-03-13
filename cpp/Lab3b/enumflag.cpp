//Provide an example that demonstrate the use of enum in defining flags.

#include<iostream>
using namespace std;
enum filePermission{
    READ=1,
    WRITE=2,
    EXCUTE=4
};
int main(){
    int myPermission= READ | WRITE;
    cout << "Enter your file access permission value(1, 2, 4): ";
    cin>> myPermission;

    cout << "Has Read permission: "<< ((myPermission&READ)? "yes":"No")<< endl;
    cout << "Has Read permission: "<< ((myPermission&WRITE)? "yes":"No")<< endl;
    cout << "Has Read permission: "<< ((myPermission&EXCUTE)? "yes":"No")<< endl;//compacted if else conditions(ternary conditonal operations)
 return 0;

}