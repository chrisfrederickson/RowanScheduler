#pragma once
#include <iostream>
#include <vector>
#include "Class.h"
#include "Course.h"
#include "Schedule.h"
//#include "Ranker.h"

//std::vector<Schedule> scheduleTraverse(std::vector<Course>, int);

class Scheduler
{
public:
	Scheduler(void);
	~Scheduler(void);
	std::vector<Schedule> genSchedules(std::vector<Course>);
private:
	std::vector<Schedule> genPossibleSchedules(std::vector<Course>);
	std::vector<Schedule> validateSchedules(std::vector<Schedule>);
};