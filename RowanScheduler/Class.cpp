#include "StdAfx.h"
#include "Class.h"


Class::Class(int inCrn, 
			 std::string inSubject, 
			 int inId, 
			 int inSection,
			 std::string inName, 
			 std::string inInstuctor, 
			 int inMax, 
			 int inEnrolled, 
			 int inRoomCap)
{
	crn = 0;
	subject = "";
	id = 0;
	section = 0;
	name = "";
	instuctor = "";
	max = 0;
	enrolled = 0;
	roomCap = 0;

	setCrn(inCrn);
	setSubject(inSubject);
	setId(inId);
	setSection(inSection);
	setName(inName);
	setInstuctor(inInstuctor);
	setMax(inMax);
	setEnrolled(inEnrolled);
	setRoomCap(inRoomCap);
}

Class::~Class(void)
{
}

int Class::getCrn()
{
	return crn;
}

std::string Class::getSubject()
{
	return subject;
}

int Class::getId()
{
	return id;
}

int Class::getSection()
{
	return section;
}

std::string Class::getName()
{
	return name;
}

std::string Class::getInstructor()
{
	return instuctor;
}

int Class::getMax()
{
	return max;
}

int Class::getEnrolled()
{
	return enrolled;
}

int Class::getRoomCap()
{
	return roomCap;
}

std::vector<Meeting> Class::getMeetings()
{
	return meetings;
}

void Class::setCrn(int inCrn)
{
	if (inCrn >= 40000 && inCrn < 50000)
		crn = inCrn;
	else
		std::cout << "Invalid crn" << std::endl;
}

void Class::setSubject(std::string inSubject)
{
	//TODO Add validation to subject
	subject = inSubject;
}

void Class::setId(int inId)
{
	if (inId > 0 && inId < 10000)
		id = inId;
	else
		std::cout << "Invalid id." << std::endl;
}

void Class::setSection(int inSection)
{
	if (inSection > 0)
		section = inSection;
	else
		std::cout << "Invalid section." << std::endl;
}

void Class::setName(std::string inName)
{
	name = inName;
}

void Class::setInstuctor(std::string inInstuctor)
{
	instuctor = inInstuctor;
}

void Class::setMax(int inMax)
{
	max = inMax;
}

void Class::setEnrolled(int inEnrolled)
{
	enrolled = inEnrolled;
}

void Class::setRoomCap(int inRoomCap)
{
	roomCap = inRoomCap;
}

void Class::setMeetings(std::vector<Meeting> inMeetings)
{
	meetings = inMeetings;
}

void Class::addMeeting(char inDay, 
					   int inStartTime, 
					   int inEndTime, 
					   std::string inBuilding, 
					   std::string inRoom)
{
	Meeting newMeeting = {{inBuilding, inRoom}, {inDay, inStartTime, inEndTime}};
	meetings.push_back(newMeeting);
}