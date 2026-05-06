#include <iostream>     // for printing output
#include <omp.h>        // for OpenMP (parallel)
using namespace std;

// -------- Sequential Bubble Sort --------
void bubble(int a[], int n) {

    // repeat n times
    for(int i = 0; i < n; i++)

        // compare adjacent elements
        for(int j = 0; j < n-1; j++)

            // swap if wrong order
            if(a[j] > a[j+1])
                swap(a[j], a[j+1]);
}

// -------- Parallel Bubble Sort --------
void pBubble(int a[], int n) {

    #pragma omp parallel   // create multiple threads
    for(int i = 0; i < n; i++) {

        // ---- Odd phase (1,3,5...) ----
        #pragma omp for
        for(int j = 1; j < n; j += 2)

            // compare and swap
            if(a[j] < a[j-1])
                swap(a[j], a[j-1]);

        // ---- Even phase (2,4,6...) ----
        #pragma omp for
        for(int j = 2; j < n; j += 2)

            // compare and swap
            if(a[j] < a[j-1])
                swap(a[j], a[j-1]);
    }
}

// -------- Merge Function --------
void merge(int a[], int l, int m, int r) {

    int temp[50];   // temporary array
    int i=l, j=m+1, k=0;

    // merge two sorted parts
    while(i<=m && j<=r)    //checking 
        temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];

    // copy remaining elements
    while(i<=m) temp[k++] = a[i++];
    while(j<=r) temp[k++] = a[j++];

    // copy back to original array
    for(i=l, k=0; i<=r; i++, k++)
        a[i] = temp[k];
}

// -------- Sequential Merge Sort --------
void mergeSort(int a[], int l, int r) {  //array,start,end position

    if(l < r) {              // if more than one element

        int m = (l+r)/2;     // find middle=m 

        mergeSort(a,l,m);    // sort left half
        mergeSort(a,m+1,r);  // sort right half

        merge(a,l,m,r);      // merge both halves
    }
}

// -------- Parallel Merge Sort --------
void pMergeSort(int a[], int l, int r) {

    if(l < r) {   //checking if its empty

        int m = (l+r)/2;

        // run left & right in parallel
        #pragma omp parallel sections
        {
            #pragma omp section
            pMergeSort(a,l,m);      // left part

            #pragma omp section
            pMergeSort(a,m+1,r);    // right part
        }

        merge(a,l,m,r);    // merge results
    }
}

// put this BEFORE main()
void print(int a[], int n) {
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

// -------- MAIN FUNCTION --------
int main() {

    int n = 6;
    int a[6] = {6,5,4,3,2,1};
    int b[6] = {6,5,4,3,2,1};

    double t1, t2;

    cout << "Original Array: ";
    print(a, n);

    // -------- Sequential Bubble --------
    t1 = omp_get_wtime();
    bubble(a,n);
    t2 = omp_get_wtime();

    cout << "\nSeq Bubble Sorted: ";
    print(a, n);
    cout << "Time: " << t2-t1 << endl;

    // Reset array
    for(int i = 0; i < n; i++)
        a[i] = n - i;

    // -------- Parallel Bubble --------
    t1 = omp_get_wtime();
    pBubble(a,n);
    t2 = omp_get_wtime();

    cout << "\nPar Bubble Sorted: ";
    print(a, n);
    cout << "Time: " << t2-t1 << endl;

    // -------- Sequential Merge --------
    t1 = omp_get_wtime();
    mergeSort(b,0,n-1);
    t2 = omp_get_wtime();

    cout << "\nSeq Merge Sorted: ";
    print(b, n);
    cout << "Time: " << t2-t1 << endl;

    // Reset array
    for(int i = 0; i < n; i++)
        b[i] = n - i;

    // -------- Parallel Merge --------
    t1 = omp_get_wtime();
    pMergeSort(b,0,n-1);
    t2 = omp_get_wtime();

    cout << "\nPar Merge Sorted: ";
    print(b, n);
    cout << "Time: " << t2-t1 << endl;

    return 0;
}