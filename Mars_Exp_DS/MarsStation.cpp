#include"priorityQueue.h"
#include"Queue.h"
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

bool MarsStation::NeedsCheckUp(Rover* R) //checks if the rover needs checkup, if yes sends it to checkup and changes variable "no_missions_completed" to zero
{
    if (R->getType() == 'E')
    {
        if (R->getNo_Check() == R->getNo_Missions_Completed())
        {
            ERCH->enqueue(R);
            R->IncrementMissionsCompleted(0);
            return 1;
        }
    }
    else if (R->getType() == 'P')
    {
        if (R->getNo_Check() == R->getNo_Missions_Completed())
        {
            PRCH->enqueue(R);
            R->IncrementMissionsCompleted(0);
            return 1;
        }
    }
    return 0;
}

void MarsStation::ReturnFromCheckUp()
{
    Rover* ERP; //pointer to first element in emergency check up list
    Rover* PRP; //pointer to first element in polar check up list
    if (!ERCH->isEmpty())
    {
        ERCH->peek(ERP);
        //while first rover in checkup queue of Emergency rovers has spent required days in checkup dequeue it and enqueue it again in Emergency Rovers Priority Queue
        while(ERP->getCheckupDuration() == ERP->getDaysSpentInCheckUp()) 
        {
            ERCH->dequeue(ERP);
            ER->enqueue(ERP, ERP->getSpeed());
            ERCH->peek(ERP);
        }
    }
    if (!PRCH->isEmpty())
    {
        PRCH->peek(PRP);
        //while first rover in checkup queue of Polar rovers has spent required days in checkup dequeue it and enqueue it again in Polar Rovers Priority Queue
        while (PRP->getCheckupDuration() == PRP->getDaysSpentInCheckUp())
        {
            PRCH->dequeue(PRP);
            PR->enqueue(PRP, PRP->getSpeed());
            PRCH->peek(PRP);
        }
    }
}


Rover* MarsStation::GetEmergencyRover()
{
    ReturnFromCheckUp(); //returns emergency rovers that have completed check up as some could have high speeds and hence higher priority
    Rover* CurrentRover;
    if (!ER->isEmpty())
    {
        ER->dequeue(CurrentRover);
        return CurrentRover;
    }
    else
        return nullptr;
}

Rover* MarsStation::GetPolarRover() //returns polar rovers that have completed check up as some could have high speeds and hence higher priority
{
    ReturnFromCheckUp();
    Rover* CurrentRover;
    if (!PR->isEmpty())
    {
        PR->dequeue(CurrentRover);
        return CurrentRover;
    }
    else
        return nullptr;
}

//Rover* currentrover;
//bool checkupstatus;
//while (!ER->isEmpty())
//{
  //  ER->dequeue(currentrover);
    //checkupstatus = CheckUp(currentrover);
    //if (checkupstatus == 0)
      //  return currentrover;
//}
//return nullptr;
//}

//Malak
void MarsStation::Assign_M_to_R(PriorityQueue<Mission*>*& EM, PriorityQueue<Mission*>*& PM, PriorityQueue<Rover*>*& ER, PriorityQueue<Rover*>*& PR, PriorityQueue<Mission*>*& WL)
{
    Mission* m;
    if ((!EM->isEmpty())&&(EM->peek(m) == 'E')) //assign emergency missions first
    {
        Rover* EmergencyRover = GetEmergencyRover();
        if (EmergencyRover) //if an emergency rover was available
        {
            RIE->sort_asc_enqueue(EmergencyRover, m->getDuration()); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority
            EmergencyRover->setptrToMission(m);
        }
        else
        {
            Rover* PolarRover = GetPolarRover();
            if (PolarRover) //else if a polar rover was available
            {

                RIE->sort_asc_enqueue(PolarRover, m->getDuration()); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority
                PolarRover->setptrToMission(m);
            }
            else //mark as waiting
            {
                //turn mission to waiting
            }
            //WL->enqueue(m, m->getWeight());
        }
    }
    if ((!PM->isEmpty())&&(PM->dequeue(m) == 'P')) //then assign polar missions
    {
        Rover* PolarRover = GetPolarRover();
        if (PolarRover) //if an emergency rover was available
        {
            RIE->sort_asc_enqueue(PolarRover, m->getDuration()); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority
            PolarRover->setptrToMission(m);
        }
        else
        {
                //turn mission to waiting
        }
            //WL->enqueue(m, m->getWeight());
    }
}

//Omar
void checkCompletedMissions()
{
	return;
}



