#include "Mission.h"

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

void Mission::setStatus(int s)
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

int Mission::getStatus()
{
	return status;
}

int Mission::calcWeight()
{
	int weight = 0;
	if (type == 'E')
	{
		weight = significance + targetLocation + duration;
	}
	return weight;
}
