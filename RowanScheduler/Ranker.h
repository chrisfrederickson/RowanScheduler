#pragma once
#include <vector>
#include <algorithm>
#include "Schedule.h"

typedef struct Preferance {
	int prefType;
	int priority;
} Preferance;

enum PrefType {noMon, noTue, noWed, noThur, noFri, noSat, noMorning, noAfternoon, noNight};
enum Priority {Mandatory = 1000, Critical = 50, Important = 20, Wanted = 10, Nice = 5};

bool sortOrder(Schedule&, Schedule&);

class Ranker
{
	std::vector<Preferance> preferances;
public:
	Ranker(void);
	~Ranker(void);

	void addPref(int, int);
	void clearPref();
	bool isValidPref(int, int);

	void scoreSchedule(Schedule&);
	int scoreMeeting(Meeting);

	void scoreSchedules(std::vector<Schedule>&);
	void scoreSortSchedules(std::vector<Schedule>&);
};