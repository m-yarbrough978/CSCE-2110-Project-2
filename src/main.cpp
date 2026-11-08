#include <iostream>
#include <fstream>
#include <string>
#include "HashTable.h"
#include "Facility.h"

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

	ifstream buildFile; 				//creates the buildFile to be used for reading "buildings.txt"
	buildFile.open("buildings.txt");   //opens "buildings.txt" to be read
	
	if(buildFile.fail()){
		
		cout << "Error opening buildings.txt." << endl;		//add a more meaningful message?
		
	}
	else{
		
		cout << "buildings.txt loaded successfully." << endl;
		
		//add load summary
	}

	ifstream conFile;
	conFile.open("connections.txt");
	
	if(conFile.fail()){
		
		cout << "Error opening connections.txt." << endl;		//add a more meaningful message?
		
	}
	else{
		
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
		
		//add load summary
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

	hTab.StoreFacility(facFile);
	
	string choice;
	
	do{
		
		cout << endl;
		cout << "<<<  Campus Facilities Directory System  >>>" << endl;
		cout << "1. View all facilities                      " << endl;
		cout << "2. Search facility by ID                    " << endl;
		cout << "3. View campus graph                        " << endl;
		cout << "4. Display graph counts and degrees         " << endl;
		cout << "5. Find Reachable buildings (BFS)           " << endl;
		cout << "6. Add department                           " << endl;
		cout << "7. Search department                        " << endl;
		cout << "8. Display department heirarchy             " << endl;
		cout << "9. Run preorder traversal                   " << endl;
		cout << "0. Exit                                     " << endl << endl;
		
		cout << "Enter your choice: ";
		cin >> choice;
		
		if(choice == "1"){

			hTab.Print();
			
		}
		else if(choice == "2"){
			
			cout << "Enter facility ID (F###): " << endl;
			cin >> choice;
			
			hTab.SearchByID(choice);
			
		}
		else if(choice == "3"){

			
			
		}
		else if(choice == "4"){

			
			
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
		else if(choice != "0"){
			
			cout << endl << "Invalid choice. Please chose one of the menu options." << endl << endl;
			
		}
		
	}while(choice != "0");
  
 
	cout << endl << "Thank you for using the Campus Facilities Directory system. Goodbye!" << endl << endl;
 
	return 0;
}
