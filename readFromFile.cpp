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
			string day;
			day = strs[i];
			days.resize(j+1);
			gregorian::date d = (gregorian::from_simple_string(day));
			days[j++] = d;
		}
		
	}
	/*for (unsigned int i = 0; i < days.size(); i++)
	{
		cout << days[i] << endl;
	}*/
	return days;
}

vector<gregorian::date> parseDates(stringstream& iss)
{
	string daysAvailable;
	getline(iss, daysAvailable, ';');
	vector<gregorian::date> dates;
	dates = parseDays(daysAvailable);
	return dates;
}

gregorian::date earliestDay(vector<gregorian::date> dates)
{
	if (dates.size() == 0)
	{
		cerr << "No dates provided" << endl;
		exit(1);
	}
	gregorian::date first = dates[0];
	for (int i = 1; i < dates.size(); i++)
	{
		if (dates[i] < first)
		{
			first = dates[i];
		}
	}
	return first;
}

gregorian::date latestDay(vector<gregorian::date> dates)
{
	if (dates.size() == 0)
	{
		cerr << "No dates provided" << endl;
		exit(1);
	}
	gregorian::date last = dates[0];
	for (int i = 1; i < dates.size(); i++)
	{
		if (dates[i] > last)
		{
			last = dates[i];
		}
	}
	return last;
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
	bool personAvailable = false;
	vector<gregorian::date>allDates;
	gregorian::date startDay, endDay;

	//print out for each day list of people who are available
	//Find out which day is the earliest date in the file
	//Check through each day until the latest date in the file
	//On each day cout the current day and the people who have that date in their vector of dates

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
		bool driver = parseDriver(iss);
		vector<gregorian::date>dates = parseDates(iss);
		Person* p = new Person(name, driver, dates);
		people.resize(++numberOfPeople);
		people[numberOfPeople - 1] = p;
		int currentPos = allDates.size();
		allDates.resize(allDates.size() + dates.size());
		for (int i = 0; i < dates.size(); i++)
		{
			allDates[currentPos+i] = dates[i];
		}

		//checkForLastDay(dates);
	}

	startDay = earliestDay(allDates);
	endDay = latestDay(allDates);


	/*for (int i = 0; i < numberOfPeople; i++)
	{
		if (people[i]->isDriver())
		{
			cout << people[i]->getName() << " is a driver and can work on: " << endl;
		}
		else
		{
			cout << people[i]->getName() << " is a passenger and can work on: " << endl;
		}
		dates = people[i]->getDate();
		for (int j = 0; j < dates.size(); j++)
		{
			 cout << dates[j] << endl;
		}
	}*/

	gregorian::date_duration dd(1);
	int count;

	for(gregorian::date i = startDay; i < endDay; i = i + dd)
	{
		cout << "The people who can work on " << i << " are as follows: " << endl;
		count = 0;
		for(int j = 0; j < numberOfPeople; j++)
		{
			dates = people[j]->getDate();
			for (int k = 0; k < dates.size(); k++)
			{
				if (dates[k] == i)
				{
					personAvailable = true;
				}
			}
			if (personAvailable)
			{
				cout << people[j]->getName() << endl;
				count++;
			}
			if (j == numberOfPeople-1 && count == 0)
			{
				cout << "No-one!" << endl;
			}
			personAvailable = false;
		}
		cout << endl;
	}	


	inFile.close();

	cin.ignore(3);
	return 0;
}