#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "person.h"
#include <vector>
#include "boost\date_time\gregorian\gregorian.hpp"
#include "boost\algorithm\string.hpp"

using namespace std;
using namespace boost;

//const array of days available

vector<Person*> people;
vector<gregorian::date> dates;

string trimString(const string& str,
	const string& whitespace = " \t")
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

vector<gregorian::date> parseDays(string daysAvailable)
{
	vector<gregorian::date> days;
	vector<string> strs;
	int j = 0;
	boost::split(strs, daysAvailable, boost::is_any_of(" "));
	for(unsigned int i = 0; i < strs.size(); i++)
	{
		if (strs[i] != "")
		{
			cout << "{" << strs[i] << "}" << endl;
			string day;
			day = strs[i];
			cout << day << endl;
			days.resize(j+1);
			gregorian::date d = (gregorian::from_simple_string(day));
			days[j++] = d;
		}
		
	}
	for (unsigned int i = 0; i < days.size(); i++)
	{
		cout << days[i] << endl;
	}
	return days;
}

vector<gregorian::date> parseDates(stringstream& iss)
{
	//make vector of empty dates
	//int  i = 1;
	string daysAvailable;
	getline(iss, daysAvailable, ';');
	vector<gregorian::date> dates;
	dates = parseDays(daysAvailable);
	/*string daysAvailable;
	getline(iss, daysAvailable, ';');
	dates.resize(i);
	date d(from_simple_string(daysAvailable));
	dates[i] = d;*/
	return dates;
}


bool parseDriver(stringstream& iss)
{
	string driver;
	getline(iss, driver, '.');
	driver = trimString(driver);
	return driver.compare("driver") == 0;
}

int main()
{
	ifstream inFile;
	inFile.open("people.txt");

	if (inFile.fail())
	{
		cerr << "Error does not work";
		exit(1);
	}

	string line;
	string name;
	int numberOfPeople = 0;
	int currentPerson = 0;
	bool b = false;

	//learn boost::date
	//print out days available for each person
	//print out for each day list of people who are available

	/*
	for(int i = 0; i < lastDay; i++)
	{
	PrintDate(i);
	Below is function PrintAvailablePeople();
	for(int j = 0; j < numberOfPeople; j++)
	{
	if(people[j]->isAvailable())
	{
	cout << people[j]->getName() << " is available." <<  endl;
	}
	else
	{
	cout << people[j]->getName() << " is not available." << endl;
	}
	}
	Below is function PrintDrivers();
	for (int y = 0; y < numberOfPeople; y++)
	{
	if (people[y]->isDriver())
	{
	cout << people[y]->getName() << " can drive too." << endl;
	}
	else
	{
	cout << people[y]->getName() << " can not drive." << endl;
	}
	}
	PrintNumberOfDrivers();
	}
	*/

	while (getline(inFile, line))
	{
		stringstream iss(line);
		getline(iss, name, ':');
		Person* p = new Person(name, parseDriver(iss));
		people.resize(++numberOfPeople);
		people[numberOfPeople - 1] = p;
		dates = parseDates(iss);
		//break if you don't start with name
		//cout << name << daysAvailable << driver << endl;
	}
	//put algorithm in own function

	for (int i = 0; i < numberOfPeople; i++)
	{
		if (people[i]->isDriver())
		{
			cout << people[i]->getName() << " is a driver." << endl;
		}
		else
		{
			cout << people[i]->getName() << " is not a driver." << endl;
		}
	}


	/*while (getline(inFile, line))
	{
	currentPerson++;
	stringstream iss(line);
	getline(iss, name, ':');
	getline(iss, daysAvailable, ';');
	getline(iss, driver, '.');
	people.setName();
	}*/

	inFile.close();

	cin.ignore(3);
	return 0;
}