// Dual-Pivot Quicksort algorithm, Vladimir Yaroslavskiy

// mainly from  https://learnforeverlearn.com/yaro_web/

// Mutlu Mete
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#define N  100

using namespace std;


void swap(short A[], int i, int j);
bool small(short a, short b);
void print(short A[]);
void fillRandom(short A[], int size);

void QuicksortYaro(short A[], int left, int right);

int main(int argc, const char * argv[])
{
	short *A = new short[N];
	//short A[N];
	fillRandom(A, N);
	print(A);
	QuicksortYaro(A, 0, N - 1);
	//Shuffle(A); shuffle  the array. commentted out for now
	print(A);
	system("pause");
}


void QuicksortYaro(short A[], int left, int right)
{
	// insertion sort for tiny array   // OPTIONAL
	/*
	int len = right - left;
	if (len < 27) {
		for (int i = left + 1; i <= right; i++) {
			for (int j = i; j > left && A[j] < A[j - 1]; j--) {
				swap(A, j, j - 1);
			}
		}
		return;
	}
	//  <END> // insertion sort for tiny array // OPTIONAL
	*/

	if (right > left) {
		// Choose outermost elements as pivots
		if (A[left] > A[right]) swap(A, left, right);
		short p = A[left];
		short q = A[right];

		// Partition A according to invariant below
		int l = left + 1;
		int k = l;
		int g = right - 1;
		while (k <= g)
		{
			if (A[k] < p)
			{
				swap(A, k, l);
				l = l + 1;
			}
			else if (A[k] >= q)   // or    if A[k] > q
				{
					while (A[g] > q && k < g)
						g = g - 1;
					swap(A, k, g);
					g = g - 1;
					if (A[k] < p)
					{
						swap(A, k, l);
						l = l + 1;
					}
				}
			k = k + 1;
		}
		l = l - 1;
		g = g + 1;

		// Swap pivots to final place
		swap(A, left, l);
		swap(A, right, g);

		QuicksortYaro(A, left, l - 1);

		QuicksortYaro(A, l + 1, g - 1);

		QuicksortYaro(A, g + 1, right);
	}
}


void swap(short A[], int i, int j)
{
	short tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

void fillRandom(short A[], int size)
{
	for (int i = 0; i < N; i++)
		A[i] = rand() % 50;
}

void print(short A[])
{
	for (int i = 0; i < N; i++)
		cout << A[i] << ", ";
	cout << endl;
}

bool small(int a, int b)
{
	if (a <= b) return true;
	return false;
}