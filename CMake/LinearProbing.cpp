// Mutlu Mete
// Linear probing demo

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip>      // std::setw
// #define N  10


using namespace std;


class LinearProb
{
public:
	LinearProb(); 					// Construction
	void put(string key, int val);
	int get(string key);
	unsigned int Hash(string key); //  a simple hash function
	void ListAll();

private:
	int M;
	string *keys;
	int *vals;
};

LinearProb::LinearProb()
{
	M = 20;
	keys = new string[M];
	vals = new int[M];
	for (int i=0; i < M; i++)
	{		
		keys[i] = "";
		vals[i] = 0;
	}
}

void LinearProb::put(string key, int val) 
   {
      int i;
      for (i = Hash(key); keys[i] != ""; i = (i+1) % M)
         if (keys[i] == key)
             break;
      keys[i] = key;
      vals[i] = val;
   }

unsigned int LinearProb::Hash(string key)
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


void LinearProb::ListAll()
{	
	for (int locC = 0; locC < M; locC++)
	{
		cout << keys[locC] << " -> " << vals[locC];
		cout << endl;
	}
}

string RandomStr();  // A function to randomly generate 10  chars strings.

int main(int argc, const char * argv[]) {

	LinearProb MyHash;
	string AddMe;
	for (int i = 0; i< 10; i++) { // Add 100 items.
		AddMe = RandomStr();
		MyHash.put(AddMe, i);
	}

	MyHash.ListAll();
	system("pause");
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
