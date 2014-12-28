#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "boost\date_time\gregorian\gregorian.hpp"
#include "boost\algorithm\string.hpp"

#include "person.h"
#include "parsing.h"
#include "output.h"

using namespace std;
using namespace boost;

//const array of days available

vector<Person*> people;
vector<gregorian::date> dates;

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

int main()
{
	int numberOfPeople = 0;
	int currentPerson = 0;
	bool b = false;
	bool personAvailable = false;
	vector<gregorian::date>allDates;
	gregorian::date startDay, endDay;

	parsing("people.txt", &numberOfPeople, &people, &allDates);
	
	startDay = earliestDay(allDates);
	endDay = latestDay(allDates);

	output(startDay, endDay, numberOfPeople, people, dates, personAvailable);

	cin.ignore(3);
	return 0;
}