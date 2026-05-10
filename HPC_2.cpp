#include <iostream>
#include <omp.h>
using namespace std;

int main() {

    int n = 1000;
    int a[1000];

    for (int i = 0; i < n; i++)
        a[i] = rand() % 1000;

    int sum = 0;
    int min_val = a[0];
    int max_val = a[0];

    double avg;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum) reduction(min:min_val) reduction(max:max_val)
    for (int i = 0; i < n; i++) {

        sum += a[i];

        if (a[i] < min_val)
            min_val = a[i];

        if (a[i] > max_val)
            max_val = a[i];
    }

    avg = (double)sum / n;

    double end = omp_get_wtime();

    cout << "Sum: " << sum << endl;
    cout << "Min: " << min_val << endl;
    cout << "Max: " << max_val << endl;
    cout << "Average: " << avg << endl;
    cout << "Time: " << end - start << " sec" << endl;

    return 0;
}
