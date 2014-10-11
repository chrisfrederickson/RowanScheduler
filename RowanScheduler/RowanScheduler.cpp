// RowanScheduler.cpp : Defines the entry point for the console application.
//
//Note: Raw data file must be .csv, have no title line, and have no invalid course ids.
//Replace \n with NONE
//Replace \r\n with \n

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>

#define RAW_DATA_LOCATION "H:\\RowanScheduler\\classes.csv"

#include "Class.h"
#include "Course.h"
#include "DataParser.h"
#include "Scheduler.h"
#include "Schedule.h"
#include "Ranker.h"

//#define DEBUG
#define IGNORE_MAX true
#define IGNORE_ROOM_CAP false

#define STATE_INSTRUCT 1
#define STATE_CLASSES 2
#define STATE_PREFERANCES 3
#define STATE_CAL 4
#define STATE_HELP 0

using namespace std;

void commandParser(int state);
void printTitle();
void printInstruct();
void printClassInstruct();
void printPrefInstruct();
void printHelp();
void clearConsole();
void printSchedule();
void prompt();
void printSchedule(Schedule);
void pause();

int _tmain(int argc, _TCHAR* argv[])
{
	string command;
	vector<Course> courses;

	printTitle();
	printInstruct();

	//Main screen
	command = "";
	while(command != "next")
	{
		prompt();
		getline(cin, command);
	}

	DataParser dp (RAW_DATA_LOCATION);

	printTitle();
	printClassInstruct();

	//Get courses
	command = "";
	while(command != "next")
	{
		prompt();
		getline(cin, command);

		string subj;
		int id;

		if(command != "next")
		{
			stringstream ssCom;
			ssCom << command;
			ssCom >> subj >> id;

			Course tempCourse = dp.courseFromSubjId(subj, id);

			if(dp.isValidCourse(tempCourse)) courses.push_back(tempCourse);
			else cout << "Invalid course." << endl;
		}
	}

	Scheduler s1;
	vector<Schedule> schedules = s1.genSchedules(courses);

	Ranker r1;

	printTitle();
	printPrefInstruct();

	command = "";
	while(command != "next")
	{
		prompt();
		getline(cin, command);

		int pref;
		int priority;

		if(command != "next")
		{
			stringstream ssCom;
			ssCom << command;
			ssCom >> pref >> priority;

			if(r1.isValidPref(pref, priority)) r1.addPref(pref, priority);
			else cout << "Invalid Preferance" << endl;
		}
	}

	r1.scoreSortSchedules(schedules);

	printTitle();

	for(int z = 0; z < schedules.size(); z++)
	{
		cout << "Schedule Option " << z << ", Score " << schedules.at(z).getScore() << ":" << endl;
		for(int c = 0; c < schedules.at(z).getClasses().size(); c++)
		{
			cout << "\t" << schedules.at(z).getClasses().at(c).getCrn()
				 << " " << schedules.at(z).getClasses().at(c).getSubject()
				 << " " << schedules.at(z).getClasses().at(c).getId() << endl;
			for(int v = 0; v < schedules.at(z).getClasses().at(c).getMeetings().size(); v++)
			{
				cout << "\t\t" << schedules.at(z).getClasses().at(c).getMeetings().at(v).time.day
					 << " " << schedules.at(z).getClasses().at(c).getMeetings().at(v).time.startTime
					 << " " << schedules.at(z).getClasses().at(c).getMeetings().at(v).time.endTime << endl;
			}
		}

		command = "";
		while(command != "next")
		{
			cout << "Type \"next\" to view next schedule." << endl;
			cin >> command;
		}
		
	}

	////////////////////////////////////////////////////////
	//Main Test Stuff
	////////////////////////////////////////////////////////

	/*
	
	DataParser dp (RAW_DATA_LOCATION);
	Course t1 = dp.courseFromSubjId("ART", 2300);
	Course t2 = dp.courseFromSubjId("ACC", 3210);
	courses.push_back(t1);
	courses.push_back(t2);
	
	//printTitle();
	//printPrefInstruct();

	Scheduler s1;
	vector<Schedule> schedules = s1.genSchedules(courses);
	
	Ranker r1;
	r1.addPref(0, 100);
	r1.addPref(1, 200);
	r1.addPref(2, 200);
	r1.addPref(6, 1000);
	r1.addPref(7, 50);

	//r1.scoreSchedule(schedules.at(0));

	//schedules.at(0).setScore(999);
	//cout << schedules.at(0).getScore() << endl;

	r1.scoreSortSchedules(schedules);

	for(int i = 0; i < schedules.size(); i++)
	{
		cout << "Classes: ";
		for(int x = 0; x < schedules.at(i).getClasses().size(); x++)
		{
			cout << schedules.at(i).getClasses().at(x).getCrn() << " ";
		}
		cout << "Score: " << schedules.at(i).getScore() << endl;
	}
	*/

	////////////////////////////////////////////////////////
	//Old Test Stuff
	////////////////////////////////////////////////////////

	/*
	DataParser dp (RAW_DATA_LOCATION);
	if(dp.isGood()) cout << "Yallr fine." << endl;
	c1 = dp.courseFromSubjId("ART", 2300);
	classes = c1.getClasses();

	for (int i = 0; i < classes.size(); i++)
	{
		cout << classes.at(i).getCrn() << " "
			 << classes.at(i).getSubject() << " "
			 << classes.at(i).getId() << " "
			 << classes.at(i).getSection() << endl;

			vector<Meeting> tempM = classes.at(i).getMeetings();
			for(int i = 0; i < tempM.size(); i++)
			{
				cout << tempM.at(i).time.day << " "
					 << tempM.at(i).time.startTime << " "
					 << tempM.at(i).time.endTime << " "
					 << tempM.at(i).location.building << " "
					 << tempM.at(i).location.room << endl;
			}
	}
	*/

	/*
	int state;
	while(true)
	{
		//TODO Command parser before everything to detect state change.
		switch(state)
		{
		case STATE_INSTRUCT:
			{
				clearConsole();
				printTitle();
				printInstruct();
				commandParser(state);
				break;
			}
		case STATE_PREFERANCES:
			{
				clearConsole();
				printTitle();
			}
		}
	}
	*/

	pause();
	return 0;
}

