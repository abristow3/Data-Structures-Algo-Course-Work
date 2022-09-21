// Alex Bristow
// CWID 50209772
// 09/21/2022

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

// A struct to keep items
struct item {
    string data;
    item *next;

    item(string x, item *t) { // constructor for each new struct
        data = x;
        next = t;
    }
};

typedef item *lnk;  // easy way to create a new "link"

// A class to represent Bag, which can hold strings in a linked list
// The items (strings) are not sorted in the list.
class Bag {
public:
    Bag();                            // Construction
    bool add(string str);            // Adds a new item to bag
    void has(string str);            // Check if Bag has this item
    unsigned short getCapacity();    // Returns the capacity of the Bag. Is there any capacity
    void ListBag();                    // List all items of Bag.
private:
    lnk first;                        // A pointer to show the first node
    lnk last;                        // A pointer to show the last node
    unsigned short size;            // how many items this Bag has

};

Bag::Bag() // Initialize an instance of the class
{
    size = 0;
    first = last = NULL; // At the beginning both, first and last are null
    cout << "A backup plan for " << getCapacity() << " employees is ready." << endl;

}

bool Bag::add(string str) {
    lnk AddItem = new item(str, NULL);            //  dynamically create a new struct/item
    if (AddItem == NULL) return false;        //   not enought memory

    if (first == NULL) {
        first = AddItem;
        cout << first->data << " is the manager of the store." << endl;// first item to be added
    } else last->next = AddItem;                    // add to the end of array

    last = AddItem;
    size++;
    return true;    // Yeah, added.
}

void Bag::ListBag()                        // List, print out, all items in the arrays, // make 5 coloumns
{
    lnk it = first;                    // it means iterator, visit all items one by one.
    int i = 0;                            // i is used to format the output
    while (it != NULL) {
        if (it->next != NULL) {
            cout << it->data << " -> " << it->next->data << ", ";
        } else { cout << last->data << " -> " << first->data << endl; }
        it = it->next;
        if ((i + 1) % 10 == 0) cout << endl;
        i++;
    }
    cout << endl;
}


void Bag::has(string str)   // Check if the bag has item "str"
{
    lnk it = first;
    string prev_it = it->data;
    bool exists = false;
    for (int i = 0; i < size; i++) {
        if (i == 0 and it->data == str) {
            cout << it->data << " is backup by " << last->data << endl;
            exists = true;
            break;
        } else if (it->data == str) {
            cout << it->data << " is backup by " << prev_it << endl;
            exists = true;
        }
        prev_it = it->data;
        it = it->next;
    }
    if (!exists) {
        cout << "There is no employee named " << str << endl;
    }
}

unsigned short Bag::getCapacity() {
    return 10;        // A made-up number.
}

int randomIntBetween() {
    int low = 65;
    int high = 90;
    return rand() % (high - low + 1) + low;
}

int main(int argc, const char *argv[]) {    //  not using command line arg for now
    srand(time(NULL));
    Bag bigBag;
    string tempStr;
    const int employee_size = 10;
    // array to hold employee names to assign during bag creation
    int names[employee_size] = {0};
    // keep track of how many employees have been made so we can continue name generation is duplicate name is chosen
    int iter = 0;

    // generate 10 unique names for employees with no duplicates.
    while (iter < 10) {
        //boolean var to flag if name is taken
        bool name_taken = false;
        //generate random number between 65 and 90 for ascii characters
        int rand_name = randomIntBetween();
        for (int i = 0; i < employee_size; i++) {
            int index_name = names[i];
            // change name taken flag to true and break loop to retry with a new number
            if (index_name == rand_name) {
                name_taken = true;
                break;
            }
        }
        // if name taken flag is true then continue onto another loop iteration
        if (name_taken) {
            continue;
        } else {  // else if false append array with name at iter index and create a bag with that ascii char, increment iter by 1
            names[iter] = rand_name;
            string ascii = "_";
            ascii = rand_name;
            bigBag.add(ascii);
            iter++;
        }
    }

    bigBag.ListBag();


    while (tempStr != "-") {
        cout << "Backup search for: ";
        cin >> tempStr;
        if (tempStr == "-") {
            cout << "Bye" << endl;
            break;
        }
        bigBag.has(tempStr);
    }
}