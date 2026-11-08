

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

void HashTable::StoreFacility(ifstream& facFile){
	
	list<key_Fac> tempList;
	key_Fac tempPair;
	Facility tempFac;
	char line[100];
	string tempStr;
	int lineCount = 1;
	int i, hKey;
	
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
					
					tempStr = line;
					tempStr.erase(count - 1);
					tempFac.SetID(tempStr);
					countA = count;
				}
				else if(barCount == 2){
					
					tempStr = line;
					tempStr.erase(0, countA);
					
					if((lineCount == 5) || (lineCount == 7) || (lineCount == 9)){
						tempStr.erase(8);
					}
					else if((lineCount == 4) || (lineCount == 6) || (lineCount == 8)){
						tempStr.erase(14);
					}
					else if(lineCount == 1){
						tempStr.erase(17);
					}
					else if(lineCount == 10){
						tempStr.erase(18);
					}
					else if(lineCount == 2){
						tempStr.erase(21);
					}
					else if(lineCount == 3){
						tempStr.erase(23);
					}
					
					tempFac.SetFName(tempStr);
					countB = count;
				}
				else if(barCount == 3){
					tempStr = line;
					tempStr.erase(0, countB);
					
					if((lineCount < 5) || (lineCount == 16) || (lineCount == 9) || (lineCount == 10) || (lineCount == 18)){
						tempStr.erase(10);
					}
					else if((lineCount >= 5) && (lineCount < 9) || (lineCount == 17)){
						tempStr.erase(6);
					}
					else if((lineCount == 11) || (lineCount == 12) || (lineCount == 13) || (lineCount == 19)){
						tempStr.erase(13);
					}
					else if((lineCount == 14) || (lineCount == 15) || (lineCount == 20)){
						tempStr.erase(20);
					}
					
					tempFac.SetBName(tempStr);
					countC = count;
					
					tempStr = line;
					tempStr.erase(0,countC);
					tempFac.SetCategory(tempStr);
				}
			}
			else if(line[i] != '|'){
				
				continue;
			}
			
		}
		
		tempStr = tempFac.GetID();
		
		if(lineCount > 1){
			
			hKey = Hash(tempStr);
			
			for(i = 0; i < hTable.size(); ++i){
			
				tempList = hTable[i];
				tempPair = tempList.front();
				
				if(hKey == tempPair.key){
					
					++numCol;
					tempPair = {hKey, tempFac};
					tempList.push_back(tempPair);
					hTable.erase(hTable.begin() + i);
					hTable.push_back(tempList);
				}
				else if(hKey != tempPair.key){
					
					list<key_Fac> tempList2;
					tempPair = {hKey, tempFac};
					tempList2.push_back(tempPair);
					hTable.push_back(tempList2);
				}
				
			}
			
		}
		else if(lineCount == 1){
			
			hKey = Hash(tempStr);
	
			tempPair = {hKey, tempFac};
			tempList.push_back(tempPair);
			hTable.push_back(tempList);
		}
		
		++lineCount;
		
	}
	
}

void HashTable::Print(){
	
	int i, hKey, j;
	key_Fac tempPair;
	Facility tempFac;
	
	cout << endl;
	cout << "+----------------------------------------------------------------------------+" << endl;
	cout << "|Facility ID |  Facility Name  |    Building Name    |   Facility Category   |" << endl;
	cout << "|----------------------------------------------------------------------------|" << endl;
	
	for(i = 0; i < hTable.size(); ++i){
		
		list tempList = hTable[i];
		list copyList = tempList;
		
		tempPair = copyList.front();
		tempFac = tempPair.fac;
		
		/*
		copyList = tempList;
		
		for(j = 0; j < copyList.size(); ++j){
			
			tempPair = copyList.front();
			tempFac = tempPair.fac;
			
			if(tempFac.GetID() == tempStr){
				
				break;
			}
			else{
				
				copyList.pop_front();
				continue;
			}
		}
		
		*/
	
		cout << left << "|" << setw(12) << tempFac.GetID() << "|";
		cout << setw(17) << tempFac.GetFName() << "|";
		cout << setw(21) << tempFac.GetBName() << "|";
		cout << setw(23) << tempFac.GetCategory() << "|" << endl;
		cout << "Number of Collisions: " << numCol << endl; 
		
		copyList.pop_front();
		
	}
	
	cout << hTable.size() << endl;
	cout << numCol << endl;
	
	
	cout << "+----------------------------------------------------------------------------+" << endl << endl;
}