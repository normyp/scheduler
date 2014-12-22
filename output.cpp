#include <iostream>
#include "person.h"
#include "boost\date_time\gregorian\gregorian.hpp"
#include "output.h"

using namespace std;
using namespace boost;

void output(gregorian::date startDay, gregorian::date endDay, int numberOfPeople, vector<Person*> people, vector<gregorian::date> dates,bool personAvailable)
{
	gregorian::date_duration dd(1);
	int count;

	for (gregorian::date i = startDay; i < endDay; i = i + dd)
	{
		cout << "The people who can work on " << i << " are as follows: " << endl;
		count = 0;
		for (int j = 0; j < numberOfPeople; j++)
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
			if (j == numberOfPeople - 1 && count == 0)
			{
				cout << "No-one!" << endl;
			}
			personAvailable = false;
		}
		cout << endl;
	}
};