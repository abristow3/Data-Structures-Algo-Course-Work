// Alex Bristow
// Quick Sort Versus Turkey Ninther in Randomly generated integer array


#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

#define N 256000

using namespace std;


void swap(string A[], int i, int min);

bool small(string a, string b);

void print(string A[]);

void fillRandom(string A[], int size);

void sort(string A[], int lo, int hi);

void turkeySort(string A[], int lo, int hi);

int partition(string A[], int lo, int hi);

int main(int argc, const char *argv[]) {
    int counter = 0;
    clock_t start, stop;
    double qsTotalTime = 0;
    double tsTotalTime = 0;
    double qsiterationTime;
    double tsiterationTime;
    string *A;
    string *B;
    A = new string[N];
    B = new string[N];
    int fasterRuns = 0;

    while (counter < 100) {
        srand(time(0));
        A = new string[N];
        B = new string[N];

        fillRandom(A, N);

        for (int i = 0; i < N; i++) {
            B[i] = A[i];
        }

        start = clock();
        sort(A, 0, N - 1);
        stop = clock();

        qsiterationTime = 1000 * (stop - start) / (double) CLOCKS_PER_SEC;
        qsTotalTime += qsiterationTime;
        counter++;

        start = clock();
        turkeySort(B, 0, N - 1);
        stop = clock();

        tsiterationTime = 1000 * (stop - start) / (double) CLOCKS_PER_SEC;
        tsTotalTime += tsiterationTime;
        counter++;

        if (qsiterationTime > tsiterationTime){
            fasterRuns++;
        }
    }
    double tsAvgTime = tsTotalTime / 100;
    double qsAvgTime = qsTotalTime / 100;
    cout << fasterRuns << endl;

    cout << "Turkey QS Ave: "  << tsAvgTime << " ms, " << "Reg. QS: " << qsAvgTime << " ms" << endl;
    cout << "Turkey QS was faster in " << fasterRuns << "% of 100 runs."<< endl;
    cout << "The T value distribution is" << endl;
}

void sort(string A[], int lo, int hi) {
    if (hi <= lo) return;
    int j = partition(A, lo, hi);
    sort(A, lo, j - 1);
    sort(A, j + 1, hi);
}

void turkeySort(string B[], int lo, int hi) {
    if (hi <= lo) return;

    int m1 = 8 + 20000 + 100000;
    m1 = m1 /3;

    int m2 = lo + hi - 20000 + 86000;
    m2 = m2 /3;

    int m3 = 124353 + 5728 + 55674;
    m3 = m3 /3;

    int m4 = m1 + m2 + m3;
    m4 = m4/3;

    turkeySort(B, m4, lo);
}

int partition(string A[], int lo, int hi) {
    int i = lo, j = hi + 1;
    while (true) {
        while (small(A[++i], A[lo]))  // find item on left to swap
            if (i == hi) break;

        while (small(A[lo], A[--j]))  // find item on right to swap
            if (j == lo) break;

        if (i >= j) break;    //check if pointers cross
        swap(A, i, j);
    }
    swap(A, lo, j);
    return j;            // return index of item now known to be in place
}

void swap(string A[], int i, int min) {
    string tmp = A[i];
    A[i] = A[min];
    A[min] = tmp;
}

void fillRandom(string A[], int size) {
    for (int i = 0; i < N; i++) {
        int counter = 0;
        while (counter != 4) {
            int ascii = rand() % 58 + 65;

            if (ascii <= 122 && ascii >= 97 || ascii <= 90 && ascii >= 65) {
                counter++;
                A[i] += ascii;
            }
        }
    }
}

void print(string A[]) {
    for (int i = 0; i < N; i++)
        cout << A[i] << ", ";
    cout << endl;
}

bool small(string a, string b) {
    if (a < b) return true;
    return false;
}
