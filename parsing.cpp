#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include "person.h"
#include "boost\date_time\gregorian\gregorian.hpp"
#include "boost\algorithm\string.hpp"
#include "parsing.h"

using namespace std;
using namespace boost;

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
	for (unsigned int i = 0; i < strs.size(); i++)
	{
		if (strs[i] != "")
		{
			string day;
			day = strs[i];
			days.resize(j + 1);
			gregorian::date d = (gregorian::from_simple_string(day));
			days[j++] = d;
		}

	}
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

bool parseDriver(stringstream& iss)
{
	string driver;
	getline(iss, driver, '.');
	driver = trimString(driver);
	return driver.compare("driver") == 0;
}

void parsing(string inputFile, int* numberOfPeople, vector<Person*>* people, vector<gregorian::date>*allDates)
{
	ifstream inFile;
	inFile.open(inputFile);

	if (inFile.fail())
	{
		cerr << "Error does not work";
		exit(1);
	}

	string line;
	string name;

	while (getline(inFile, line))
	{
		stringstream iss(line);
		getline(iss, name, ':');
		bool driver = parseDriver(iss);
		vector<gregorian::date>dates = parseDates(iss);
		Person* p = new Person(name, driver, dates);
		people->resize(++*numberOfPeople);
		(*people)[*numberOfPeople - 1] = p;
		int currentPos = allDates->size();
		allDates->resize(allDates->size() + dates.size());
		for (int i = 0; i < dates.size(); i++)
		{
			(*allDates)[currentPos + i] = dates[i];
		}
	}

	inFile.close();
};