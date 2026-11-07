

#include <Facility.h>

using namespace std;


Facility::Facility(){
	
	id = "F000";
	fName = "NONE";
	bName = "Unknown";
	category = "N/A";
	
}

void Resource::SetID(string idX){
	id = idX;
}

string Resource::GetID() const{
	return id;
}

void Resource::SetFName(string fNameX){
	fName = fNameX;
}

string Resource::GetFName() const{
	return fName;
}

void Resource::SetBName(string bNameX){
	bName = bNameX;
}

string Resource::GetBName() const{
	return bName;
}

void Resource::SetCategory(string categoryX){
	category = categoryX;
}

string Resource::GetStatus() const{
	return category;
}
