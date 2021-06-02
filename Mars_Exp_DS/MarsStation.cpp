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
}

//Omar Yasser
void MarsStation::UI_file()
{
    UI uiobj;
    uiobj.r_input();
    uiobj.p_output();
}

//Malak
void MarsStation::setCurrentDay(int day)
{
    CurrentDay = day;
}

//Malak
int MarsStation::getCurrentDay()
{
    return CurrentDay;
}

//Malak
bool MarsStation::CheckAreWeDone()
{
    if (EM->isEmpty() && PM->isEmpty() && PFAIL->isEmpty())
        return 1;
    else
        return 0;
}

//Malak
bool MarsStation::NeedsCheckUp(Rover* R, char s) //checks if the rover needs checkup, if yes sends it to checkup and changes variable "no_missions_completed" to zero
{

    if (s == 'C') //if character sent is C this means the rover completed a mission and therefore we need to check if it reached maximum amount of missions completed before checkup
    {
        if (R->getType() == 'E') //if Rover was an emergency rover
        {
            if (R->getNo_Check() == R->getNo_Missions_Completed())
            {
                ERCH->enqueue(R);
                R->setDayToLeaveCheckup((R->getCheckupDuration()) + CurrentDay); //sets variable DayToLeaveCheckup
                R->IncrementMissionsCompleted(0);
                return 1;
            }
        }
        else if (R->getType() == 'P') //if Rover was a polar rover
        {
            if (R->getNo_Check() == R->getNo_Missions_Completed())
            {
                PRCH->enqueue(R);
                R->setDayToLeaveCheckup((R->getCheckupDuration()) + CurrentDay); //sets variable DayToLeaveCheckUp
                R->IncrementMissionsCompleted(0);
                return 1;
            }
        }
    }
    else if (s == 'F') //if character sent was F this means rover failed to do mission and therefore it should automatically go to checkup
    {
        if (R->getType() == 'E')
        {
            ERCH->enqueue(R);
            R->setDayToLeaveCheckup((R->getCheckupDuration()) + CurrentDay); //sets variable DayToLeaveCheckUp
            R->IncrementMissionsCompleted(0);
            return 1;
        }
        else if (R->getType() == 'P')
        {
            PRCH->enqueue(R);
            R->setDayToLeaveCheckup((R->getCheckupDuration()) + CurrentDay); //sets variable DayToLeaveCheckUp
            R->IncrementMissionsCompleted(0);
            return 1;
        }
    }
    return 0;
}


//Malak
void MarsStation::ReturnFromCheckUp()
{
    Rover* ERP; //pointer to first element in emergency check up list
    Rover* PRP; //pointer to first element in polar check up list
    if (ERCH->peek(ERP))
    {
        //while currentday is equal to the day the first rover (in the priority queue) should leave check up then dequeue rover from checkup and enqueue it in emergency rovers priority queue
        while((ERCH->peek(ERP))&&(CurrentDay==ERP->getDayToLeaveCheckUp()))
        {
            ERCH->dequeue(ERP);
            ER->enqueue(ERP, ERP->getSpeed());
        }
    }
    if (PRCH->peek(PRP))
    {
        //while currentday is equal to the day the first rover (in the queue) should leave check up
        while ((PRCH->peek(PRP)) && (CurrentDay == PRP->getDayToLeaveCheckUp()))
        {
            PRCH->dequeue(PRP);
            PR->enqueue(PRP, PRP->getSpeed());
        }
    }
    return;
}

//Malak
Rover* MarsStation::GetEmergencyRover()
{
    Rover* CurrentRover;
    if (!ER->isEmpty())
    {
        ER->dequeue(CurrentRover);
        return CurrentRover;
    }
    else
        return nullptr;
}

