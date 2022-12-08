//  Mutlu Mete
//  HashTable, Separate Chaining implemenete with Singly Linked List

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip> // std::setw


using namespace std;

// A struct to keep items
struct item
{
    string key;
    int value;
    item *next;
};

struct HashRow
{
    unsigned int size;
    item *first;
    item *last;
};

class HashT
{
public:
    HashT(); // Construction
    void insert(string key, int value);
    unsigned int Hash(string key); //  a hash function
    void ListAll();

private:
    int N;
    int M;
    HashRow *HArray;
};

HashT::HashT()
{
    M = 7;
    HArray = new HashRow[M];
    N = 0;
    for (int i; i < M; i++)
    {
        HArray[i].first = NULL;
        HArray[i].last = NULL;
        HArray[i].size = 0;
    }
}

void HashT::insert(string key, int value)
{
    unsigned int loc = Hash(key);

    // cout << key << " " <<  value << " " << loc << endl;

    item *NewItemPtr = new item; //  dynamically create a new struct/item
    if (NewItemPtr == NULL)
        return; // not enought memory

    NewItemPtr->key = key; // we append, add to end of list
    NewItemPtr->value = value;
    NewItemPtr->next = NULL;

    if (HArray[loc].first == NULL) // first item to be added
    {
        HArray[loc].first = NewItemPtr;
        HArray[loc].last = NewItemPtr;
    }
    else
    {
        (HArray[loc].last)->next = NewItemPtr;
        HArray[loc].last = NewItemPtr;
    }
    HArray[loc].size++;
    N++;
}

void HashT::ListAll()
{
    item *it;
    for (unsigned short locC = 0; locC < M; locC++)
    {
        cout << HArray[locC].size << " items: ";

        it = HArray[locC].first;

        while (it != NULL)
        {
            cout << it->key << "->" << it->value << "   ";
            it = it->next;
        }
        cout << endl;
    }
}

unsigned int HashT::Hash(string key)
{
    unsigned int b = 378551; // a prime number
    unsigned int a = 63689;  // Another prime number
    unsigned int hash = 0;

    for (std::size_t i = 0; i < key.length(); i++)
    {
        hash = hash * a + key[i];
        a = a * b;
    }
    return (hash % M);
}

string RandomStr(); // A function to randomly generate 10  chars strings.

int main(int argc, const char *argv[])
{

    HashT MyHash;
    string AddMe;
    for (int i = 0; i < 100; i++)
    { // Add 100 items.
        AddMe = RandomStr();
        MyHash.insert(AddMe, rand() % 200);
    }

    MyHash.ListAll();
}

string RandomStr()
{
    string AddMe = "0123"; // A string example  we will randomle generate
    for (int j = 0; j < 4; j++)
    {
        AddMe[j] = rand() % 25 + 65;
    }
    return AddMe;
}