void printTitle()
{
	cout  << '\u00C9' << string(78, '\u00CD') << '\u00BB';
	cout << '\u00BA'
		 << setw(30) << "Rowan Class Scheduler" 
		 << setw(49) << right << '\u00BA';
	cout  << '\u00C8' << string(78, '\u00CD') << '\u00BC' << endl;
}

void printInstruct()
{
	cout << "This is the Rowan Automated Class Scheduler. "
		 << "Enter your classes and preferance using the console and your ideal schedule will be automatically generated. Follow the instuctions on screen. Type help at any time for assistance." << endl << endl;
	cout << "Type \"next\" to continue." << endl;
}

void printClassInstruct()
{
	cout << "Enter classes in the format \"SUBJ (all caps) Id\"." << endl;
	cout << "Type \"next\" to pick preferances." << endl;
}

void printPrefInstruct()
{
	cout << "Enter preferances in the format \"PreferanceType (int from below list) Priority (int, higher = higher prioority)" << endl;
	cout << "PreferanceTypes" << endl
		 << "\u00FE 0 No Class Mondays" << endl
		 << "\u00FE 1 No Class Tuesdays" << endl
		 << "\u00FE 2 No Class Wednesdays" << endl
		 << "\u00FE 3 No Class Thurdsdays" << endl
		 << "\u00FE 4 No Class Fridays" << endl
		 << "\u00FE 5 No Class Saturdays" << endl
		 << "\u00FE 6 No Class Mornings" << endl
		 << "\u00FE 7 No Class Afternoons" << endl
		 << "\u00FE 8 No Class Nights" << endl;
	cout << "Type \"next\" to generate schedule." << endl;
}

