#include"Rover.h"

Rover::Rover()
{
}

Rover::Rover(char t, int sp, int ch, int n)
{
	R_type = t; speed = sp; checkupDuration = ch, no_check = n;
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

void Rover::setNo_Check(int n)
{
	no_check = n;
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

int Rover::getNo_Check()
{
	return no_check;
}
