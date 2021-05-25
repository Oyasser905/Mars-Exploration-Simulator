#include"Rover.h"

void Rover::setType(char t)
{
	R_type = t;
}

void Rover::setSpeed(int s)
{
	speed = s;
}

void Rover::setCheckupDuration(int ch)
{
	checkupDuration = ch;
}

char Rover::getType()
{
	return R_type;
}

int Rover::getSpeed()
{
	return speed;
}

int Rover::getCheckupDuration()
{
	return checkupDuration;
}
