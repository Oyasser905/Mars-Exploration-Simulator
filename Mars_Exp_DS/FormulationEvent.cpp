#include<iostream>
#include "FormulationEvent.h"
#include "Queue.h"
#include"priorityQueue.h"
using namespace std;

FormulationEvent::FormulationEvent(char mission_type, int event_day, int id, int tloc, int mdur, int sig)
{
    type = mission_type; setDay(event_day); setID(id); targetLocation = tloc; duration = mdur; significance = sig;
}

void FormulationEvent::Execute(Mission*& M)
{
    if (type == 'E')
    {
        M = new Mission(type, getDay(), getID(), targetLocation, duration, significance);
        M->setStatus('N'); //Not Assigned
    }
    else if (type == 'P')
    {
        M = new Mission(type, getDay(), getID(), targetLocation, duration, significance);
        M->setStatus('N'); //Not Assigned
    }
}

