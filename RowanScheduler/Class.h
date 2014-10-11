#pragma once
#include <string>
#include <vector>
#include <iostream>

typedef struct Location {
	std::string building;
	std::string room;
} Location;

typedef struct Time {
	char day;
	int startTime;
	int endTime;
} Time;

typedef struct Meeting {
	Location location;
	Time time;
} Meeting;

class Class
{
	int crn;
	std::string subject;
	int id;
	int section;
	std::string name;
	std::string instuctor;
	std::vector<Meeting> meetings;
	int max;
	int enrolled;
	int roomCap;
public:
	Class(int crn, 
		  std::string subject, 
		  int id, 
		  int section,
		  std::string name, 
		  std::string instuctor, 
		  int max, 
		  int enrolled, 
		  int roomCap);
	~Class(void);

	int getCrn();
	std::string getSubject();
	int getId();
	int getSection();
	std::string getName();
	std::string getInstructor();
	int getMax();
	int getEnrolled();
	int getRoomCap();
	std::vector<Meeting> getMeetings();

	void setCrn(int crn);
	void setSubject(std::string subject);
	void setId(int id);
	void setSection(int section);
	void setName(std::string name);
	void setInstuctor(std::string instuctor);
	void setMax(int max);
	void setEnrolled(int enrolled);
	void setRoomCap(int roomCap);
	void setMeetings(std::vector<Meeting>);

	void addMeeting(char day, 
					int startTime, 
					int endTime, 
					std::string building, 
					std::string room);
	

	
};