//Malak
Rover* MarsStation::GetPolarRover() //returns polar rovers that have completed check up as some could have high speeds and hence higher priority
{
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
void MarsStation::Assign_M_to_R()
{
    Mission* m;
    while ((EM->peek(m)) && (m->getDay() <= CurrentDay) && (m->getType() == 'E')) //assign emergency missions first //CHECK if it is not in execution
    {
        Rover* EmergencyRover = GetEmergencyRover();
        if (EmergencyRover) //if an emergency rover was available
        {
            RIE->sort_asc_enqueue(EmergencyRover, GetED(m,'E')); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority
            EmergencyRover->setptrToMission(m);
            EmergencyRover->setDayToLeaveFromExecution((GetED(m, 'E') + CurrentDay)); //Sets variable day to leave from execution
            EM->dequeue(m);
            m->setStatus('I');
            EM->enqueue(m, m->calcWeight());
        }
        else
        {
            Rover* PolarRover = GetPolarRover();
            if (PolarRover) //else if a polar rover was available
            {
                RIE->sort_asc_enqueue(PolarRover, GetED(m,'P')); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority
                PolarRover->setptrToMission(m); 
                PolarRover->setDayToLeaveFromExecution((GetED(m, 'P') + CurrentDay)); //Sets variable day to leave from execution
                EM->dequeue(m);
                m->setStatus('I');
                EM->enqueue(m, m->calcWeight());
            }
            else //mark as waiting
            {
                m->setStatus('W'); //marks ONLY the first element as waiting since all the rest (except in execution) would be waiting as well
            }
        }
    }

    while ((PFAIL->peek(m)) && (m->getDay() == CurrentDay) && (m->getType() == 'P'))
    {
        Rover* PolarRover = GetPolarRover();
        if (PolarRover) //if a polar rover was available
        {
            RIE->sort_asc_enqueue(PolarRover, GetED(m, 'P')); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority
            PolarRover->setptrToMission(m);
            PolarRover->setDayToLeaveFromExecution((GetED(m, 'P') + CurrentDay)); //Sets variable day to leave from execution
            PFAIL->dequeue(m);
            m->setStatus('I');
            PFAIL->enqueue(m); //Since failed polar missions are in a queue and I want in-execution missions to be at the end I will dequeue and enqueue again
        }
        else
        {
            m->setStatus('W');
        }
    }

    while ((PM->peek(m))&& (m->getDay() == CurrentDay) && (m->getType() == 'P')) //then assign polar missions
    {
        Rover* PolarRover = GetPolarRover();
        if (PolarRover) //if an emergency rover was available
        {
            RIE->sort_asc_enqueue(PolarRover, GetED(m,'P')); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority
            PolarRover->setptrToMission(m);
            PM->dequeue(m);
            m->setStatus('I');
            PM->enqueue(m); //Since polar missions are in a queue and I want in-execution missions to be at the end I will dequeue and enqueue again
        }
        else
        {
            m->setStatus('W');
        }
    }
}

//Omar AbdelAzeem
//int MarsStation::getCompletedMissions()
//{
   // Mission* m2;
    //while (->dequeue(m2))
   // {
      //  CM->sort_asc_enqueue(m2, m2->getWeight()); //send days taken to complete missions NOT getWeight() as getweight is made to determine priority of emergency missions
   // }
   // return CM->getSize();
//}

//Omar AbdelAzeem
//int GetFD() //To get the Formulation Day
//{
  //  FormulationEvent e;
    //return e.getDay();
//}

//int GetWD(PriorityQueue<Mission*>* m) //To get the Waiting Days
//{
//    the day the mission get assigned to a rover - the day the mission got formulated GetFD(e)
//
//}

//Omar AbdelAzeem
int MarsStation::GetED(Mission* M, char rovertype) //To get the Execution Days 
{
    float Time;
    Rover* r;
    if ((M->getType() == 'E') && (rovertype=='E')) //if it was an Emergency mission with an emergency rover assigned to it
    {
        ER->peek(r);
        r->getSpeed();           
        Time = ceil(M->getDuration() + (((M->getTargetLocation() / r->getSpeed()) / 25) * 2));    //(the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station)
    }
    else if ((M->getType() == 'E') && (rovertype == 'P')) //if it was an Emergency mission with a polar rover assigned to it
    {
        PR->peek(r);
        r->getSpeed();
        Time = ceil(M->getDuration() + (((M->getTargetLocation() / r->getSpeed())/25) * 2));      //(the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station)
    }
    else if ((M->getType() == 'P') && (rovertype=='P')) //if it was a Polar mission it must have a polar rover
    {
        PR->peek(r);
        r->getSpeed();            
        Time = ceil(M->getDuration() + ((M->getTargetLocation() / r->getSpeed()) / 25)*2);      //(the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station)
    }
    return Time;
}

//Omar AbdelAzeem
//int MarsStation::GetCD(PriorityQueue<Mission*>* m, Mission M, PriorityQueue<Rover*>* ER, PriorityQueue<Rover*>* PR, FormulationEvent e) //To get the Completion Day
//{
  //  int CD;
    //CD = /*GetWD(m)*/ +GetED(M, ER, PR) + GetFD(); //CD = FD + WD + ED
    //return CD;
//}

