

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

		hKey = Hash(tempStr);
		
		if(lineCount > 1){
			
			int dupe = 0;
			int tempKey = 0;
			
			for(i = 0; i < hTable.size(); ++i){
				
				tempPair = hTable[i];
				
				if(hKey == tempPair.key){
					
					for(j = 0; j < hTable.size(); ++j){
						
						tempPair = hTable[j];
						
						if(tempKey < tempPair.key){
							
							tempKey = tempPair.key;
						}
						else if(tempKey > tempPair.key){
							
							continue;
						}
						
					}
					
					tempPair = {tempKey + 1, tempFac};
					hTable.push_back(tempPair);
					++numCol;
					++dupe;
					break;
				}
				
			}
			
			
			if(dupe == 0){
				tempPair = {hKey, tempFac};
				hTable.push_back(tempPair);
			}
			
		}
		else if(lineCount == 1){
			
			tempPair = {hKey, tempFac};
			hTable.push_back(tempPair);
			
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
		
		tempPair = hTable[i];
		tempFac = tempPair.fac;
		
		cout << left << "|" << setw(12) << tempFac.GetID() << "|";
		cout << setw(17) << tempFac.GetFName() << "|";
		cout << setw(21) << tempFac.GetBName() << "|";
		cout << setw(23) << tempFac.GetCategory() << "|" << endl; 
		
	}

	cout << "+----------------------------------------------------------------------------+" << endl << endl;
}

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
	cout << "+-----------------------------------------------------------------------------+" << endl;
	cout << "| Facility ID |  Facility Name  |    Building Name    |   Facility Category   |" << endl;
	cout << "|-----------------------------------------------------------------------------|" << endl;
	cout << left << "|" << setw(12) << tempPair.fac.GetID() << "|";
	cout << setw(17) << tempPair.fac.GetFName() << "|";
	cout << setw(21) << tempPair.fac.GetBName() << "|";
	cout << setw(23) << tempPair.fac.GetCategory() << "|" << endl;
	cout << "+-----------------------------------------------------------------------------+" << endl << endl;
	
}
