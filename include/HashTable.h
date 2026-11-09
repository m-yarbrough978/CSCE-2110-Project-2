/*

Purpose:

This header file provides the function declarations, private variables, and the hash
table that are used in HashTable.cpp.

Some declarations, such as SearchByName and SearchByCategory, are not implemented into
the code yet because they are not required for Milestone 1.

Author: Micah Yarbrough

*/

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
		int GethTableSize() const;				//Returns hash table size which is needed for the facilities load summary
		void SetnumBuckets(int numBucketsX);	//Mutator for total number of buckets (technically not used)
		int GetnumBuckets() const;				//Accessor for total number of buckets
		void SetnumCol(int numColX);			//Mutator for total number of collisions (technically not used)
		int GetnumCol() const;					//Accessor for total number of collisions
		void SetnumReject(int numRejectX);		//Mutator for total number of rejected facilities (technically not used)
		int GetnumReject() const; 				//Accessor for total number of rejected facilities
		
	
	
	private:
		struct key_Fac{
	
			int key;
			Facility fac;
			int pCol;			//personal collisions
			
		};
		
		vector<key_Fac> hTable;						//defines the hashtable from a vector of a list of structs
		int numBuckets = 241;						//total number of buckets in the hash table
		int numCol = 0;								//total number of collisions found during StoreFacility function
		int numReject = 0;							//total number of rejected facilities from facilities.txt
		
	
	
};



#endif