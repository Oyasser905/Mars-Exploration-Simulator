#include<iostream>
#include "FormulationEvent.h"
#include "Queue.h"
#include"priorityQueue.h"
using namespace std;

FormulationEvent::FormulationEvent(char rover_type, int event_day, int id, int tloc, int mdur, int sig, PriorityQueue<Mission*>*& EM, LinkedQueue<Mission*>*& PM)
{
    type = rover_type; day = event_day; ID = id; targetLocation = tloc; duration = mdur; significance = sig;
}

void FormulationEvent::Execute()
{
    if (type == 'E')
    {
        Mission* em = new Mission(type, day, ID, targetLocation, duration, significance);
        //em->setType(rover_type); em->setDay(event_day); em->setID(ID); em->setTargetLocation(tloc); em->setDuration(mdur); em->setSignificance(sig);
        int w = em->calcWeight();
        EM->enqueue(em, w);
    }
    else if (type == 'P')
    {
        Mission* pm = new Mission(type, day, ID, targetLocation, duration, significance);
        //pm->setType(rover_type); pm->setDay(event_day); pm->setID(ID); pm->setTargetLocation(tloc); pm->setDuration(mdur); pm->setSignificance(sig);
        PM->enqueue(pm);
    }
}

