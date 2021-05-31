#include"Rover.h"
#include"Mission.h"

Rover::Rover()
{
}

Rover::Rover(char t, int sp, int ch, int n)
{
	R_type = t; speed = sp; checkupDuration = ch, no_check = n;
	no_missions_completed = 0; 
	DaysSpentInCheckUp = 0;
	ptrToMission = nullptr;
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

void Rover::IncrementMissionsCompleted(bool m)
{
	if (m == 0)
		no_missions_completed = 0;
	else
		no_missions_completed++;

}

void Rover::setDaysSpentInCheckup(bool m)
{
	if (m == 0)
		DaysSpentInCheckUp = 0;
	else
		DaysSpentInCheckUp++;
}

void Rover::setptrToMission(Mission* M)
{
	ptrToMission = M;
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

int Rover::getNo_Missions_Completed()
{
	return no_missions_completed;
}

int Rover::getDaysSpentInCheckUp()
{
	return DaysSpentInCheckUp;
}

Mission* Rover::getptrToMission()
{
	return ptrToMission;
}


