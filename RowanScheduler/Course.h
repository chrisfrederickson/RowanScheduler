#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Class.h"

class Course
{
	std::string subject;
	int id;
	std::vector<Class> classes;
public:
	Course();
	Course(std::string, int);
	~Course(void);

	std::string getSubject();
	int getId();
	void addClass(Class);
	void setClasses(std::vector<Class>);
	std::vector<Class> getClasses();
};

