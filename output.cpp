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

	/*for (gregorian::date i = startDay; i < endDay; i = i + dd)
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
	}*/

	//Assign people to dates
	//If someone works has been assigned to two more dates than everyone else then stop assigning them on their available days until it's even again.
	//Each person needs a 'how many times used value' to compare across all
	//Every day needs a driver and two passengers or it's a no-go
	//need a timesmore than everyone else
	int timesUsed;
	int numberOfDrivers;
	int count2;
	bool check;
	string peopleOfDay[3];
	string extraPeople[16];

	//vector of people for that specific day
	//then I can use the vector of people to find the drivers and get rid of one of them for that day
	//next time it happens this driver needs to replace the next driver
	//

	for (gregorian::date i = startDay; i < endDay; i = i + dd)
	{
		cout << "The people working on " << i << " are as follows: " << endl;
		count = 0;
		count2 = 0;
		numberOfDrivers = 0;
		for (int j = 0; j < numberOfPeople; j++)
		{
			int timesUsedCount = 0;
			dates = people[j]->getDate();

			for (int k = 0; k < dates.size(); k++)
			{
				if (dates[k] == i)
				{
					personAvailable = true;
				}
			}
			
			if (personAvailable && count < 3)
			{
				peopleOfDay[count] = people[j]->getName();
				count++;
			}
			/*else if (personAvailable && count >= 3)
			{
				extraPeople[count2] = people[j]->getName();
				count2++;
			}*/
			personAvailable = false;
		}
		if (count < 3)
		{
			cout << "Not enough people available" << endl;
		}
		else if (count >= 3)
		{
			for (int l = 0; l < 3; l++)
			{
				cout << peopleOfDay[l] << endl;
			}
		}
		/*if (count2 > 0)
		{
			if (count2 > 3)
			{
				for (int y = 0; y < 3; y++)
				{
					peopleOfDay[y] = extraPeople[y];
				}
			}
			else{
				for (int y = 0; y < count2; y++)
				{
					peopleOfDay[y] = extraPeople[y];
				}
			}
			count = count2;
		}*/
		else
		{
			count = 0;
		}
		cout << endl;
	}
};