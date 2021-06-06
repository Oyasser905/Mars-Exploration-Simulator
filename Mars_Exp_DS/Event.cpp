#include"Event.h"
#include"Mission.h"
#include"priorityQueue.h"


void Event::setDay(int day)
{
	eventDay = day;
}

void Event::setID(int id)
{
	missionID = id;
}

int Event::getDay() const
{
	return eventDay;
}

int Event::getID() const
{
	return missionID;
}
