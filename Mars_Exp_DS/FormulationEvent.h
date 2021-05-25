#pragma once
#include"Event.h"
#include"Mission.h"
#include<iostream>
using namespace std;

class FormulationEvent:Event
{
	void Execute();
	Mission* Formulate(char f, char t, int day, int id, int tloc, int dur, int sig);
};