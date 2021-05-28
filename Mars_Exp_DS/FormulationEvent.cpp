#include<iostream>
#include "FormulationEvent.h"
#include"priorityQueue.h"
using namespace std;

FormulationEvent::FormulationEvent()
{
}

void FormulationEvent::Execute(char rover_type, int event_day, int ID, int tloc, int mdur, int sig, PriorityQueue<Mission*>* EM, PriorityQueue<Mission*>* PM)
{
    if (rover_type == 'E')
    {
        Mission* em = new Mission(rover_type, event_day, ID, tloc, mdur, sig);
        em->setType(rover_type); em->setDay(event_day); em->setID(ID); em->setTargetLocation(tloc); em->setDuration(mdur); em->setSignificance(sig);
        int w = em->calcWeight();
        EM->enqueue(em, w);
    }
    else if (rover_type == 'P')
    {
        Mission* pm = new Mission(rover_type, event_day, ID, tloc, mdur, sig);
        pm->setType(rover_type); pm->setDay(event_day); pm->setID(ID); pm->setTargetLocation(tloc); pm->setDuration(mdur); pm->setSignificance(sig);
        PM->enqueue(pm, sig);
    }
}

