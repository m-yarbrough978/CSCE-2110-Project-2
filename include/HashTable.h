

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Facility.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

class HashTable{
	
	public:
		int Hash(string facID);					//function that uses the string hash function on a facility ID
		void StoreFacility(ifstream& facFile);	//function that takes the facility file and puts it into the hash table
		void Print();							//prints the elements in the hash table using their indices
		void SearchByID(string facID);			//prints the facilty information for the facility (or facilities) by turing the ID into the key
		
	
	
	private:
		struct key_Fac{
	
			int key;
			Facility fac;
			
		};
		
		vector<key_Fac> hTable;						//defines the hashtable from a vector of a list of structs
		int numBuckets = 241;						//total number of buckets in the hash table
		int numCol = 0;								//total number of collisions found during StoreFacility function
		
	
	
};



#endif
