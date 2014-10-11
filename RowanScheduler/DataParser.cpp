#include "StdAfx.h"
#include "DataParser.h"


DataParser::DataParser(std::string inFileLocation)
{
	fileLocation = inFileLocation;
}

DataParser::~DataParser(void)
{
}

bool DataParser::isGood()
{
	data.open(fileLocation, std::ifstream::in);
	if (data.is_open()) 
		data.close();
	return true;
	data.close();
	return false;

}

Course DataParser::courseFromSubjId(std::string subj, int id)
{
	//Init new course object
	Course newCourse (subj, id);

	//Open file
	data.open(fileLocation, std::ifstream::in);
	//std::cout << "File opened." << std::endl;

	std::string temp;
	std::string cell;
	int loc;

	//Parse row
	while(!data.eof())
		//for(int i = 0; i < 5; i++)
	{
		std::stringstream ss;
#ifdef DEBUG
		std::cout << "****************** Row read. **************" << std::endl;
#endif
		std::getline(data, temp);
#ifdef DEBUG
		std::cout << "Full row: " << temp << std::endl;
#endif
		ss << temp;
		loc = 0;

		int tempCrn;
		std::string tempSubject;
		int tempId;
		int tempSection;
		int tempCredits;
		std::string tempName;
		std::string tempInstructor;
		std::vector<Meeting> tempMeetings;
		std::string tempCampus;
		int tempMax;
		int tempEnrolled;
		int tempRoomCap = 0;

		//Parse colum
		while(!ss.eof())
		{


			std::getline(ss, cell, ',');
#ifdef DEBUG
			std::cout << "Colum read| ";
			std::cout << "Cell: " << cell << " Loc: " << loc << std::endl;
#endif
			switch(loc)
			{
			case 0: //Crn
				{
					tempCrn = std::stoi(cell);
					break;
				}
			case 1: //Subj
				{
					tempSubject = cell;
					if (tempSubject != subj)
					{
						goto NextLine;
					}
					break;
				}
			case 2: //Course
				{
					tempId = std::stoi(cell);
					if (tempId != id)
					{
						goto NextLine;
					}
					break;
				}
			case 3: //Section
				{
					tempSection = std::stoi(cell);
					break;
				}
			case 4: //Part of Term UNUSED
				break;
			case 5: //Session UNUSED
				break;
			case 6: //Title
				{
					tempName = cell;
					break;
				}
			case 7: //Instuctor
				{
					tempInstructor = cell;
					break;
				}
			case 8: //Meetings
				{
					tempMeetings = parseClassMeetings(cell);
					break;
				}
			case 9: //Campus
				{
					tempCampus = cell;
					break;
				}
			case 10: //Additional info UNUSED
				break;
			case 11: //Credits
				{
					tempCredits = std::stoi(cell);
					break;
				}
			case 12: //Max enrolled
				{
					tempMax = std::stoi(cell);
					break;
				}
			case 13: //Max reserved UNUSED
				break;
			case 14: //Left reserved UNUSED
				break;
			case 15: //Enrolled
				{
					tempEnrolled = std::stoi(cell);\
						break;
				}
			case 16: //Avaliable UNUSED
				break;
			case 17: //Room cap
				{
					if(cell.length() == 0)
						break;
					tempRoomCap = std::stoi(cell);
					break;
				}
			}
			loc++;
		}

NextLine:
		if(tempSubject == subj && tempId == id)
		{
#ifdef DEBUG
			std::cout << "Crn: " << tempCrn << std::endl
				<< "Subject: " << tempSubject << std::endl
				<< "Id: " << tempId << std::endl
				<< "Section: " << tempSection << std::endl
				<< "Name: " << tempName << std::endl
				<< "Instructor: " << tempInstructor << std::endl
				<< "Enrolled: " << tempEnrolled << std::endl
				<< "RoomCap: " << tempRoomCap << std::endl;
#endif
			Class newClass (tempCrn,
				tempSubject,
				tempId,
				tempSection,
				tempName,
				tempInstructor,
				tempMax,
				tempEnrolled,
				tempRoomCap);
			newClass.setMeetings(tempMeetings);
			newCourse.addClass(newClass);
		}

	}
	data.close();
	return newCourse;
}

std::vector<Meeting> DataParser::parseClassMeetings(std::string inClassMeetings)
{
	std::stringstream meet;
	meet << inClassMeetings;

	std::vector<Meeting> tempMeetings;

	int loc2 = 0;
	std::string days = "";
	int startTime = 0;
	int endTime = 0;
	std::string building = "";
	std::string room = "";

	while(!meet.eof())
	{
		std::string cell2;
		meet >> cell2;
#ifdef DEBUG
std::cout << "Loc2: " << loc2 << " Meet Cell: " << cell2 << std::endl;
#endif
		switch(loc2)
		{
		case 0:
			{
				days = cell2;
				break;
			}
		case 1:
			{
				startTime = std::stoi(cell2);
				break;
			}
		case 2:
			{
				endTime = std::stoi(cell2);
				break;
			}
		case 3:
			{
				if(cell2 == "(Class)")
				{
					loc2 = -1;
					char day;

					for(int i = 0; i < days.length(); i++)
					{
						day = days.at(i);
						Meeting tempMeeting = {{building, room}, {day, startTime, endTime}};
						tempMeetings.push_back(tempMeeting);
					}
				}
				else
				{
					building = cell2;
				}
				break;
			}
		case 4:
			{
				room = cell2;
				break;
			}
		case 5:
			{
				if(cell2 == "(Class)")
				{

					loc2 = -1;
					char day;

					for(int i = 0; i < days.length(); i++)
					{
						day = days.at(i);
						Meeting tempMeeting = {{building, room}, {day, startTime, endTime}};
						tempMeetings.push_back(tempMeeting);
					}
				}
				else
				{
					std::cout << "Invalid Meeting" << std::endl;
				}
				break;
			}
		}
		loc2++;
	}
#ifdef DEBUG
	for(int i = 0; i < tempMeetings.size(); i++)
	{
		std::cout << tempMeetings.at(i).time.day << " "
			<< tempMeetings.at(i).time.startTime << " "
			<< tempMeetings.at(i).time.endTime << " "
			<< tempMeetings.at(i).location.building << " "
			<< tempMeetings.at(i).location.room << std::endl;
	}
#endif
	return tempMeetings;
}

bool DataParser::isValidCourse(Course inCourse)
{
	return inCourse.getClasses().size() > 0;
}