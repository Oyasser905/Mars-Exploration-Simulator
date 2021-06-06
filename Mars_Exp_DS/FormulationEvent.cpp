#include<iostream>
#include "FormulationEvent.h"
#include "Queue.h"
#include"priorityQueue.h"
using namespace std;

FormulationEvent::FormulationEvent(char rover_type, int event_day, int id, int tloc, int mdur, int sig, PriorityQueue<Mission*>*& EM, LinkedQueue<Mission*>*& PM)
{
    type = rover_type; setDay(event_day); setID(id); targetLocation = tloc; duration = mdur; significance = sig;
}

void FormulationEvent::Execute()
{
    if (type == 'E')
    {
        Mission* em = new Mission(type, getDay(), getID(), targetLocation, duration, significance);
        int w = em->calcWeight();
        EM->enqueue(em, w);
    }
    else if (type == 'P')
    {
        Mission* pm = new Mission(type, getDay(), getID(), targetLocation, duration, significance);
        PM->enqueue(pm);
    }
}

