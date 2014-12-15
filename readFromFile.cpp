#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "boost\algorithm\string.hpp"
#include "boost\date_time\gregorian\gregorian.hpp"
#include "person.h"

using namespace std;

//const array of days available

vector<Person*> people;
vector<boost::gregorian::date> dates;

std::string trim(const std::string& str,
	const std::string& whitespace = " \t")
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

vector<boost::gregorian::date> parseDates(stringstream& iss)
{
	//make vector of empty dates
	//int  i = 1;
	string daysAvailable;
	getline(iss, daysAvailable, ';');
	boost::gregorian::date parseDays(string daysAvailable);
	boost::gregorian::date d = (boost::gregorian::from_simple_string(daysAvailable));
	vector<boost::gregorian::date> dates;
	//dates.resize(i);
	boost::gregorian::date d(boost::gregorian::from_simple_string(daysAvailable));
	//dates[i] = d;
	return dates;
}

vector<boost::gregorian::date> parseDays(string daysAvailable)
{
	vector<boost::gregorian::date> days;
	//string j;
	//date d = (from_simple_string(j));
	// FIXME
	//days.resize(2); 
	vector<string> strs;
	boost::split(strs, daysAvailable, boost::is_any_of(' '));
	//put strs into days?
	cout << strs[0];
	/*for(int i = 0; i < strs.size(); i++)
	{
		cout << strs[i];
		//j = strs[i];
		//days[i] = d;
	}*/
	return days;
}

bool parseDriver(stringstream& iss)
{
	string driver;
	getline(iss, driver, '.');
	driver = trim(driver);
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