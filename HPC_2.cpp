#include <iostream>
#include <omp.h>
using namespace std;

void bubble(int a[], int n) {

    for(int i = 0; i < n; i++)

        for(int j = 0; j < n-1; j++)

            if(a[j] > a[j+1])
                swap(a[j], a[j+1]);
}

void pBubble(int a[], int n) {

    #pragma omp parallel
    for(int i = 0; i < n; i++) {

        #pragma omp for
        for(int j = 1; j < n; j += 2)

            if(a[j] < a[j-1])
                swap(a[j], a[j-1]);

        #pragma omp for
        for(int j = 2; j < n; j += 2)

            if(a[j] < a[j-1])
                swap(a[j], a[j-1]);
    }
}

void merge(int a[], int l, int m, int r) {

    int temp[50];
    int i=l, j=m+1, k=0;

    while(i<=m && j<=r)

        temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];

    while(i<=m)
        temp[k++] = a[i++];

    while(j<=r)
        temp[k++] = a[j++];

    for(i=l, k=0; i<=r; i++, k++)

        a[i] = temp[k];
}

void mergeSort(int a[], int l, int r) {

    if(l < r) {

        int m = (l+r)/2;

        mergeSort(a,l,m);

        mergeSort(a,m+1,r);

        merge(a,l,m,r);
    }
}

void pMergeSort(int a[], int l, int r) {

    if(l < r) {

        int m = (l+r)/2;

        #pragma omp parallel sections
        {
            #pragma omp section
            pMergeSort(a,l,m);

            #pragma omp section
            pMergeSort(a,m+1,r);
        }

        merge(a,l,m,r);
    }
}

void print(int a[], int n) {

    for(int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
}

int main() {

    int n = 6;

    int a[6] = {6,5,4,3,2,1};

    int b[6] = {6,5,4,3,2,1};

    double t1, t2;

    cout << "Original Array: ";

    print(a, n);

    t1 = omp_get_wtime();

    bubble(a,n);

    t2 = omp_get_wtime();

    cout << "\nSeq Bubble Sorted: ";

    print(a, n);

    cout << "Time: " << t2-t1 << endl;

    for(int i = 0; i < n; i++)
        a[i] = n - i;

    t1 = omp_get_wtime();

    pBubble(a,n);

    t2 = omp_get_wtime();

    cout << "\nPar Bubble Sorted: ";

    print(a, n);

    cout << "Time: " << t2-t1 << endl;

    t1 = omp_get_wtime();

    mergeSort(b,0,n-1);

    t2 = omp_get_wtime();

    cout << "\nSeq Merge Sorted: ";

    print(b, n);

    cout << "Time: " << t2-t1 << endl;

    for(int i = 0; i < n; i++)
        b[i] = n - i;

    t1 = omp_get_wtime();

    pMergeSort(b,0,n-1);

    t2 = omp_get_wtime();

    cout << "\nPar Merge Sorted: ";

    print(b, n);

    cout << "Time: " << t2-t1 << endl;

    return 0;
}
