// Alex Bristow

// Comparison of Selection Sort and Insertion Sort 
// in Randomly genereated integer with dynamicaly crated arrays

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip> // std:setprecision 
#include <ctime>

using namespace std;

void swap(int A[], int i, int min);

bool small(int a, int b);

void print(int A[]);

void fillRandom(int A[], int size);

void InsSort(int A[], int size);

void SelSort(int A[], int size);


int main(int argc, const char *argv[]) {
    int *A;
    int *B;
    int size = 16000;
    clock_t start, stop;
    double selTotalTime;
    double insTotalTime;
    string stage = "Asc";
    string prevStage;

    // iterate and perform pre-sorting setup ropcedures based on which stage we are one (asc, rand, or, desc)
    while (stage != "Done") {
        A = new int[size];
        B = new int[size];
        fillRandom(A, size);
        for (int i = 0; i < size; i++) B[i] = A[i]; // deep copy

        //store current stage in prevStage for cout
        prevStage = stage;

        if (stage == "Asc") {
            // sort Asc prior to timing sort functions
            sort(A, A + size);
            sort(B, B + size);

            // set next stage for next iteration
            stage = "Rand";
        } else if (stage == "Rand") {
            stage = "Des";
        } else if (stage == "Des") {
            // sort both arrays descending order prior to timing functions
            sort(A, A + size, greater<int>());
            sort(B, B + size, greater<int>());
            stage = "Done";
        }

        // Insertion sort timing
        start = clock();
        InsSort(A, size);
        stop = clock();
        insTotalTime = (stop - start) / (double) CLOCKS_PER_SEC;

        // Selection sort timing
        start = clock();
        SelSort(B, size);
        stop = clock();
        selTotalTime = (stop - start) / (double) CLOCKS_PER_SEC;

        delete[]A;
        delete[]B;

        cout << prevStage << " ordered, SS: " << setprecision(2) << insTotalTime << " sec, IS: " << selTotalTime << " sec"
             << endl;
    }
}

void SelSort(int A[], int size) {
    // Selection sort
    for (int i = 0; i < size; i++) {                                // Swap a[i] with smallest entry in a[i+1...N).
        int min = i;                // index of minimal entr.
        for (int j = i + 1; j < size; j++) {
            if (small(A[j], A[min]) == true) min = j;
        }
        swap(A, i, min);
    }

}

void InsSort(int A[], int size) {
    // Insertion sort
    for (int i = 0; i < size; i++) {
        for (int j = i; j > 0; j--)
            if (small(A[j], A[j - 1]) == true) // compare
                swap(A, j, j - 1); // exchange or swap
            else break;
    }

}

bool small(int a, int b) {
    if (a < b) return true;
    return false;

}

void swap(int A[], int i, int min) {
    int tmp = A[i];
    A[i] = A[min];
    A[min] = tmp;
}

void fillRandom(int A[], int size) {
    for (int i = 0; i < size; i++)
        A[i] = rand() % 40000 + (-20000);
}

