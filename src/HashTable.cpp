/*

Purpose:

This source file provides the implementation of the function declarations, private variables, and the hash
table that are defined in HashTable.h. It has a custom hash function is used to store the facilities recorded
in facilities.txt into the hash table using the facility ID. The hash table is Open Adressing and uses Linear 
Probing to handle collisions. Their are also functions for printing the hash table in file order and searching
the table by hashing a user-inputted facility ID.

Some functions, such as SearchByName and SearchByCategory, are not implemented into
the code yet because they are not required for Milestone 1.

Author: Micah Yarbrough

*/

#include "HashTable.h"

using namespace std;

int HashTable::Hash(string facID){
	
	int hashNum = 0;
	int i;
	
	for(i = 0;i < 4; ++i){
		
		hashNum = hashNum + static_cast<int>(facID[i]);
		
	}
	
	hashNum = hashNum % numBuckets;
	
	return hashNum;
	
}

/*
	The Hash(string facID) takes the inputted string and runs it through the custom hash function,
	and then returns the result, which becomes a hash key. The hash function is below.
	
	key = (ASCII(facID[0]) + ASCII(facID[1]) + ASCII(facID[2]) + ASCII(facID[3])) % numBuckets
	
	where numBuckets = 241
*/

void HashTable::StoreFacility(ifstream& facFile){
	
	key_Fac tempPair;
	Facility tempFac;
	char line[100];
	string tempStr;
	int lineCount = 1;
	int i, j , hKey;
	
	facFile.ignore(numeric_limits<streamsize>::max(), '\n');	//ensures the first line of the file is skipped
	
	
	while(facFile.getline(line, 100)){
		
		int barCount = 0;
		int count, countA, countB, countC;
		
		count = 0;
		countA = 0;
		countB = 0;
		countC = 0;
		
		for(i = 0; i < 100; ++i){
			
			++count;
			
			if(line[i] == '|'){
				
				++barCount;
				
				if(barCount == 1){
					
					countA = count;
				}
				else if(barCount == 2){
					
					countB = count;
				}
				else if(barCount == 3){
					
					countC = count;
				}
			}
			else if(line[i] != '|'){
				
				continue;
			}
			
		}

		tempStr = line;
		tempStr.erase(4);
		tempStr.at(0) = toupper(tempStr.at(0));		//capitilizes the f in the facility ID beofre hashing or putting it into tempFac
		tempFac.SetID(tempStr);
		
		/*
			Ensures that the facility ID has no whitespace and is uppercase normalized
		*/
		
		tempStr = line;
		tempStr.erase(0, countA);
		countA = countB - countA - 1;
		tempStr.erase(countA);
		tempFac.SetFName(tempStr);
		
		/*
			Ensures that the facility name has no whitespace for any length of facility name
		*/
		
		tempStr = line;
		tempStr.erase(0, countB);
		countB = countC - countB - 1;
		tempStr.erase(countB);
		tempFac.SetBName(tempStr);
		
		/*
			Ensures that the building name has no whitespace for any length of building name
		*/
		
		tempStr = line;
		tempStr.erase(0, countC);
		tempFac.SetCategory(tempStr);
		
		/*
			Ensures that the facility category has no whitespace for any length of facility category (unless it has comments after the line, which needs to be fixed)
		*/
		
		tempStr = tempFac.GetID();

		hKey = Hash(tempStr);

		int dupeID = 0;
		char c2, c3, c4;
		c2 = static_cast<char>(tempStr.at(1));
		c3 = static_cast<char>(tempStr.at(2));
		c4 = static_cast<char>(tempStr.at(3));

		for(i = 0; i < hTable.size(); ++i){				//this for-loop checks if any of the elements in the hash table have the same facility ID as the new facility that we want to add
			
			tempPair = hTable[i];
			
			if(tempStr == tempPair.fac.GetID()){
				++dupeID;
				break;
			}
			else{
				continue;
			}
		}
		
		if((tempStr.size() != 4) || (tempStr.at(0) != 'F') || (isdigit(c2) == 0) || (isdigit(c2) == 0) || (isdigit(c3) == 0) || (tempFac.GetFName().size() < 2) || (tempFac.GetCategory().size() < 2)){
			
			++numReject;
			continue;
			
			//the coditions allow the code to reject any line that has an invalid key and an empty facility name or category
		}
		else if((dupeID == 1)){		//this condition allows the code to reject a facility in facilites.txt with a duplicate ID
			
			++numReject;
			continue;
		}
		else{
			
			if(lineCount > 1){									//this conditional statement checks if the program is currently on line 1
			
				int dupe = 0;		//dupe is used to tell if a facility has been seen already.
				int tempKey = hKey;	//copy of hKey to preserve hKey's value
			
				for(i = 0; i < hTable.size(); ++i){
				
					tempPair = hTable[i];
				
					if(tempKey == tempPair.key){				//this for-loop implements a rough linear probing collision handling strategy
					
					
						for(j = 0; j < hTable.size(); ++j){
						
							tempPair = hTable[j];
							
							if(tempKey == tempPair.key){
								
								++numCol;
							}
							else{
								
								break;
							}
							
							
							if(hKey >= 241){					//this if-else statement should make hKey 0 when it equals maax capacity (although then we'd need to check it against the either buckets)
								tempKey = tempKey - 241;
							}
							else if(tempKey < 241){
								++tempKey;
							}
							
						}
						
						tempPair = {tempKey, tempFac};
						hTable.push_back(tempPair);
						++dupe;
						break;
					}
					else{
						
						continue;
					}
					
				}
			
			
				if(dupe == 0){							//if a duplicate facility ID wasn't found, then enter the new facility with tempPair unaffected by collsion handling
					tempPair = {hKey, tempFac};
					hTable.push_back(tempPair);
				}
				
			}
			else if(lineCount == 1){					//if this is the first line fully searched, then enter the first facility into the hash table
			
				tempPair = {hKey, tempFac};
				hTable.push_back(tempPair);
				
			}
		
			++lineCount;
		}
		
	}
	
}

