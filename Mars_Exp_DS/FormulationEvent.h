#pragma once
#include"Event.h"
#include"Mission.h"
#include"priorityQueue.h"
#include "Queue.h"
#include<iostream>
using namespace std;

class FormulationEvent: public Event
{
private:
	int ID;
	int day;
	char type;
	int targetLocation;
	int duration;
	int significance;
	PriorityQueue<Mission*>* EM;
	LinkedQueue<Mission*>* PM;
public:
	FormulationEvent(char rover_type, int event_day, int id, int tloc, int mdur, int sig, PriorityQueue<Mission*>*& EM, LinkedQueue<Mission*>*& PM);
	void Execute();
};