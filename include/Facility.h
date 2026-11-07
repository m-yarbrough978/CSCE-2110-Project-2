

#ifndef FACILITY_H
#define FACILITY_H

#include <string>

using namespace std;

class Facility{
	
	public:
		
		Facility();							//default constructor
		void SetID(string idX);				//Mutator for id
		string GetID() const;				//Accessor for id
		void SetFName(string fNameX);		//Mutator for facility name
		string GetFName() const;			//Accessor for facility name
		void SetBName(string bNameX);		//Mutator for building name
		string GetBName() const;			//Accessor for buildng name
		void SetCategory(string catX);		//Mutator for facility category
		string GetCategory() const; 		//Accessor for facility category
	
	
	private:
		string id, fName, bName, category;	
		
		//defines string variables for facility ID, name, building name, and facility category
	
	
	
};



#endif
