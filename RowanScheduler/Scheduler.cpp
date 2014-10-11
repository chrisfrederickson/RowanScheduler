#include "StdAfx.h"
#include "Scheduler.h"


Scheduler::Scheduler(void)
{
}

Scheduler::~Scheduler(void)
{
}

std::vector<Schedule> Scheduler::genSchedules(std::vector<Course> inCourses)
{
	return validateSchedules(genPossibleSchedules(inCourses));
}

std::vector<Schedule> Scheduler::genPossibleSchedules(std::vector<Course> inCourses)
{
	
	std::vector<Schedule> possibleSchedules;
	bool end = false;
	int x = 0;

	std::vector<int> position;
	for(int i = 0; i < inCourses.size(); i++)
		position.push_back(0);

	while(!end)
	{
		position[0]++;
		for(x = 0; x < inCourses.size(); x++)
		{
			if(position.at(x) == inCourses.at(x).getClasses().size())
			{
				if(x == inCourses.size()-1)
				{
					end = true;
				}
				else
				{
					position.at(x) = 0;
					position.at(x+1)++;
				}
			}
		}
		
		if(!end)
		{
			Schedule tempSchedule;
#ifdef DEBUG
			std::cout << "Added schedule: ";
#endif
			for(int i = 0; i < position.size(); i++)
			{
				tempSchedule.addClass(inCourses.at(i).getClasses().at(position.at(i)));
#ifdef DEBUG
				std::cout << inCourses.at(i).getClasses().at(position.at(i)).getCrn() << " ";
#endif
			}
#ifdef DEBUG
			std::cout << std::endl;
#endif
			possibleSchedules.push_back(tempSchedule);
		}
	}
	return possibleSchedules;
}

std::vector<Schedule> Scheduler::validateSchedules(std::vector<Schedule> inSchedules)
{
	std::vector<Schedule> validSchedules;

	//Iterate through all schedules
	for(int i = 0; i < inSchedules.size(); i++)
	{
		bool valid = true;
		std::vector<Meeting> allMeetings;
		auto classes = inSchedules.at(i).getClasses();
		//Iterate through all classes
		for(int x = 0; x < classes.size(); x++)
		{
			//Interate through all meetings
			for(int y = 0; y < classes.at(x).getMeetings().size(); y++)
			{
				//Compare them will all current meetings in schedule
				for(int z = 0; z < allMeetings.size(); z++)
				{
#ifdef DEBUG
					std::cout << allMeetings.at(z).time.day << " != " << classes.at(x).getMeetings().at(y).time.day << " || " 
						<< allMeetings.at(z).time.endTime << " < " << classes.at(x).getMeetings().at(y).time.startTime << " && "
						<< allMeetings.at(z).time.startTime << " < " << classes.at(x).getMeetings().at(y).time.endTime << std::endl;
#endif
					//If they conflict, do not add it to the valid schedules vector;
					/*
					if(!(allMeetings.at(z).time.day != classes.at(x).getMeetings().at(y).time.day || 
					     (allMeetings.at(z).time.endTime < classes.at(x).getMeetings().at(y).time.startTime && 
					     allMeetings.at(z).time.startTime < classes.at(x).getMeetings().at(y).time.endTime)))
						 */
					if(!(allMeetings.at(z).time.day != classes.at(x).getMeetings().at(y).time.day || 
					     ((allMeetings.at(z).time.startTime < classes.at(x).getMeetings().at(y).time.startTime && 
					     allMeetings.at(z).time.endTime < classes.at(x).getMeetings().at(y).time.startTime) ||
						 (allMeetings.at(z).time.endTime > classes.at(x).getMeetings().at(y).time.endTime && 
					     allMeetings.at(z).time.endTime > classes.at(x).getMeetings().at(y).time.startTime))))
					{
#ifdef DEBUG
						std::cout << "Conflicting schedule: " << std::endl;
						std::cout << "Day: " << allMeetings.at(z).time.day
								  << " StartTime: " << allMeetings.at(z).time.startTime
								  << " EndTime: " << allMeetings.at(z).time.endTime << std::endl;
						std::cout << "Day: " << classes.at(x).getMeetings().at(y).time.day
								  << " StartTime: " << classes.at(x).getMeetings().at(y).time.startTime
								  << " EndTime: " << classes.at(x).getMeetings().at(y).time.endTime << std::endl;
#endif
						valid = false;
						goto NextSchedule;
					}
				}
				allMeetings.push_back(classes.at(x).getMeetings().at(y));
			}
		}
		NextSchedule:
		//Add schedule to valid
		if(valid) validSchedules.push_back(inSchedules.at(i));
		else
		{
#ifdef DEBUG
			std::cout << "Invalid schedule: ";
			for(int k = 0; k < inSchedules.at(i).getClasses().size(); k ++)
			{
				std::cout << inSchedules.at(i).getClasses().at(k).getCrn() << " ";
			}
			std::cout << std::endl;
#endif
		}
	}
	return validSchedules;
}