// Mutlu Mete
// Sparse Vector
// Demonstrate how to sum two sparse vectors.

#include <iostream>
#include <string>
#include <fstream>
// #include <unistd.h> // Optional, to stop execution of the program, From http://cs.dvc.edu/HowTo_CSleep.html

using namespace std;

const int SIZE = 1000;
// A struct to keep items
struct item {
    unsigned int index;
    int data;
    item *next;
};

// Maintains index, data association for the vector. Indexes are kept ordered.
// Do not confuse with STL vector, https://en.cppreference.com/w/cpp/container/vector

class Vector {
public:
    Vector();                                   // Construction
    bool add(unsigned int index, int data);

    void setSize(unsigned int size);

    void processFile(string row);

    std::string parseString(const std::string &file_delimiter, std::string row, size_t pos);

    void ListNonZeroes();

    Vector operator*(Vector &);

    item *getFirst();        // returns the pointer, "first"

private:
    item *first;                    // A pointer to show the first node
    item *last;                     // A pointer to show the last node
    unsigned short size;            // how many items vector has (kind of length)
    unsigned short compSize;        // non-zero items vector has
};

// Initialize the class
Vector::Vector() {
    first = last = NULL;
    size = 0;
}

item *Vector::getFirst() {
    return first;
}

// Lists all index with elements who are not 0
void Vector::ListNonZeroes() {
    item *it = first;
    int cnt = 0;

    while (it != NULL) {

        while (cnt < it->index) {
            cnt++;
        }
        if (it->data != 0) {
            cout << it->index << ":";
            cout << it->data << " ";
        }
        it = it->next;
        cnt++;
    }
    cout << endl;
}

Vector Vector::operator*(Vector &param) {
    Vector productVector;
    if (size != param.size) cout << "Something is wrong ..." << endl;
    cout << "Same size vectors found, summing vectors items now..." << endl;
    item *itA = first;
    item *itB = param.getFirst();

    while (itA != NULL || itB != NULL) {
        if (itA == NULL) {
            productVector.add(itB->index, itB->data);
            itB = itB->next;
        } else if (itB == NULL) {
            productVector.add(itA->index, itA->data);
            itA = itA->next;
        } else if (itA->index < itB->index) {
            productVector.add(itA->index, 0);
            itA = itA->next;
        } else if (itA->index > itB->index) {
            productVector.add(itB->index, 0);
            itB = itB->next;
        } else // Colliding indexes
        {
            productVector.add(itA->index, (itB->data * itA->data));
            itA = itA->next;
            itB = itB->next;
        }
    }
    productVector.setSize(size);
    return productVector;
}

// set the size of the vector
void Vector::setSize(unsigned int size) {
    this->size = size;
}

bool Vector::add(unsigned int index, int data)        // Adds a new item to Vector, to the end
{
    item *NewItemPtr = new item;                    // dynamically create a new struct/item
    if (NewItemPtr == NULL) return false;        // not enough memory

    NewItemPtr->index = index;                    // we append, add to end of list
    NewItemPtr->data = data;
    NewItemPtr->next = NULL;
    compSize++;

    if (last == NULL)                                // first item to be added
    {
        first = last = NewItemPtr;
    } else {
        last->next = NewItemPtr;
        last = NewItemPtr;
    }
    return true;    // Added.
}

// class method to process the input file string arg given in command line
void Vector::processFile(std::string row) {
    std::string file_delimiter = ", ";
    size_t pos = 0;

    // get substrings based on delimiter criteria given in instructions
    // Each substring is an index:value pair
    while ((pos = row.find(file_delimiter)) != std::string::npos) {
        // call parseString member method to split the index:value pair into an index and a value individually
        row = parseString(file_delimiter, row, pos);
        if ((pos = row.find(file_delimiter)) == std::string::npos) {
            row = parseString(file_delimiter, row, pos);
        }
    }
}

std::string Vector::parseString(const std::string &file_delimiter, std::string row, size_t pos) {
    std::string token;
    size_t pos2 = 0;
    std::string index_value_delimiter = ":";
    unsigned int vector_index;
    int vector_value;

    // splits index:value pair on the : as delimiter.
    //stores index in index arg for member method "add" call
    token = row.substr(0, pos);
    pos2 = token.find(":");
    vector_index = stoi(token.substr(0, pos2));

    //stores value in data arg for member method "add" call
    token.erase(0, pos2 + index_value_delimiter.length());
    vector_value = stoi(token);

    this->add(vector_index, vector_value);
    row.erase(0, pos + file_delimiter.length());
    return row;
}

int main(int argc, const char *argv[]) {
    string fname = argv[1];

    Vector A, B, ProductVector;
    A.setSize(25);
    B.setSize(25);

    // open txt file
    fstream myfile;
    myfile.open(fname);

    if (myfile.is_open()) {
        short line_num = 1;
        // for each line in .txt file, get the line and process is, if line is 1, store index and data pairs in vector A
        // if line is 2, store in vector B
        for (std::string line; std::getline(myfile, line);) {
            if (line_num == 1) {
                A.processFile(line);
            } else if (line_num == 2) {
                B.processFile(line);
            }
            line_num++;
        }
    } else {
        cout << "Unable to open your file! Please provide the absolute path as the arg if file not in same directory"
             << endl;
    }

    //multiply sparse vectors
    ProductVector = A * B;
    //list all non zeroes in product vector.
    ProductVector.ListNonZeroes();
}
