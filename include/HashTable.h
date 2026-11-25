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
		void SearchByName(string facName);		//prints the facility or facilities whose name matches a user-inputted facility name
		void SearchByCategory(string facCat);	//prints the facility or facilities whose category matches a user-inputted facility category
		void PrintCategoryReport();				//prints a report that tells us what facility categories are in the hash table and how many facilities are in that category
		void SetnumBuckets(int numBucketsX);	//Mutator for total number of buckets (technically not used)
		int GetnumBuckets() const;				//Accessor for total number of buckets
		void SetnumCol(int numColX);			//Mutator for total number of collisions (technically not used)
		int GetnumCol() const;					//Accessor for total number of collisions
		void SetnumReject(int numRejectX);		//Mutator for total number of rejected facilities (technically not used)
		int GetnumReject() const; 				//Accessor for total number of rejected facilities
		void SetnumPairs(int numPairsX);		//Mutator for total number of occupied buckets (technically not used)
		int GetnumPairs() const;				//Accessor for total number of occupied buckets
		

	
	private:
		struct key_Fac{
	
			int key;
			Facility fac;
			
		};
		
		vector<key_Fac> hTable;						//defines the hashtable from a vector of a list of structs
		vector<Facility> fileOrder;					//puts the accepted facilites into a different vector to preserve file order for the Print(), SearchByName(), and SearchByCategory() functions
		int numBuckets = 241;						//total number of buckets in the hash table
		int numCol = 0;								//total number of collisions found during StoreFacility function
		int numReject = 0;							//total number of rejected facilities from facilities.txt
		int numPairs = 0;							//total number of occupied buckets in the hash table
		
	
	
};



#endif
