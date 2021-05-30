#include"priorityQueue.h"
#include"UI.h"
#include"Mission.h"
#include"Rover.h"
#include "FormulationEvent.h"
#include "MarsStation.h"
using namespace std;

MarsStation::MarsStation()
{
    UI uiobj;
}

//Malak
void MarsStation::Assign_M_to_R(PriorityQueue<Mission*>*& EM, PriorityQueue<Mission*>*& PM, PriorityQueue<Rover*>*& ER, PriorityQueue<Rover*>*& PR, PriorityQueue<Mission*>*& WL)
{
    Mission* m;
    if (EM->dequeue(m) == 'E')
    {
        if (!ER->isEmpty())
        {
            //Assign rover code
        }
        else if (!PR->isEmpty())
        {
            //Assign rover code
        }
        else
        {
            WL->enqueue(m, m->getWeight());
        }
    }
    if (PM->dequeue(m) == 'P')
    {
        if (!PR->isEmpty())
        {
            //Assign rover code
        }
        else
        {
            WL->enqueue(m, m->getWeight());
        }
    }
}

//Omar
void checkCompletedMissions()
{
	return;
}



