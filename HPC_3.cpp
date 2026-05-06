#include <iostream>     // for input-output
#include <omp.h>        // for OpenMP functions
using namespace std;

int main() {
    int n = 1000;       // number of elements
    int a[1000];        // array to store values

    // Initialize array with random values
    for (int i = 0; i < n; i++)
        a[i] = rand() % 1000;   // values between 0 to 999

    int sum = 0;        // to store total sum
    int min_val = a[0]; // initialize min with first element
    int max_val = a[0]; // initialize max with first element
    double avg;         // to store average

    double start = omp_get_wtime(); // start time (OpenMP function)

    // Parallel loop with reduction
    #pragma omp parallel for reduction(+:sum) reduction(min:min_val) reduction(max:max_val)
    for (int i = 0; i < n; i++) {

        sum += a[i];    // add element to sum

        // find minimum value
        if (a[i] < min_val)
            min_val = a[i];

        // find maximum value
        if (a[i] > max_val)
            max_val = a[i];
    }

    avg = (double)sum / n;   // calculate average- overried datatype of sum

    double end = omp_get_wtime(); // end time

    // Display results
    cout << "Sum: " << sum << endl;
    cout << "Min: " << min_val << endl;
    cout << "Max: " << max_val << endl;
    cout << "Average: " << avg << endl;
    cout << "Time: " << end - start << " sec" << endl;

    return 0;   // end of program
}