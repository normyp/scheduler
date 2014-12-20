#include <iostream>
#include "Person.h"
#include <vector>
#include "boost\date_time\gregorian\gregorian.hpp"
using namespace std;
using namespace boost;

Person::Person(string name, bool driver, vector<gregorian::date>daysAvailable) {
	_name = name;
	_daysAvailable = daysAvailable;
	_driver = driver;
	//int _timesUsed;
};

bool Person::isDriver()
{
	return _driver;
}

vector<gregorian::date> Person::getDate()
{
	return _daysAvailable;
}

string Person::getName()
{
	return _name;
}
