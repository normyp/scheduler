#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>
#include <vector>
#include "boost\date_time\gregorian\gregorian.hpp"

using namespace std;
using namespace boost;

class Person
{
	string _name;
	vector<gregorian::date> _daysAvailable; //vector of dates - date class
	bool _driver;
	int timesUsed;

public:
	Person(string name, bool driver, vector<gregorian::date> dates);
	bool isDriver();
	vector<gregorian::date>getDate();
	string getName();
};

#endif _PERSON_H_