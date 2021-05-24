#pragma once
#include<iostream>
using namespace std;

class Event
{
private:
	int missionID;
	int eventDay;
public:
	virtual void Execute() = 0;
	int getDay() const;
	int getID() const;
};