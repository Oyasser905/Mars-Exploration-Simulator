#include"Rover.h"

Rover::Rover()
{
}

Rover::Rover(char t, int sp, int ch, char st)
{
	R_type = t; speed = sp; checkupDuration = ch; R_status = st;
}

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

void Rover::setStatus(char s)
{
	R_status = s;
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

char Rover::getStatus()
{
	return R_status;
}
