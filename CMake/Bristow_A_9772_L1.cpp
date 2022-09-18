// Alex Bristow
// CWID 50209772
// 09/11/2022

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class BagDyn {
public:
    BagDyn(); // construction
    bool Add(int n); // Add, true if successfully added
    void ListAll();

private:
    int *data;
    unsigned int size;
    unsigned int capacity = 10;

};


BagDyn::BagDyn() {
    data = NULL;

    size = 0;
    data = new int[capacity];
    if (data == NULL) {
        cout << "An error occured, bag cannot be allocated" << endl;
    } else {
        cout << data;
        cout << "A bag to keep " << capacity << " items is created and ready to use" << endl;
    }

}

bool BagDyn::Add(int n) {
    int numDupes = 0;
    if (size > capacity - 1) {
        cout << "Bag has reached capacity at 10 items! \n";
        return false;
    }

    for (int i = 0; i < size; i++)    // i < size   or i <= (size-1)
    {
        if (data[i] == n) {
            numDupes++;
            if (numDupes >= 3) {
                cout << "Bag already has three " << n << "s. \n";
                return true;
            }
        }
    }
    // data[size] = n; size++;
    data[size++] = n;

    return true;
}

void BagDyn::ListAll() {
    if (size == 0) {
        cout << "Bag is empty" << endl;
        return;
    }

    for (int i = 0; i < size; i++)    // i < size   or i <= (size-1)
    {
        cout << data[i] << ", ";
    }

    cout << endl;

}

int main() {
    BagDyn aBag;
    bool spaceAvailable = true;

    while (spaceAvailable) {
        int userEntry;
        cout << "Enter a number:";
        cin >> userEntry;

        if (userEntry < 0) {
            cout << "Bye...";
            spaceAvailable = false;
        } else {
            spaceAvailable = aBag.Add(userEntry);
            aBag.ListAll();
        }
    }
    return 0;
}
