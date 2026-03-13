
#include <iostream>
using namespace std;
void pattern(int length=5, string symbol= "*"){
    for(int i=0; i<= length; i++){
        for(int j=0; j<= i; j++){
            cout << symbol;
        }
    cout << endl;
}
 }
int main()
{
    int len;
    string sym;
    string choice;
    cout << "to see the difault pattern enter'y' ";
    cin >> choice;
    if (choice=="y"||choice=="Y"){
       pattern();
    }
       
       else{
             cout << "enter the length: ";
          cin >> len;
          cout<< "enter the symbol: ";
          cin >> sym;
          cout << "the last result"<< endl;
          pattern(len,sym); 
       }
    return 0;
}