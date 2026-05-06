#include <iostream>
using namespace std;

int main() {
    int n = 5;

    double x[5] = {1, 2, 3, 4, 5};
    double y[5] = {2, 4, 5, 4, 5};

    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    // Sequential computation
    for (int i = 0; i < n; i++) {
        sum_x += x[i];             // sum of x values
        sum_y += y[i];             // sum of y values
        sum_xy += x[i] * y[i];     // sum of x*y
        sum_x2 += x[i] * x[i];     // sum of x^2
    }

    // Calculate slope (m) and intercept (b)
    double m = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    double b = (sum_y - m * sum_x) / n;

    cout << "Slope (m): " << m << endl;
    cout << "Intercept (b): " << b << endl;

    return 0;
}