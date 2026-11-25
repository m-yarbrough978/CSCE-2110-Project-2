/*

Purpose:
 
This program is built to implement a Campus Facilities Directory that uses
lets a user locate facilities, explore building connections, find routes, browse a
department hierarchy, and view summary reports. It uses a hash table to store and
look for facilities, an undirected graph for campus buildings and walkways, and a
general tree for the department heirarchy.

Some implementations, such as the facility category report, are not implemented into
the code yet because they are not required for Milestone 1.

Author: Micah Yarbrough, Dabira Olubobola, and Jayden Thompson

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "HashTable.h"
#include "Facility.h"
#include "CampusGraph.h"
#include "BFS.h"

using namespace std; 

int main (){

	HashTable hTab;
	
	cout << "+--------------------------------------------------+" << endl;
	cout << "|         Computer Science and Engineering         |" << endl;
	cout << "|              CSCE 2110 - Project 2               |" << endl;
	cout << "|     Micah Yarbrough micahyarbrough@my.unt.edu    |" << endl;
	cout << "| Dabira olubobola OluwadabiraOlubobola@my.unt.edu |" << endl; 
	cout << "|    Jayden Thompson jaydenthompson2@my.unt.edu    |" << endl;
	cout << "+--------------------------------------------------+" << endl << endl;

	CampusGraph graph; //creates the campus graph

	ifstream buildFile; 				//creates the buildFile to be used for reading "buildings.txt"
	buildFile.open("buildings.txt");   //opens "buildings.txt" to be read
	
	if(buildFile.fail()){
		
		cout << "Error opening buildings.txt." << endl;		//add a more meaningful message?
		
	}
	else{
		string buildingName;

		while(getline(buildFile, buildingName)) {
			if(!buildingName.empty()) {
				graph.addBuilding(buildingName);
			}
		}
		buildFile.close();
		cout << "buildings.txt loaded successfully." << endl;
		
		//add load summary
	}

	ifstream conFile;
	conFile.open("connections.txt");
	
	if(conFile.fail()){
		
		cout << "Error opening connections.txt." << endl;		//add a more meaningful message?
		
	}
	else{
		string line;

		while(getline(conFile, line)) {
			size_t separator = line.find('|');

			if(separator != string::npos){
				string building1 = line.substr(0, separator);
				string building2 = line.substr(separator + 1);

				graph.addConnection(building1, building2);
			}
		}
		
		conFile.close();		
		cout << "connections.txt loaded successfully." << endl;
		
		//add load summary
	}
	
	ifstream facFile;
	facFile.open("facilities.txt");
	
	if(facFile.fail()){
		
		cout << "Error opening facilities.txt." << endl;		//add a more meaningful message?
		
	}
	else{
		
		cout << "facilities.txt loaded successfully." << endl;
		hTab.StoreFacility(facFile);
		
		cout << endl << "Load summary" << endl;
		cout << "------------" << endl;
		cout << "Facilities Accepted: " << hTab.GethTableSize() << endl;
		cout << "Facilities Rejected: " << hTab.GetnumReject() << endl;
		cout << "Hash Capacity: " << hTab.GetnumBuckets() << endl;
		cout << "Entries: " << hTab.GethTableSize() << endl;
		cout << "Collisions: " << hTab.GetnumCol() << endl << endl;
	}
	
	ifstream depFile;
	depFile.open("departments.txt");
	
	if(depFile.fail()){
		
		cout << "Error opening departments.txt." << endl;		//add a more meaningful message?
		
	}
	else{
		
		cout << "departments.txt loaded successfully." << endl;
		
		//add load summary
	}
	
	string choice;
	
	do{
		
		cout << endl;
		cout << "<<<  Campus Facilities Directory System  >>>" << endl;
		cout << "1. View all facilities                      " << endl;
		cout << "2. Search facility by ID                    " << endl;
		cout << "3. Search facility by name                  " << endl;
		cout << "4. Search facility by category              " << endl;
		cout << "5. View campus graph                        " << endl;
		cout << "6. Display graph counts and degrees         " << endl;
		cout << "7. Find Reachable buildings (BFS)           " << endl;
		cout << "8. Find shortest path (BFS)                 " << endl;
		cout << "9. Add department                           " << endl;
		cout << "10. Search department                       " << endl;
		cout << "11. Display department heirarchy            " << endl;
		cout << "12. Preorder traversal                      " << endl;
		cout << "13. Postorder traversal                     " << endl;
		cout << "14. Level-order traversal                   " << endl;
		cout << "15. Department statistics                   " << endl;
		cout << "16. Facility Category Report                " << endl;
		cout << "17. Graph Connectivity Report               " << endl;
		cout << "0. Exit                                     " << endl << endl;
		
		cout << "Enter your choice: ";
		getline(cin, choice);
		
		if(choice == "1"){

			hTab.Print();
			
		}
		else if(choice == "2"){
			
			cout << "Enter facility ID (F###): " << endl;
			getline(cin, choice);
			
			if(choice.size() != 4){
				
				cout << endl << "Invaild facility ID. Please try again with a facility that is 4 characters." << endl;
			
				//the coditions allow the menu to reject an invalid user-inputted facility ID shorter or longer than 4 characters
			}
			else{

				int i, sCount;
				int charCount = 0;
			
				for(i = 0; i < choice.size(); ++i){
				
					if(isalnum(choice.at(i))){
						
						++charCount;
					}
					
					if(charCount == 1){
						
						sCount = i;
					}
				}
			
				choice.erase(0, sCount);
			
				choice.at(0) = toupper(choice.at(0));					//capitilizes the f in the facility ID beofre passing into error handling and hTab's SearchByID function
				
				char c2, c3, c4;
				c2 = static_cast<char>(choice.at(1));
				c3 = static_cast<char>(choice.at(2));
				c4 = static_cast<char>(choice.at(3));
				
				if((choice.at(0) != 'F') || (isdigit(c2) == 0) || (isdigit(c2) == 0) || (isdigit(c3) == 0)){
					
					cout << endl << "Invaild facility ID. Please try again in the form F### or f###." << endl;
					
					//the coditions allow the menu to reject an invalid user-inputted facility ID
				}
				else{
					
					hTab.SearchByID(choice);
				}
				
			}
			
		}
		else if(choice == "3"){

			cout << endl << "Enter facility name: " << endl;
			getline(cin, choice);
			
			int i, sCount;
			int charCount = 0;
			
			for(i = 0; i < choice.size(); ++i){
				
				if(isalnum(choice.at(i))){
					
					++charCount;
				}
				
				if(charCount == 1){
					
					sCount = i;
				}
			}
			
			choice.erase(0, sCount);
			
			if(choice.size() <= 0){
				
				cout << endl << "Invaild facility name. Please try again with a facility name." << endl;
			}
			else{
				
				hTab.SearchByName(choice);
				
			}
			
		}
			
		else if(choice == "4"){

			cout << endl << "Enter facility category: " << endl;
			getline(cin, choice);
			
			int i, sCount;
			int charCount = 0;
			
			for(i = 0; i < choice.size(); ++i){
				
				if(isalnum(choice.at(i))){
					
					++charCount;
				}
				
				if(charCount == 1){
					
					sCount = i;
				}
			}
			
			choice.erase(0, sCount);
			
			if(choice.size() <= 0){
				
				cout << endl << "Invaild facility category. Please try again with a facility category." << endl;
			}
			else{
				
				hTab.SearchByCategory(choice);
				
			}
			
		}
			
		else if(choice == "5"){


			
		}
			
		else if(choice == "6"){
			
			
			
		}
		else if(choice == "7"){
			
			
			
		}
		else if(choice == "8"){
			
			
			
		}
		else if(choice == "9"){
			
			
			
		}
		else if(choice == "10"){
			
			
			
		}
		else if(choice == "11"){
			
			
			
		}
		else if(choice == "12"){
			
			
			
		}
		else if(choice == "13"){
			
			
			
		}
		else if(choice == "14"){
			
			
			
		}
		else if(choice == "15"){
			
			
			
		}
		else if(choice == "16"){
			
			
			
		}
		else if(choice == "17"){
			
			
			
		}
		else if(choice != "0"){
			
			cout << endl << "Invalid choice. Please chose one of the menu options." << endl << endl;
			
		}
		
	}while(choice != "0");
  
 
	cout << endl << "Thank you for using the Campus Facilities Directory system. Goodbye!" << endl << endl;
 
	return 0;
}
