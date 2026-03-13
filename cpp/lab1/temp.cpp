#include <iostream>
using namespace std;

// Function to find daily average temperature (no parameters)
double tempFinder() {
    double low, high;
    cout << "Enter low and high temperature for the day: ";
    cin >> low >> high;
    return (low + high) / 2.0;  // Daily average
}

// Function to find weekly/monthly average temperature (with parameter)
double tempFinder(int length) {
    double total = 0.0;
    for (int i = 1; i <= length; ++i) {
        cout << "\nDay " << i << ": ";
        total += tempFinder();  // Call tempFinder() to get daily average
    }
    return total / length;  // Weekly or monthly average
}

int main() {
    int weekDays, monthDays;

    // Prompt for number of days in a week and month
    cout << "Enter the number of days in a week: ";
    cin >> weekDays;
    cout << "Enter the number of days in a month: ";
    cin >> monthDays;

    // Find daily average temperature
    double dailyAvg = tempFinder();
    cout << "\nDaily average temperature: " << dailyAvg << "°C" << endl;

    // Find weekly average temperature
    double weeklyAvg = tempFinder(weekDays);
    cout << "\nWeekly average temperature: " << weeklyAvg << "°C" << endl;

    // Find monthly average temperature
    double monthlyAvg = tempFinder(monthDays);
    cout << "\nMonthly average temperature: " << monthlyAvg << "°C" << endl;

    return 0;
}