/*
	The StoreFacility(ifstream& facFile) takes the facility records stored inside facilities.txt
	and puts them into the hash table by hashing their facility ID. It also has implementation to
	perform Linear Probing collision handling, rejecting lines with invalid facility records, and
	checking to see if a facility in the hash table is already using the facility ID that a later
	line is trying to use.
*/

void HashTable::Print(){
	
	int i, hKey, j;
	key_Fac tempPair;
	Facility tempFac;
	
	cout << endl;
	cout << "Facility with ID " << facID << " found." << endl;
	cout << "+--------------------------------------------------------------------------------------+" << endl;
	cout << "|Facility ID |     Facility Name     |    Building Name    |     Facility Category     |" << endl;
	cout << "|--------------------------------------------------------------------------------------|" << endl;
	
	for(i = 0; i < hTable.size(); ++i){
		
		tempPair = hTable[i];
		tempFac = tempPair.fac;
		
		cout << left << "|" << setw(13) << tempFac.GetID() << "|";
		cout << setw(25) << tempFac.GetFName() << "|";
		cout << setw(21) << tempFac.GetBName() << "|";
		cout << setw(25) << tempFac.GetCategory() << "|" << endl; 
		
	}

	cout << "+----------------------------------------------------------------------------+" << endl << endl;
}

/*
	The Print() function prints the elements in the hash table in the same order as facilities.txt.
*/

void HashTable::SearchByID(string facID){
	
	int hKey = Hash(facID);
	int i;
	key_Fac tempPair;
	
	for(i = 0; i < hTable.size(); ++i){
		
		tempPair = hTable[i];
		
		if(hKey == tempPair.key){
			
			if(facID == tempPair.fac.GetID()){
				
				break;
			}
			
		}
		else{
			
			continue;
		}
	}
	
	cout << endl;
	cout << "Facility with ID " << facID << "found." << endl;
	cout << "+---------------------------------------------------------------------------------------+" << endl;
	cout << "| Facility ID |     Facility Name     |    Building Name    |     Facility Category     |" << endl;
	cout << "|---------------------------------------------------------------------------------------|" << endl;
	cout << left << "|" << setw(13) << tempPair.fac.GetID() << "|";
	cout << setw(25) << tempPair.fac.GetFName() << "|";
	cout << setw(21) << tempPair.fac.GetBName() << "|";
	cout << setw(25) << tempPair.fac.GetCategory() << "|" << endl;
	cout << "+-----------------------------------------------------------------------------+" << endl << endl;
	
}

/*
	The SearchByID(string facID) function a valid user-inputted facility ID, hashes it using the
	the hash function, and checks that hash against the other hash keys in the hash table. When
	the program finds a matching hash key, it checks the facility ID of that facility to make
	sure its the correct facility. If the facility matches, it outputs a found message and 
	the information regarding the facility.
	
	If the facility ID doesn't match, the code knows this is a collision and tries to find where 
	the collided facility is now. When it finds the facility, it outputs a found message and 
	the information regarding the facility.
	
	If no facility with the user-inputted facility ID is found, it outputs a not found message.
*/

int HashTable::GethTableSize() const{
	return hTable.size();
}

/*
	The GethTableSize() function returns the size of the hash table. This is for the facilities.txt
	load summary.
*/

void HashTable::SetnumBuckets(int numBucketsX){
	numBuckets = numBucketsX;
}

int HashTable::GetnumBuckets() const{
	return numBuckets;
}

void HashTable::SetnumCol(int numColX){
	numCol = numColX;
}

int HashTable::GetnumCol() const{
	return numCol;
}

void HashTable::SetnumReject(int numRejectX){
	numReject = numRejectX;
}

int HashTable::GetnumReject() const{
	return numReject;
}
