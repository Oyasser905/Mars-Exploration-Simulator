#include"priorityQueue.h"
#include"Queue.h"
#include"UI.h"
#include"Mission.h"
#include"Rover.h"
#include "FormulationEvent.h"
#include "MarsStation.h"
#include "time.h"
using namespace std;

MarsStation::MarsStation()
{
    EV = new LinkedQueue<Event*>();

    ER = new PriorityQueue<Rover*>(); //Emergency Rovers Priority Queue
    PR = new PriorityQueue<Rover*>(); //Polar Rovers Priority Queue

    EM = new PriorityQueue<Mission*>(); //Emergency Missions Priority Queue
    PM = new LinkedQueue<Mission*>(); //Polar Missions Queue

    ERCH = new LinkedQueue<Rover*>(); //Emergency Rovers Check-Up Queue;
    PRCH = new LinkedQueue<Rover*>(); //Polar Rovers Check-Up Queue;

    RIE = new PriorityQueue<Rover*>(); //Rovers executing missions priority queue

    PFAIL = new LinkedQueue<Mission*>(); //Queue for failed polar missions

    CM = new PriorityQueue<Mission*>(); //Priority Queue for completed missions
    uiobj = new UI(this);
}

//Omar Yasser
void MarsStation::UI_r()
{
    uiobj->r_input();
}

void MarsStation::chooseMode()
{
    uiobj->chooseMode();
}

void MarsStation::UI_p()
{
    uiobj->p_output();
}

void MarsStation::UI_w()
{
    uiobj->w_file();
}

//Malak
void MarsStation::setCurrentDay(int day)
{
    CurrentDay = day;
}

void MarsStation::setEV(LinkedQueue<Event*>* e)
{

    EV = e;
}

void MarsStation::setEM(PriorityQueue<Mission*>* ME)
{
    EM = ME;
}

void MarsStation::setPM(LinkedQueue<Mission*>* MP)
{
    PM = MP;
}

void MarsStation::setER(PriorityQueue<Rover*>* RE)
{
    ER = RE;
}

void MarsStation::setPR(PriorityQueue<Rover*>* RP)
{
    PR = RP;
}

void MarsStation::setERCH(LinkedQueue<Rover*>* CHER)
{
    ERCH = CHER;
}

void MarsStation::setPRCH(LinkedQueue<Rover*>* CHPR)
{
    PRCH = CHPR;
}

void MarsStation::setRIE(PriorityQueue<Rover*>* RI)
{
    RIE = RI;
}

void MarsStation::setPFAIL(LinkedQueue<Mission*>* PF)
{
    PFAIL = PF;
}

void MarsStation::setCM(PriorityQueue<Mission*>* C)
{
    CM = C;
}

//Malak
int MarsStation::getCurrentDay()
{
    return CurrentDay;
}

PriorityQueue<Mission*>* MarsStation::GetEM()
{
    return EM;
}

LinkedQueue<Mission*>* MarsStation::GetPM()
{
    return PM;
}

PriorityQueue<Rover*>* MarsStation::GetER()
{
    return ER;
}

PriorityQueue<Rover*>* MarsStation::GetPR()
{
    return PR;
}

LinkedQueue<Rover*>* MarsStation::GetERCH()
{
    return ERCH;
}

LinkedQueue<Event*>* MarsStation::GetEV()
{
    return EV;
}

LinkedQueue<Rover*>* MarsStation::GetPRCH()
{
    return PRCH;
}

PriorityQueue<Rover*>* MarsStation::GetRIE()
{
    return RIE;
}

LinkedQueue<Mission*>* MarsStation::GetPFAIL()
{
    return PFAIL;
}

PriorityQueue<Mission*>* MarsStation::GetCM()
{
    return CM;
}

