// ALEX BRISTOW
// Lab 6
// Source modified Data Structures and Algorithm Analysis,
// Edition 3.2 (C++ Version) Clifford A. Shaffer


#include <iostream>
#include <stdlib.h>
#include <iomanip> // std:setprecision

#define N 256000
#define RB 10  //  number base
using namespace std;


void radix(int A[], int B[], int k, int r, int cnt[]);

void fillRandom(int A[], int size);

// The program lunches here
int main() {
    int Arr1 [N];
    int Arr2 [N];
    int Arr3 [N];
    clock_t start, stop;
    double r10totalTime, r100totalTime, r1000totalTime;

    fillRandom(Arr1, N);

    for (int i = 0; i < N; i++) {
        Arr2[i] = Arr1[i];
        Arr3[i] = Arr1[i]; // deep copy
    }

    int B[N] = {0};
    int cnt[RB] = {0};

    // r10 sort
    start = clock();
    radix(Arr1, B, 6, 10, cnt);
    stop = clock();
    r10totalTime = 1000 * (stop - start) / (double) CLOCKS_PER_SEC;

    cout << "r=10, " << setprecision(4) << r10totalTime << " ms" << endl;

    // r100 sort
    start = clock();
    radix(Arr2, B, 6, 100, cnt);
    stop = clock();
    r100totalTime = 1000 * (stop - start) / (double) CLOCKS_PER_SEC;

    cout << "r=100, " << setprecision(4) << r100totalTime << " ms" <<  endl;

    // r1000 sort
    start = clock();
    radix(Arr3, B, 6, 1000, cnt);
    stop = clock();
    r1000totalTime = 1000 * (stop - start) / (double) CLOCKS_PER_SEC;

    cout << "r=1000, " << setprecision(4) << r1000totalTime << " ms" << endl;

}

/*
A: data array,
B: bucket/bin array
k: max number of digit of the longest key
r: numbers base, decimal=10
cnt: auxiliary array
    cnt[i] stores number of records in bin[i]
*/

void radix(int A[], int B[], int k, int r, int cnt[]) {
    // cnt[i] stores number of records in bin[i]
    int j;
    for (int i = 0, dpl = 1; i < k; i++, dpl *= r)   // For k digits
    {
        for (j = 0; j < r; j++)
            cnt[j] = 0; // Initialize cnt

        // Count the number of key for each bin for this iteration
        for (j = 0; j < N; j++)
            cnt[(A[j] / dpl) % r]++;

        // Index for B, cnt[j] will be index for last slot of bin[j].
        // Note we keep last index, so need to decrease it later
        for (j = 1; j < r; j++)
            cnt[j] = cnt[j - 1] + cnt[j];

        // Put records into bins, work from bottom of each bin.
        // Since bins fill from bottom, j is decreased, also
        // since we kept last index, we need to --
        for (j = N - 1; j >= 0; j--)
            B[--cnt[(A[j] / dpl) % r]] = A[j];

        for (j = 0; j < N; j++) // for this iteration move them back to A
            A[j] = B[j];
    }

}

void fillRandom(int A[], int size) {
    for (int i = 0; i < size; i++)
        A[i] = rand() % 899999 + 100000;
}
