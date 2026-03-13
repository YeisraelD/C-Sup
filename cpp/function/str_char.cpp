#include<iostream>
#include<string>
using namespace std;
void display(char s[]){
    cout<< "entered message: "<< s<< endl;
}
void display(string s){
    cout << "entered message: "<< s<< endl;
}
int main()
{
    char str1[100];
    string str2;

    cout<<"Enter message1: ";
    cin.getline(str1, 100, '\n');

    cout<<"Enter message2: ";
    getline(cin, str2);
    
    display(str1);
    display(str2);
return 0;
}