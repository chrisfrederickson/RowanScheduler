#include "StdAfx.h"
#include "Ranker.h"


Ranker::Ranker(void)
{
}

Ranker::~Ranker(void)
{
}

void Ranker::addPref(int inPrefType, int inPriority)
{
	bool flag = false;
	for(int i = 0; i < preferances.size(); i++)
	{
		if(preferances.at(i).prefType = inPrefType)
			flag = true;
	}
	if(!flag)
	{
		Preferance test = {inPrefType, inPriority};
		preferances.push_back(test);
	}
}

void Ranker::clearPref()
{
	preferances.clear();
}

bool Ranker::isValidPref(int inPrefType, int inPriority)
{
	return (inPrefType >= 0 && inPrefType <= 8) && (inPriority > 0);
}

void Ranker::scoreSchedule(Schedule& inSchedule)
{
	int score = 0;
	auto classes = inSchedule.getClasses();
	for(int i = 0; i < classes.size(); i++)
	{
		for(int x = 0; x < classes.at(i).getMeetings().size(); x++)
		{
			score += scoreMeeting(classes.at(i).getMeetings().at(x));
		}
	}
	inSchedule.setScore(score);
}

int Ranker::scoreMeeting(Meeting inMeeting)
{
	int score = 0;
	for(int i = 0; i < preferances.size(); i++)
	{
		switch(preferances.at(i).prefType)
		{
		case noMon:
			if (inMeeting.time.day == 'M') score += preferances.at(i).priority;
			break;
		case noTue:
			if (inMeeting.time.day == 'T') score += preferances.at(i).priority;
			break;
		case noWed:
			if (inMeeting.time.day == 'W') score += preferances.at(i).priority;
			break;
		case noThur:
			if (inMeeting.time.day == 'R') score += preferances.at(i).priority;
			break;
		case noFri:
			if (inMeeting.time.day == 'F') score += preferances.at(i).priority;
			break;
		case noSat:
			if (inMeeting.time.day == 'S') score += preferances.at(i).priority;
			break;
		case noMorning:
			if (inMeeting.time.startTime <= 1200) score += preferances.at(i).priority;
			break;
		case noAfternoon:
			if (inMeeting.time.startTime <= 1200 && inMeeting.time.startTime <= 1600) score += preferances.at(i).priority;
			break;
		case noNight:
			if (inMeeting.time.startTime <= 1800 && inMeeting.time.startTime <= 2400) score += preferances.at(i).priority;
			break;
		}
	}
	return score;
}

void Ranker::scoreSchedules(std::vector<Schedule>& inSchedules)
{
	for(int i = 0; i < inSchedules.size(); i++)
	{
		scoreSchedule(inSchedules.at(i));
	}
}

void Ranker::scoreSortSchedules(std::vector<Schedule>& inSchedules)
{
	scoreSchedules(inSchedules);
	std::sort(inSchedules.begin(), inSchedules.end(), sortOrder);
}

bool sortOrder(Schedule& s1, Schedule& s2)
{
	return s1.getScore() < s2.getScore();
}