void printHelp()
{
	cout << "Commands" << endl
		 << "\u00FE Type \"next\" at any time to continue to the next section." << endl
		 << "\u00FE Type \"back\" at any time to go back to the last screen." << endl
		 << "\u00FE Type \"help\" at any time to return to this help screen." << endl
		 << "\u00FE Type \"exit\" at any time to exit the program." << endl;
}

void prompt()
{
	cout << ">> ";
}

void clearConsole()
{
	cout << string(100, '\n');
}

void printSchedule(Schedule inSchedule)
{
	string cal[40][6];
	for(int i = 0; i < inSchedule.getClasses().size(); i++)
	{
		for(int x = 0; x < inSchedule.getClasses().at(i).getMeetings().size(); x++)
		{
			auto meeting = inSchedule.getClasses().at(i).getMeetings().at(x);
			switch(meeting.time.day)
			{
			case 'M':
				cal[(meeting.time.startTime - 800 / 15)][0] = string(10, '\u00C4');
				cal[(meeting.time.startTime - 800 / 15)+1][0] = inSchedule.getClasses().at(i).getSubject() + " " + to_string(static_cast<long long>(inSchedule.getClasses().at(i).getId()));
				cal[(meeting.time.endTime - 800 / 15)][0] = string(10, '\u00C4');
				break;
			case 'T':
				cal[(meeting.time.startTime - 800 / 15)][1] = string(10, '\u00C4');
				cal[(meeting.time.startTime - 800 / 15)+1][1] = inSchedule.getClasses().at(i).getSubject() + " " + to_string(static_cast<long long>(inSchedule.getClasses().at(i).getId()));
				cal[(meeting.time.endTime - 800 / 15)][1] = string(10, '\u00C4');
				break;
			case 'W':
				cal[(meeting.time.startTime - 800 / 15)][2] = string(10, '\u00C4');
				cal[(meeting.time.startTime - 800 / 15)+1][2] = inSchedule.getClasses().at(i).getSubject() + " " + to_string(static_cast<long long>(inSchedule.getClasses().at(i).getId()));
				cal[(meeting.time.endTime - 800 / 15)][2] = string(10, '\u00C4');
				break;
			case 'R':
				cal[(meeting.time.startTime - 800 / 15)][3] = string(10, '\u00C4');
				cal[(meeting.time.startTime - 800 / 15)+1][3] = inSchedule.getClasses().at(i).getSubject() + " " + to_string(static_cast<long long>(inSchedule.getClasses().at(i).getId()));
				cal[(meeting.time.endTime - 800 / 15)][3] = string(10, '\u00C4');
				break;
			case 'F':
				cal[(meeting.time.startTime - 800 / 15)][4] = string(10, '\u00C4');
				cal[(meeting.time.startTime - 800 / 15)+1][4] = inSchedule.getClasses().at(i).getSubject() + " " + to_string(static_cast<long long>(inSchedule.getClasses().at(i).getId()));
				cal[(meeting.time.endTime - 800 / 15)][4] = string(10, '\u00C4');
				break;
			case 'S':
				cal[(meeting.time.startTime - 800 / 15)][5] = string(10, '\u00C4');
				cal[(meeting.time.startTime - 800 / 15)+1][5] = inSchedule.getClasses().at(i).getSubject() + " " + to_string(static_cast<long long>(inSchedule.getClasses().at(i).getId()));
				cal[(meeting.time.endTime - 800 / 15)][5] = string(10, '\u00C4');
				break;
			}
		}
	}


	cout << '\u00C9' << string(78, '\u00CD') << '\u00BB';
}

void pause()
{
	int iWait;
	cout << endl << "Enter any character to exit." << endl;
	cin >> iWait;
}