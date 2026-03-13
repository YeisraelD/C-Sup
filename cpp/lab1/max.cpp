#include <iostream>
using namespace std;

double max(double x, double y) {
    return (x > y) ? x : y;  // ternary conditional opretion
}

double max(double x, double y, double z) {
    return max(max(x, y), z);  
}

int main() {
    double n1, n2, n3;
    cout << "Enter your numbers to get the max of them: ";
    cin >> n1 >> n2 >> n3;
    cout << "The max num is: " << max(n1, n2, n3) << endl;

    return 0;
}
