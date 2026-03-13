#include "company.h"
#include<iostream>
#include<fstream>  // Needed for file operations
using namespace std;

void readInfo() {
    fstream inf("record.bin", ios::in | ios::binary); // Open in input-binary mode
    if (!inf) {
        cerr << "Cannot open file!" << endl;
        return;
    }

    Company temp;  // Temporary variable to read one employee at a time
    int count = 1;

    // Read until end of file
    while (inf.read(reinterpret_cast<char*>(&temp), sizeof(Company))) {
        cout << "---Employee " << count++ << "---" << endl;
        cout << "ID: " << temp.id << endl;
        cout << "Sex: " << temp.Sex << endl;
        cout << "Hourly Wage: " << temp.Hourly_Wage << endl;
        cout << "Years with Company: " << temp.Years_with_the_Company << endl;
        cout << endl;
    }

    inf.close();
}

int main() {
    readInfo();
    return 0;
}
