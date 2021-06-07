#include"Rover.h"
#include"Mission.h"

Rover::Rover()
{
}


Rover::Rover(char t, int sp, int ch, int n, int ID)
{
	R_type = t; speed = sp; checkupDuration = ch, no_check = n; RID = ID;
	no_missions_completed = 0; 
	DayToLeaveCheckUp = 75073; //this number would never be used except if there was a logical error
	ptrToMission = nullptr;
	DayToLeaveExecution = 75073; //this number would never be used except if there was a logical error
}

void Rover::setType(char t)
{
	R_type = t;
}

void Rover::setID(int id)
{
	RID = id;
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

void Rover::setDayToLeaveCheckup(int day1)
{
	DayToLeaveCheckUp = day1;
}

void Rover::setptrToMission(Mission* M)
{
	ptrToMission = M;
}

void Rover::setDayToLeaveFromExecution(int d)
{
	DayToLeaveExecution = d;
}

char Rover::getType()
{
	return R_type;
}

int Rover::GetID()
{
	return RID;
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

int Rover::getDayToLeaveCheckUp()
{
	return DayToLeaveCheckUp;
}

Mission* Rover::getptrToMission()
{
	return ptrToMission;
}

int Rover::getDayToLeaveFromExecution()
{
	return DayToLeaveExecution;
}