//Malak
bool MarsStation::CheckAreWeDone()
{
    if (EM->isEmpty() && PM->isEmpty() && PFAIL->isEmpty() && EV->isEmpty())
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
    Rover* r;
    while ((EM->peek(m)) && (m->getDay() <= CurrentDay) && (m->getType() == 'E') && (m->getStatus()!='I')) //assign emergency missions first //CHECK if it is not in execution
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

    while ((PFAIL->peek(m)) && (m->getDay() == CurrentDay) && (m->getType() == 'P') && (m->getStatus()!='I'))
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

    while ((PM->peek(m))&& (m->getDay() == CurrentDay) && (m->getType() == 'P') && (m->getStatus()!='I')) //then assign polar missions
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

void MarsStation::O_WaitingEM()
{

    //law awel element status W keda fih 7agaat waiting
    //tayeb eh el waiting (lel 7agaat el ba3do) howa el el eventday beta3o ==currentday aw el eventday beta30 faat w kamaan en el status not IE 
    //dequeue ha2ra el data law el lesa aylah sa7 then call asc queue and pass el M fa hatet7at fel a5er
    //w hafdal a3mel keda le7ad 
    //int s=size;
    Mission* M;
    int size = EM->getSize();
    if ((EM->peek(M)) && (M->getStatus() == 'W'))
    {
        cout << "[ ";
        for (int i = 0; i < size; i++)
        {
            EM->dequeue(M);
            EM->sort_asc_enqueue(M, M->calcWeight());
            if ((M->getDay() <= CurrentDay) && (M->getStatus() != 'I'))
            {
                cout << M->getID() << " , ";
            }
        }
        cout << "]";
        for (int i = 0; i < size; i++)
        {
            EM->dequeue(M);
            EM->enqueue(M, M->calcWeight());
        }
    }
    return;
}

void MarsStation::O_AvailableRovers()
{
    Rover* R;
    int sizeER = ER->getSize();
    int sizePR = PR->getSize();
    if ((ER->peek(R)) && (R->getStatus() == 'A'))
    {
        cout << "[ ";
        for (int i = 0; i < sizeER; i++)
        {
            ER->dequeue(R);
            ER->sort_asc_enqueue(R, R->getSpeed());
            if (R->getStatus() != 'I')
            {
                cout << R->getID() << " , ";
            }
        }
        cout << "]";
        for (int i = 0; i < sizeER; i++)
        {
            ER->dequeue(R);
            ER->enqueue(R, R->getSpeed());
        }
    }
    if ((PR->peek(R)) && (R->getStatus() == 'A'))
    {
        cout << "( ";
        for (int i = 0; i < sizePR; i++)
        {
            PR->dequeue(R);
            PR->sort_asc_enqueue(R, R->getSpeed());
            if (R->getStatus() != 'I')
            {
                cout << R->getID() << " , ";
            }
        }
        cout << ")";
        for (int i = 0; i < sizePR; i++)
        {
            PR->dequeue(R);
            PR->enqueue(R, R->getSpeed());
        }
    }
    return;
}

void MarsStation::O_InCheckupRovers()
{
    Rover* R;
    int sizeER = ER->getSize();
    int sizePR = PR->getSize();
    if ((ER->peek(R)) && (R->getStatus() == 'CH'))
    {
        cout << "[ ";
        for (int i = 0; i < sizeER; i++)
        {
            ER->dequeue(R);
            ER->sort_asc_enqueue(R, R->getSpeed());
            if (R->getStatus() != 'I')
            {
                cout << R->getID() << " , ";
            }
        }
        cout << "]";
        for (int i = 0; i < sizeER; i++)
        {
            ER->dequeue(R);
            ER->enqueue(R, R->getSpeed());
        }
    }
    if ((PR->peek(R)) && (R->getStatus() == 'CH'))
    {
        cout << "( ";
        for (int i = 0; i < sizePR; i++)
        {
            PR->dequeue(R);
            PR->sort_asc_enqueue(R, R->getSpeed());
            if (R->getStatus() != 'I')
            {
                cout << R->getID() << " , ";
            }
        }
        cout << ")";
        for (int i = 0; i < sizePR; i++)
        {
            PR->dequeue(R);
            PR->enqueue(R, R->getSpeed());
        }
    }
    return;
}

void MarsStation::checkEvents()
{
    Event* E;
    EV->peek(E);
    while (E->getDay() == CurrentDay)
    {
        EV->dequeue(E);
        E->Execute();
        EV->peek(E);
    }
}

//Law queue 3ady
//awel element status W
//3ayza 2a output el waiting el mawgood
//dequeue awel element staus W print ID
//enqueue it fel a5er
//w hafdal a3mel dequeue w a2ra w ashoof law howa mesh I w ba3d keda enqueue

//int GetWaitingNumber()
//{
//case 1
//3adad dequeue, increment only law el status! I, enqueue asc, dequeue while(element status != W)
//}
//case 2
//t

//Mai
void MarsStation::CheckCompleted()
{
    Rover* R;
    Mission* M;
    bool ans;
    while ((RIE->peek(R))&&(R->getDayToLeaveFromExecution() == CurrentDay))
    {
        RIE->dequeue(R);
        if (!isFailed(R->getptrToMission(),R))
        {
            R->IncrementMissionsCompleted(1);
            (R->getptrToMission())->setStatus('C');
            ans=NeedsCheckUp(R, 'C');
            if (!ans)
            {
                if (R->getType() == 'E')
                {
                    ER->enqueue(R, R->getSpeed());
                }
                else if (R->getType() == 'P')
                {
                    PR->enqueue(R, R->getSpeed());
                }
            }
            M = R->getptrToMission();
            //CM->sort_asc_enqueue(R->getptrToMission(), GetCD());
            delete M;
        }

    }
}

//Mai
bool MarsStation::isFailed(Mission* M, Rover* R)
{

    srand(time(NULL));
    int failure = rand() % 100 + 1;
    if ((failure == 71) || (failure == 88) || (failure == 38) || (failure == 3) || (failure == 100) || (failure == 50))
    {
        NeedsCheckUp(R, 'F');
        M->setStatus('F');
        char c = M->getType();
        if (c == 'P')
        {
            PFAIL->enqueue(M);
            delete M;
        }
        else if (c == 'E')
        {
            EM->enqueue(M, M->calcWeight());
            delete M;
        }
        return true;
    }
    else
        return false;
}

//int MarsStation::GetWD(PriorityQueue<Mission*>* m) //To get the Waiting Days
//{

//daytoleaveexecution (getter) - getED() -eventday
//    the day the mission get assigned to a rover - the day the mission got formulated GetFD(e)
//
//}

//Omar AbdelAzeem
int MarsStation::GetED(Mission* M, char rovertype) //To get the Execution Days 
{
    int Day;
    Rover* r;
    if ((M->getType() == 'E') && (rovertype=='E')) //if it was an Emergency mission with an emergency rover assigned to it
    {
        ER->peek(r);
        r->getSpeed();           
        Day = ceil(M->getDuration() + (((M->getTargetLocation() / r->getSpeed()) / 25) * 2));    //(the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station)
    }
    else if ((M->getType() == 'E') && (rovertype == 'P')) //if it was an Emergency mission with a polar rover assigned to it
    {
        PR->peek(r);
        r->getSpeed();
        Day = ceil(M->getDuration() + (((M->getTargetLocation() / r->getSpeed())/25) * 2));      //(the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station)
    }
    else if ((M->getType() == 'P') && (rovertype=='P')) //if it was a Polar mission it must have a polar rover
    {
        PR->peek(r);
        r->getSpeed();            
        Day = ceil(M->getDuration() + ((M->getTargetLocation() / r->getSpeed()) / 25)*2);      //(the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station)
    }
    return Day;
}

////Omar AbdelAzeem
//int MarsStation::GetCD(Mission* M, char rovertype) //To get the Completion Day
//{
//    int CD = /*GetWD(m)*/ + GetED(M, rovertype) + M->getDay(); //CD = FD + WD + ED
//    return CD;
//}

