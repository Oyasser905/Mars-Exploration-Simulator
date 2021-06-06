#pragma once
#include"Mission.h"
#include"priorityQueue.h"
#include"Queue.h"
class Event
{
private:
	int missionID;
	int eventDay;
public:
	virtual void Execute() = 0;
	void setDay(int day);
	void setID(int id);
	int getDay() const;
	int getID() const;
};