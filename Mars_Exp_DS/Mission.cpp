#include "Mission.h"

Mission::Mission()
{
}

Mission::Mission(char t, int d, int id, int tloc, int dur, int sig)
{
	type = t; day = d; ID = id; targetLocation = tloc; duration = dur; significance = sig;
}

void Mission::setID(int id)
{
	ID = id;
}

void Mission::setDay(int d)
{
	day = d;
}

void Mission::setType(char t)
{
	type = t;
}

void Mission::setTargetLocation(int tloc)
{
	targetLocation = tloc;
}

void Mission::setDuration(int dur)
{
	duration = dur;
}

void Mission::setSignificance(int sig)
{
	significance = sig;
}

void Mission::setStatus(char s)
{
	status = s;
}

int Mission::getID()
{
	return ID;
}

int Mission::getDay()
{
	return day;
}

char Mission::getType()
{
	return type;
}

int Mission::getTargetLocation()
{
	return targetLocation;
}

int Mission::getDuration()
{
	return duration;
}

int Mission::getSignificance()
{
	return significance;
}

char Mission::getStatus()
{
	return status;
}

int Mission::getWeight()
{
	return weight;
}


int Mission::calcWeight()
{
	int weight = 0;
	int F=0; //Failure Factor
	int I = 0;
	if (getStatus() == 'F') //status (F: FAIL High Priority)
		F = 100;
	if (getStatus() == 'I')
		I = -100;
	const int avgspeed = 6; //average speed of a rover
	int Day = ceil(duration + ((targetLocation / avgspeed) / 25) * 2); 
	weight = Day + (F * 1.5) + significance +(I*1.5); 

	return weight;
}
