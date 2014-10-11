#include "StdAfx.h"
#include "Schedule.h"


Schedule::Schedule(void)
{
	//score = 0;
	//std::cout << "Constructor called." << std::endl;
}

Schedule::~Schedule(void)
{
}

void Schedule::setScore(int inScore)
{
	score = inScore;
}

void Schedule::setClasses(std::vector<Class> inClasses)
{
	classes = inClasses;
}

void Schedule::addClass(Class inClass)
{
	classes.push_back(inClass);
}

int Schedule::getScore()
{
	return score;
}

std::vector<Class> Schedule::getClasses()
{
	return classes;
}