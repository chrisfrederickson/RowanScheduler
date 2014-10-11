#pragma once
#include <vector>
#include "Class.h"

class Schedule
{
private:
	int score;
	std::vector<Class> classes;
public:
	Schedule(void);
	~Schedule(void);

	void setScore(int);
	void setClasses(std::vector<Class>);

	void addClass(Class);

	int getScore();
	std::vector<Class> getClasses();
};

