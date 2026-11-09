

#include "Facility.h"

using namespace std;


Facility::Facility(){
	
	id = "F000";
	fName = "NONE";
	bName = "Unknown";
	category = "N/A";
	
}

void Facility::SetID(string idX){
	id = idX;
}

string Facility::GetID() const{
	return id;
}

void Facility::SetFName(string fNameX){
	fName = fNameX;
}

string Facility::GetFName() const{
	return fName;
}

void Facility::SetBName(string bNameX){
	bName = bNameX;
}

string Facility::GetBName() const{
	return bName;
}

void Facility::SetCategory(string categoryX){
	category = categoryX;
}

string Facility::GetCategory() const{
	return category;
}
