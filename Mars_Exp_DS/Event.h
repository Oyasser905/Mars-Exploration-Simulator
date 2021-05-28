#pragma once
#include"Mission.h"
#include"priorityQueue.h"

class Event
{
private:
	int missionID;
	int eventDay;
public:
	virtual void Execute(char rover_type, int event_day, int ID, int tloc, int mdur, int sig, PriorityQueue<Mission*>* EM, PriorityQueue<Mission*>* PM) = 0;
	int getDay() const;
	int getID() const;
};