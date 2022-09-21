// Alex Bristow
// Random data generator
// Terminal > g++ ./randomDataGen.cpp -o ./randomDataGen ; ./randomDataGen
// VSCODE   > Terminal > Run Build Task

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

string randomStr();
int randomInt();
int randomIntBetween(int low, int high);

int main() {
	srand(time(NULL)); // random seed, to get different random number at each run.

	cout << "This progam generates a random number between 0 and " <<  RAND_MAX << endl;

	cout << "Random string:" << randomStr() << endl ;
	cout << "Random integer:" << randomInt() << endl ;

	cout << endl;
	for (int j = 0; j < 10; j++)
		cout << "Rand in [3,9]:" << randomIntBetween(3,9) << endl ;
}


string randomStr()
{
	string str = "____"; // A string  we will randomly generate
	for (int j = 0; j < 4; j++)	
		str[j] = rand() % 25 + 65; // between [65,89]	
	return str;
}

int randomInt()
{
	return rand();  // 
}

int randomIntBetween(int low, int high)
{
	return rand() % (high - low + 1) + low;
}
