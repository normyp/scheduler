#ifndef _PERSON_H_
#define _PERSON_H_

using namespace std;
#include <string>

class Person
{
	string _name;
	int _daysAvailable; //vector of dates - date class
	bool _driver;
	int timesUsed;
public:
	Person(string name, bool driver);
	bool isDriver();
	//int getDate(int daysAvailable);
	string getName();

	void setLegal(bool driver, bool _driver);
	//void setDate(int daysAvailable, int _daysAvailable);
	void setName(string name, string _name);
};

#endif _PERSON_H_