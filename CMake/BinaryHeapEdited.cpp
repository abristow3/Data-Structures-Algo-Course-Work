//
//  Alex Bristow
//
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

// The program lunches here
int main(int argc, char *argv[]) {
    int SIZE = 20;
    string line;
    // get file path and name from command line args
    string file = argv[1];

    ifstream infile(argv[1]);

    // Open fle and iterate over each line that gets read in until no lines left
    while (getline(infile, line, '\n')) {
        stringstream ss(line);

        // Setting default values for each line that gets read to ensure no values carry over
        // from previous line
        int count = 0;
        int arr[SIZE];
        bool heap_flag = true;

        // get a total count of numbers from the current row being read in
        while (count < SIZE && ss >> arr[count]) {
            count += 1;
        }

        // start with k=1 to ensure we skip index 0 of array
        for (int k = 1; k < count; k++) {
            // if left child exists and it's value is greater than parent values
            // or if right child exists and it's value is greater than the parent values
            // set our flag to False and break the loop
            if (2 * k < count && arr[2 * k + 1] > arr[k] || (2 * k + 1) < count && arr[2 * k + 1] > arr[k]) {
                heap_flag = false;
                break;
            }
        }
        // print based on flag value
        if (heap_flag) {
            std::cout << "True" << endl;
        } else {
            std::cout << "False" << endl;
        }
    }
}


