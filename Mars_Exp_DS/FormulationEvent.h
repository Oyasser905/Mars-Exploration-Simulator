#pragma once
#include"Event.h"
#include"Mission.h"
#include"priorityQueue.h"
#include "Queue.h"
using namespace std;

class FormulationEvent: public Event
{
private:
	char type;
	int targetLocation;
	int duration;
	int significance;
public:
	FormulationEvent(char mission_type, int event_day, int id, int tloc, int mdur, int sig);
	void Execute(Mission*& M);
};