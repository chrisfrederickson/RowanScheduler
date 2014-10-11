#include "StdAfx.h"
#include "Course.h"

Course::Course()
{
}

Course::Course(std::string inSubject, int inId)
{
	subject = inSubject;
	id = inId;
}

Course::~Course(void)
{
}

std::string Course::getSubject()
{
	return subject;
}

int Course::getId()
{
	return id;
}

void Course::addClass(Class newClass)
{
	classes.push_back(newClass);
	
	/*
	if (newClass.getSubject() == getSubject() && newClass.getId() == getId())
	{
		classes.push_back(newClass);
	}
	else
	{
		std::cout << "Invalid class." << std::endl;
	}
	*/
}

std::vector<Class> Course::getClasses()
{
	return classes;
}

void Course::setClasses(std::vector<Class> inClasses)
{
	classes = inClasses;
}