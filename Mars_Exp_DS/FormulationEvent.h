#pragma once
#include"Event.h"
#include"Mission.h"
#include"priorityQueue.h"
#include "Queue.h"
#include<iostream>
using namespace std;

class FormulationEvent: public Event
{
public:
	FormulationEvent();
	void Execute(char rover_type, int event_day, int ID, int tloc, int mdur, int sig, PriorityQueue<Mission*>*& EM, LinkedQueue<Mission*>*& PM);
};