// Alex Bristow
// Lab 3
// CSCI 520


#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <unistd.h> // From http://cs.dvc.edu/HowTo_CSleep.html

using namespace std;

// A struct to keep items
struct node {
    string data;
    node *next;

    node(char x, node *t) {
        data = x;
        next = t;
    }
};


typedef node *lnk;

// A class to represent Stack, where we push and pop items.
// The items (strings) are not sorted in the list.
class Stack {
public:
    Stack();                        // Construction
    bool push(char str);            // Adds a new item to stack
    bool pop();                    // remove the head guy (the most recently added item)     // Return the item on the top, the most recently added
    unsigned short getSize();        // How many items  the stack has
private:
    lnk head;                        // A pointer to show the head node
    unsigned short size;            // how many items stack has
};

// Initialize the class
Stack::Stack() {
    size = 0;
    head = NULL;
}

// How many items the Stack has
unsigned short Stack::getSize() {
    return size;
}

// add an item as the head one in the stack
bool Stack::push(char str) {
    lnk NewItemPtr = new node(str, head);    //  dynamically create a new struct/item
    if (NewItemPtr == NULL) return false;  // not enought memory
    head = NewItemPtr;
    size++;
    return true;    // Yeah, added.
}

// remove the head one from the stack
bool Stack::pop() {
    if (head == NULL) { return false; }

    lnk RemovePtr = head;
    head = head->next;
    delete RemovePtr;
    size--;
    return true;    // Yeah, removed.
}

int main(int argc, const char *argv[]) {

    Stack S;
    std::string user_input;

    // continue prompting user for input until they type exit
    while (user_input != "exit") {
        cout << "Enter an expression, or type 'exit' to end the program" << endl;
        std::getline(std::cin, user_input);

        //exit loop if user enters exit
        if (user_input == "exit") {
            cout << "bye." << endl;
        } else {
            //iterate over string and check each char
            for (int i = 0; i < user_input.size(); i++) {
                //if char at index == ( then add it to the stack
                if (user_input[i] == '(') {
                    S.push(user_input[i]);

                // if char at index == ")" then pop the stack to remove the "(" that it matches
                } else if (user_input[i] == ')') {
                    S.pop();
                }
            }

            // at end of loop, check stack size.
            //if size == 0 then valid parenthsis matches were found as no "(" are left on stack
            if (S.getSize() == 0) {
                cout << "True" << endl;

            // if size > 0 then unmatching parenthesis
            } else if (S.getSize() > 0) {
                cout << "False" << endl;
            }
        }
    }
}
