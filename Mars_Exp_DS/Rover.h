#pragma once
#include<iostream>
#include"Mission.h"
using namespace std;

class Rover
{
private:
	char R_type;
	int speed;
	int checkupDuration;
	char R_status;
	int no_check; //No. of missions allowed before check up 
	int no_missions_completed; //how many missions has the rover completed ever since last checkup
	int DaysSpentInCheckUp;
	Mission* ptrToMission; //pointer so that rover can point to a mission when it is executing it

public:
	//constructors
	Rover();
	Rover(char t, int sp, int ch, int n);
	//setters
	void setType(char t);
	void setSpeed(int s);
	void setCheckupDuration(int ch);
	void setStatus(char s);
	void setNo_Check(int n);
	void IncrementMissionsCompleted(bool m); //Increments the number of missions the rover has completed ever since checkup OR resets this number to 0
	void setDaysSpentInCheckup(bool m); //Increments the number of days the rover has spent in checkup OR resets this number to 0
	void setptrToMission(Mission* M); //sets pointer to the mission it is executing

	//getters
	char getType();
	int getSpeed();
	int getCheckupDuration();
	char getStatus();
	int getNo_Check();
	int getNo_Missions_Completed(); //Returns the number of missions the rover has completed ever since checkup
	int getDaysSpentInCheckUp();
	Mission* getptrToMission(); //gets pointer to mission a rover is executing
	
};