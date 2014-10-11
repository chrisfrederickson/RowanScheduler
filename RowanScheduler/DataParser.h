#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Course.h"
#include "Class.h"

class DataParser
{
	std::string fileLocation;
	std::ifstream data;
public:
	DataParser(std::string);
	~DataParser(void);

	bool isGood();
	Course courseFromSubjId(std::string, int);
	bool isValidCourse(Course);

private:
	std::vector<Meeting> parseClassMeetings(std::string);
	Meeting generateMeeting(std::string building, std::string room, char day, int startTime, int endTime);
};

