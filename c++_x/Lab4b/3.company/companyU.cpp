#include<iostream>
#include "company.h"
#include <iomanip>
#include <string>
using namespace std;

void updateInfo(Company employee[]) {
    string chs;
    int choose;

    do {
        cout << "1. Information view" << endl;
        cout << "2. To update the record" << endl;
        cout<< "Your chooice: ";
        cin >> choose;
        
        switch (choose) {
        case 1: {
            ifstream file("record.txt");
            string line;
            getline(file, line);
            for (int i = 0; i < empNum; i++) {
                file >> employee[i].id >> employee[i].Sex >> employee[i].Hourly_Wage
                     >> employee[i].Years_with_the_Company;
                cout << "---employee " << i + 1 << " ---" << endl;
                cout << "ID: " << employee[i].id << endl;
                cout << "Sex: " << employee[i].Sex << endl;
                cout << "Hourly_Wage: " << employee[i].Hourly_Wage << endl;
                cout << "Years with the Company: " << employee[i].Years_with_the_Company << endl;
            }
            file.close();
            break;
        }
        case 2: {
            ofstream file("record2.txt");
            file << "Employee ID" << setw(14)
                 << "Sex(M/F)" << setw(15)
                 << "Hourly-Wage " << setw(20)
                 << "Years-with-the-Company" << endl;
            
            for (int i = 0; i < empNum; i++) {
                cout << "---Employee " << i + 1 << "---" << endl;
                cout << "Sex(M/F): ";
                cin >> employee[i].Sex;
                cout << "Hourly-Wage: ";
                cin >> employee[i].Hourly_Wage;
                cout << "Years-with-the-Company: ";
                cin >> employee[i].Years_with_the_Company;
            }
            for (int i = 0; i < empNum - 1; i++) {
                for (int j = 0; j < empNum - i - 1; j++) {
                    if (employee[j].id > employee[j + 1].id) {
                        swap(employee[j], employee[j + 1]);
                    }
                }
            }
            for (int i = 0; i < empNum; i++) {
                file << employee[i].id << setw(15)
                     << employee[i].Sex << setw(15)
                     << employee[i].Hourly_Wage << setw(15)
                     << employee[i].Years_with_the_Company << endl;
            }
            file.close();
            break;
        }
        default:
            cout << "Invalid input" << endl;
            break;
        }

        cout << "Back to the main menu(y/n): ";
        cin >> chs;
    } while (chs == "Y" || chs == "y");

    cout << "exiting..." << endl;
}

int main() {
    updateInfo(employee);
    return 0;
}
