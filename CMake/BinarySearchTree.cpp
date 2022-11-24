//
//  Mutlu Mete
//  BinarySearchTree
//


#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip>      // std::setw
// #define N  10

using namespace std;

// Node objects that each contain a key, associated value, two links, and a node count N. Each Node is the root of
// a subtree containing N nodes, with its left link pointing to a Node that is the root of a subtree with smaller keys and
// its right link pointing to a Node that is the root of a subtree with larger keys. Note that there is no same keys in the three. All keys are different.

struct Node
{
    string key; // key
    int val; // associated value
    Node* left; // links to left-subtrees
    Node* right; // links to right-subtrees
    int N; // # nodes in subtree rooted here
    Node(string Nkey, int Nval, int NN)
    {
        key = Nkey;
        val = Nval;
        N = NN;
        left = NULL;
        right = NULL;
    }
};

class BST // Binary search Symbol Table
{
public:
    BST();	//create an ordered symbol table
    void put(string key, int value); 	// put key-value pair into the table
    Node* put(Node* x, string key, int val);
    int* get(string key);			 	// value paired with key, (null if key is absent, then int*)
    int* get(Node* x, string key);

    int find(string key);				// returns
    bool contains(string key);			// is there a value paired with this key?
    bool isEmpty();						// is the table empty?
    void list(Node* x);					// show all keys
    int size(Node* x); 					// number of key-value pairs
    int size(); 						// number of key-value pairs
    string min();							// smallest key
    Node* min(Node* x);							// smallest key
    int max();							// largest key
    int floor(string key);				// largest key less than or equal to key
    int ceiling(string key);			// smallest key greater than or equal to key
    // int rank(Key key) number of keys less than key
    string select(int k);	// key of rank k
    void deleteMin(); 		// delete smallest key
    Node* deleteMin(Node* ); 		// delete smallest key
    void deleteMax(); 		// delete largest key

    void del(string key); // remove key (and its value) from tree, implement eager Hibbard deletion in BSTs,
    Node* del(Node*, string key);

    Node* getRoot();
private:
    Node* root; // root of BST

};

BST::BST()
{
    root = NULL;
}
int BST::size()
{ return size(root); }

Node* BST::getRoot()
{ return root; }

int BST::size(Node* x)
{
    if (x == NULL) return 0;
    else return x->N;
}


string BST::min()
{
    Node* t = min(root);
    if (t!=NULL) return t->key;
    return "No found";

}

Node* BST::min(Node* x)
{
    if (x->left == NULL) return x;
    return min(x->left);
}


void BST::deleteMin()
{
    root = deleteMin(root);
}

Node* BST::deleteMin(Node* x)
{
    if (x->left == NULL) return x->right;
    x->left = deleteMin(x->left);
    x->N = 1 + size(x->left) + size(x->right);
    return x;
}

void BST::del(string key)  { root = del(root, key); }

Node* BST::del(Node* x, string key)
{
    if (x == NULL) return NULL;


    if (key == x->key)
    {
        if (x->right == NULL) return x->left;
        if (x->left == NULL) return x->right;

        Node* t = x;
        x = min(t->right);
        x->right = deleteMin(t->right);
        x->left = t->left;
    }
    else if (key < x->key) { x->left  = del(x->left,  key); }
    else if (key > x->key)  { x->right  = del(x->right,  key); }

    x->N = 1 + size(x->left) + size(x->right);
    return x;
}



int* BST::get(string key) // search
{
 return get(root, key);
}

int* BST::get(Node* x, string key)
{  // Return value associated with key in the subtree rooted at x;
// return null if key not present in subtree rooted at x.

    if (x == NULL) return NULL;
    cout << key <<  " and " << x->key << endl;
    if (key == x->key)    { return &(x->val); } // &(x->val) // &((*x).val);
    else if (key < x->key)	return get(x->left,key);
    else if (key > x->key)	return get(x->right,key);

    return NULL;
}


void BST::put(string key, int val)
{ // Search for key. Update value if found; grow table if new.
    root = put(root, key, val);
}

Node* BST::put(Node* x, string key, int val)
{
    // Change key’s value to val if key in subtree rooted at x.
    // Otherwise, add new node to subtree associating key with val.
    if (x == NULL)
    {
        return new Node(key, val, 1);
    }

    if (key == x->key)	{ x->val = val;}
    else if (key < x->key)	x->left = put(x->left, key, val);
    else if (key > x->key)	x->right = put(x->right, key, val);

    x->N = size(x->left) + size(x->right) + 1;
    return x;
}

void BST::list(Node* x)
{
    if (x == NULL) return;
    cout << x->key << " " << x->val << endl;
    list(x->left);
    list(x->right);
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
    BST A;
    string AddMe;
    int AddValue=0;

    while (true) // a loop to search strings. "exit" exits the program
    {
        cout << "\nEnter a  string and number: ";
        cin >> AddMe >> AddValue;
        if (AddValue == 0) break;
        A.put(AddMe,AddValue);
        A.list(A.getRoot());

    }
    int* srch= NULL;

    while (true) // a loop to search strings. "exit" exits the program
    {
        cout << "\nEnter a  string to search ";
        cin >> AddMe;
        if (AddMe == "exit") break;
        srch=A.get(AddMe);
        if (srch != NULL) cout << *srch <<  endl;
        else cout <<  " Not Found " << endl;

    }
    while (true) // a loop to search strings. "exit" exits the program
    {
        cout << "\nEnter a  string to delete ";
        cin >> AddMe;
        if (AddMe == "exit") break;
        A.del(AddMe);
        A.list(A.getRoot());
    }

    cout << endl;
    A.list(A.getRoot());
    cout<< " ------\n ";



}











