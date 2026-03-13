#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int empnum = 4;

struct Report {
    string name;
    double rate;
    int hours;
};

double calcRegularPay(const Report& emp) {
    double regularPay = 0;
    if (emp.hours > 40) {
        regularPay = 40 * emp.rate;
    } else {
        regularPay = emp.hours * emp.rate;
    }
    return regularPay;
}

double calcOvertimePay(const Report& emp) {
    double overtimePay;
    if (emp.hours > 40) {
        overtimePay = (emp.hours - 40) * emp.rate * 1.5;
    } else {
        overtimePay = 0.0;
    }
    return overtimePay;
}

double grossPay(const Report& emp) {
    return calcRegularPay(emp) + calcOvertimePay(emp);
}
double totalRegularPay(const Report emp[]) {
    double total = 0;
    for (int i = 0; i < empnum; i++) {
        total += calcRegularPay(emp[i]);
    }
    return total;
}
double totalOvertimePay(const Report emp[]) {
    double total = 0;
    for (int i = 0; i < empnum; i++) {
        total += calcOvertimePay(emp[i]);
    }
    return total;
}
double totalGrossPay(const Report emp[]) {
    double total = 0;
    for (int i = 0; i < empnum; i++) {
        total += grossPay(emp[i]);
    }
    return total;
}

int main() {
    Report emp[empnum];

    ofstream file("report.txt");
    file <<left<<setw(15) <<"----  Employee record ----" << endl;
    file << left << setw(15) << "Name" 
         << setw(10) << "Rate" 
         << setw(10) << "Hours"
         << setw(15) << "Regular Pay" 
         << setw(15) << "Overtime Pay" 
         << setw(15) << "Gross Pay" << endl;

    for (int i = 0; i < empnum; i++) {
        cout << "Name: ";
        cin >> emp[i].name;
        cout << "Pay rate: ";
        cin >> emp[i].rate;
        cout << "Hours: ";
        cin >> emp[i].hours;

        double regular ;
        double overtime ;
        double gross ;
        file << left << setw(15) << emp[i].name
             << setw(10) << emp[i].rate
             << setw(10) << emp[i].hours
             << setw(15) << calcRegularPay(emp[i])
             << setw(15) << calcOvertimePay(emp[i])
             << setw(15) << grossPay(emp[i])<<endl;

    }
    cout << endl;

    file << "\nTotal" << setw(25) << ""
         << setw(15) << totalRegularPay(emp)
         << setw(15) << totalOvertimePay(emp)
         << setw(15) << totalGrossPay(emp) << endl;

    file.close();
    return 0;
}
