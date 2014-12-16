#include <iostream>
#include "Person.h"
using namespace std;

Person::Person(string name, bool driver) {
	_name = name;
	//_daysAvailable = daysAvailable;
	_driver = driver;
	//int _timesUsed;
};

bool Person::isDriver()
{
	return _driver;
}
/*int Person::getDate(int daysAvailable)
{
return daysAvailable;
}*/
string Person::getName()
{
	return _name;
}

void Person::setLegal(bool driver, bool _driver)
{
	_driver = driver;
}

/*void Person::setDate(int daysAvailable, int _daysAvailable)
{
_daysAvailable = daysAvailable;
}*/

void Person::setName(string name, string _name)
{
	_name = name;
}