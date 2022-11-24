// Mutlu Mete
// BinarySearch.cpp
// Symbol Table with Sorted Parallel Arrays. Uses Binary Search


#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip>      // std::setw
// #define N  10

using namespace std;

class BSST // Binary search Symbol Table
{
public:
    BSST(int cap);	                    //create an ordered symbol table
    void put(string key, int value); 	// put key-value pair into the table
    int* get(string key);			 	// value paired with key, (null if key is absent, then int*)
    void del(string key);				// remove key (and its value) from table
    int find(string key);				// returns
    bool contains(string key);			// is there a value paired with this key?
    bool isEmpty();						// is the table empty?
    void list();
    int size(); 						//number of key-value pairs
    int min();							// smallest key
    int max();							// largest key
    int floor(string key);				// largest key less than or equal to key
    int ceiling(string key);			//smallest key greater than or equal to key
    int rank(string key);               // number of keys less than key
    string select(int k);	// key of rank k
    void deleteMin(); 		// delete smallest key
    void deleteMax(); 		// delete largest key
private:
    unsigned int N;
    unsigned int capacity;
    string *keys;
    int   *values;
};

BSST::BSST(int cap)
{
    N=0;
    capacity = cap;
    keys = new string[cap];
    values = new int[cap];
}

int BSST::size()
{
    return N;
}

bool BSST::isEmpty()
{
    if (N>0)
        return false;
    else
        return true;
}

int BSST::find(string key) // Binary search. what we return, this method also called rank in a bit different way
{
    int lo = 0, hi = N-1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if ( keys[mid] == key )
        {
            return mid;
        }
        else if ( keys[mid] > key )
            hi = mid - 1;
        else if ( keys[mid] < key)
            lo = mid + 1;
    }
    return lo;  //returns the number of keys in the table that are smaller than key.
}

void BSST::list()
{
    if (isEmpty())
        return;
    for (int i = 0; i < N; i++) // shift
        cout << keys[i] << " --> "  << values[i] << endl;

    cout << endl;
}

int* BSST::get(string key)
{
    if (isEmpty())
        return NULL;
    int i = find(key) ;
    if (keys[i] == key)
        return &values[i];
    else
        return NULL;
}

void BSST::put(string key, int value)
{
    // Search for key. Update value if found; grow table if new.
    int i = find(key);
    if (keys[i] == key)
    {
        values[i] = value;    // update the existing  value
        return;
    }

    for (int j = N; j > i; j--) // shift
    {
        keys[j] = keys[j-1];
        values[j] = values[j-1];
    }
    keys[i] = key;
    values[i] = value;
    N++;
}

string RandomStr()
{
    string AddMe="ABC"; // A string example  we will randomle generate
    for (int j=0; j < 3; j++)
    {
        AddMe[j]=rand() % 26 + 65;
    }
    return AddMe;
}


// The program lunches here
int main( )
{
    BSST A(20);
    string AddMe;
    int AddValue=0;
    for (int i=0; i< 10; i++)   // Add 10 items.
    {
        AddMe=RandomStr();
        //A.put(AddMe,i*2);
        //cout << AddMe << "->" << i*2 << ", ";
    }

    A.list();


    while (AddMe != "exit" ) // a loop to search strings. "exit" exits the program
    {
        cout << "\nEnter a  string and number: ";
        cin >> AddMe >> AddValue;
        A.put(AddMe,AddValue);
        A.list();
    }

    cout << endl;
    A.list();
    cout<< " Bye...." << endl ;



}

