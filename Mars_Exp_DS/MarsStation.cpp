#include"priorityQueue.h"
#include"Queue.h"
#include"UI.h"
#include"Mission.h"
#include"Rover.h"
#include "FormulationEvent.h"
#include "MarsStation.h"
#include "time.h"
#include <cmath>
using namespace std;

MarsStation::MarsStation()
{
    int CurrentDay=0;
    NumberEMissions=0;
    NumberPMissions=0;
    NumberPRovers=0;
    NumberERovers=0;
    eventsWaiting = 0;
    WaitingTotal = 0;
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

void MarsStation::SetRoverIDs()
{
    int ID = 1;
    int j=PR->getSize();
    Rover* R;
    if (PR->peek(R))
    {
        for (int i = 0; i < j; i++)
        {
            PR->dequeue(R);
            R->setID(ID);
            ID++;
            PR->sort_asc_enqueue(R, R->getSpeed());
        }
        for (int i = 0; i < j; i++)
        {
            PR->dequeue(R);
            PR->enqueue(R, R->getSpeed());
        }
    }
    j= ER->getSize();
    if (ER->peek(R))
    {
        for (int i = 0; i < j; i++)
        {
            ER->dequeue(R);
            R->setID(ID);
            ID++;
            ER->sort_asc_enqueue(R, R->getSpeed());
        }
        for (int i = 0; i < j; i++)
        {
            ER->dequeue(R);
            ER->enqueue(R, R->getSpeed());
        }
    }
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

void MarsStation::SetNumberEMissions(int s)
{
    NumberEMissions = s;
}

void MarsStation::SetNumberPMissions(int s)
{
    NumberPMissions = s;
}

void MarsStation::SetNumberPRovers(int s)
{
    NumberPRovers = s;
}

void MarsStation::SetNumberERovers(int s)
{
    NumberERovers = s;
}

void MarsStation::SetEventsWaiting(int s)
{
    eventsWaiting = eventsWaiting + s;
}

void MarsStation::SetWaitingTotal(int s)
{
    WaitingTotal = WaitingTotal + s;
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
    if (uiobj->getNum_of_events() == CM->getSize() && CM->getSize() != 0)
        return 1;
    else
        return 0;
}



void MarsStation::initialize()
{
    SetNumberERovers(ER->getSize());
    SetNumberPRovers(PR->getSize());
}

void MarsStation::initialize2()
{
    int n=0, k = 0;
    Mission* M;
    PriorityQueue<Mission*>* temp = new PriorityQueue<Mission*>(*CM);
    while (!temp->isEmpty())
    {
        temp->dequeue(M);
        if (M->getType() == 'E')
            n++;
        if (M->getType() == 'P')
            k++;
    }
    SetNumberEMissions(n);
    SetNumberPMissions(k);
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
                R->setStatus('U');
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
                R->setStatus('U');
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
            R->setStatus('U');
            return 1;
        }
        else if (R->getType() == 'P')
        {
            PRCH->enqueue(R);
            R->setDayToLeaveCheckup((R->getCheckupDuration()) + CurrentDay); //sets variable DayToLeaveCheckUp
            R->IncrementMissionsCompleted(0);
            R->setStatus('U');
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
        while((ERCH->peek(ERP))&&(CurrentDay == ERP->getDayToLeaveCheckUp()))
        {
            ERCH->dequeue(ERP);
            ERP->setStatus('A');
            ER->enqueue(ERP, ERP->getSpeed());
        }
    }
    if (PRCH->peek(PRP))
    {
        //while currentday is equal to the day the first rover (in the queue) should leave check up
        while ((PRCH->peek(PRP)) && (CurrentDay == PRP->getDayToLeaveCheckUp()))
        {
            PRCH->dequeue(PRP);
            PRP->setStatus('A');
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
        ER->peek(CurrentRover);
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
        PR->peek(CurrentRover);
        return CurrentRover;
    }
    else
        return nullptr;
}

int MarsStation::GetEventsWaiting()
{
    return eventsWaiting;
}

int MarsStation::GetWaitingTotal()
{
    return WaitingTotal;
}

int MarsStation::GetNumberEMissions()
{
    return NumberEMissions;
}

int MarsStation::GetNumberPMissions()
{
    return NumberPMissions;
}

int MarsStation::GetNumberPRovers()
{
    return NumberPRovers;
}

int MarsStation::GetNumberERovers()
{
    return NumberERovers;
}


//Malak
void MarsStation::Assign_M_to_R()
{
    Mission* m;
    Rover* r;
    int v;
    while ((EM->peek(m)) && (m->getType() == 'E') && (m->getStatus()!='I') && (m->getStatus()!='C')) //assign emergency missions first
    {
        Rover* EmergencyRover = GetEmergencyRover();
        if (EmergencyRover) //if an emergency rover was available
        {
            v= GetED(m, 'E');
            ER->dequeue(EmergencyRover);
            m->setWaitingDays(CurrentDay - (m->getDay()));
            m->setExecutionDays(v);
            EM->dequeue(m);
            m->setStatus('I');
            //EM->enqueue(m, m->calcWeight());
            EmergencyRover->setStatus('I');
            EmergencyRover->setDayToLeaveFromExecution(v + CurrentDay); //Sets variable day to leave from execution
            EmergencyRover->setptrToMission(m);
            RIE->enqueue(EmergencyRover, -1* EmergencyRover->getDayToLeaveFromExecution()); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority
            
        }
        else
        {
            Rover* PolarRover = GetPolarRover();
            if (PolarRover) //else if a polar rover was available
            {
                v = GetED(m, 'P');
                PR->dequeue(PolarRover);
                m->setWaitingDays(CurrentDay - (m->getDay()));
                m->setExecutionDays(v);
                EM->dequeue(m);
                m->setStatus('I');
                EM->enqueue(m, m->calcWeight());
                PolarRover->setptrToMission(m);
                PolarRover->setDayToLeaveFromExecution(v+ CurrentDay); //Sets variable day to leave from execution
                PolarRover->setStatus('I');
                RIE->enqueue(PolarRover, -1 * PolarRover->getDayToLeaveFromExecution()); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority
          
            }
            else //mark as waiting
            {
                m->setStatus('W'); //marks ONLY the first element as waiting since all the rest (except in execution) would be waiting as well
                break;
            }
        }
    }

    while ((PFAIL->peek(m)) && (m->getType() == 'P') && (m->getStatus()!='I')&&(m->getStatus() != 'C') && !PR->isEmpty())
    {
        Rover* PolarRover = GetPolarRover();
        if (PolarRover) //if a polar rover was available
        {
            m->setWaitingDays(CurrentDay - (m->getDay()));
            v = GetED(m, 'P');
            PR->dequeue(PolarRover);

            m->setExecutionDays(v);
            PolarRover->setptrToMission(m);
            PolarRover->setDayToLeaveFromExecution(v + CurrentDay); //Sets variable day to leave from execution
            PolarRover->setStatus('I');
            PFAIL->dequeue(m);
            m->setStatus('I');
            RIE->enqueue(PolarRover, -1 * PolarRover->getDayToLeaveFromExecution()); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority

            //PFAIL->enqueue(m); //Since failed polar missions are in a queue and I want in-execution missions to be at the end I will dequeue and enqueue again
        }
        else
        {
            m->setStatus('W');
            break;

        }
    }

    while ((PM->peek(m)) && (m->getType() == 'P') && (m->getStatus()!='I')&& (m->getStatus() != 'C') && PR->getSize() != 0) //then assign polar missions
    {
        Rover* PolarRover = GetPolarRover();

        if (PolarRover) //if an emergency rover was available
        {
            m->setWaitingDays(CurrentDay - (m->getDay()));
            v = GetED(m, 'P');
            PR->dequeue(PolarRover);
            m->setExecutionDays(v);
            PolarRover->setptrToMission(m);
            int ff = (GetED(m, 'P') + CurrentDay);
            PolarRover->setDayToLeaveFromExecution((v + CurrentDay)); //Sets variable day to leave from execution
            PolarRover->setStatus('I');
            PM->dequeue(m);
            m->setStatus('I');
            RIE->enqueue(PolarRover, -1 * PolarRover->getDayToLeaveFromExecution()); //put the rover in "in-execution priority queue" but in reverse as I want mission with lowest durations days to have higher priority

            //Since polar missions are in a queue and I want in-execution missions to be at the end I will dequeue and enqueue again
        }
        else
        {
            m->setStatus('W');
            break;
        }
    }
}

void MarsStation::O_Waiting()
{
    PriorityQueue<Mission*>* temp = new PriorityQueue<Mission*>(*EM);
    LinkedQueue<Mission*>* temp2 = new LinkedQueue<Mission*>(*PM);
    Mission* M;
    if (temp->peek(M))
    {
        cout << "["<<M->getID();
        temp->dequeue(M);
        while (temp->peek(M))
        {
            if (M->getType() == 'E')
            {
                cout <<", " <<M->getID();
            }
            temp->dequeue(M);
        }
        cout << "] ";
    }
    if (temp2->peek(M))
    {
        cout << "(" << M->getID();
        temp2->dequeue(M);
        while (temp2->peek(M))
        {
            if (M->getType() == 'P')
            {
                cout <<", " <<M->getID();
            }
            temp2->dequeue(M);
        }
        cout << ")";
    }
return;
}

void MarsStation::O_InExec()
{
    PriorityQueue<Rover*>* temp = new PriorityQueue<Rover*>(*RIE);
    Rover* R;
    int sizeRIE = RIE->getSize();
    int sizePR = 0;
    int sizeER = 0;
    if ((temp->peek(R)) && (R->getStatus() == 'I'))
    {
        for (int i = 0; i < sizeRIE; i++)
        {
            temp->dequeue(R);
            if (R->getptrToMission()->getType() == 'E' && sizeER == 0)
            {
                cout << "[" << R->getptrToMission()->getID() << "/" << R->GetID();
                sizeER++;
            }
            else if (R->getptrToMission()->getType() == 'E')
            {
                cout << ", " << R->getptrToMission()->getID() << "/" << R->GetID();
                sizeER++;
            }
        }
       if(sizeER!=0)
           cout << "] ";

        PriorityQueue<Rover*>* temp2 = new PriorityQueue<Rover*>(*RIE);
        for (int i = 0; i < sizeRIE; i++)
        {
            temp2->dequeue(R);
            if (R->getptrToMission()->getType() == 'P' && sizePR == 0)
            {
                cout << "(" << (R->getptrToMission())->getID() << "/" << R->GetID();
                sizePR++;
            }
            else if (R->getptrToMission()->getType() == 'P')
            {
                cout << ", " << R->getptrToMission()->getID() << "/" << R->GetID();
            }
        }
        if(sizePR!=0)
            cout << ")";
    }
    else
        return;
}

void MarsStation::O_AvailableRovers()
{
    Rover* R;
    int ID;
    //SetRoverIDs();
    int sizeER = ER->getSize();
    int sizePR = PR->getSize();
    if ((ER->peek(R)) && (R->getStatus() == 'A'))
    {
        PriorityQueue<Rover*>* temp = new PriorityQueue<Rover*>();
        cout << "[";
        for (int i = 0; i < sizeER; i++)
        {

            ER->dequeue(R);
            temp->enqueue(R, R->getSpeed());
            ID = R->GetID();
            cout << ID;
                if (i < sizeER - 1)
                {
                    cout << ", ";
                }
        }
        cout << "] ";
        for (int i = 0; i < sizeER; i++)
        {
            temp->dequeue(R);
            ER->enqueue(R, R->getSpeed());
        }
    }
    if ((PR->peek(R)) && (R->getStatus() == 'A'))
    {
        PriorityQueue<Rover*>* temp = new PriorityQueue<Rover*>();
        cout << "(";
        for (int i = 0; i < sizePR; i++)
        {
            PR->dequeue(R);
            temp->enqueue(R, R->getSpeed());
            if (R->getStatus() == 'A')
            {
                cout << R->GetID();
                if (i < sizePR - 1)
                {
                    cout << ", ";
                }
            }

        }
        cout << ")";
        for (int i = 0; i < sizePR; i++)
        {
            temp->dequeue(R);
            PR->enqueue(R, R->getSpeed());
        }
    }
    return;
}

void MarsStation::O_InCheckupRovers()
{
    Rover* R;
    int sizeERCH = ERCH->getSize();
    int sizePRCH = PRCH->getSize();
    if (ERCH->peek(R))
    {
        cout << "[";
        for (int i = 0; i < sizeERCH; i++)
        {
            ERCH->dequeue(R);
            ERCH->enqueue(R);
            cout << R->GetID();
            if (i < sizeERCH - 1)
            {
                cout << ", ";
            }
        }
        cout << "]";
    }
    if (PRCH->peek(R))
    {
        cout << "(";
        for (int i = 0; i < sizePRCH; i++)
        {
            PRCH->dequeue(R);
            PRCH->enqueue(R);
            cout << R->GetID();
            if (i < sizePRCH - 1)
            {
                cout << ", ";
            }
        }
        cout << ")";
    }
    return;
}

void MarsStation::O_CompletedMissions()
{
    PriorityQueue<Mission*>* temp = new PriorityQueue<Mission*>(*CM);
    string PolarMissions = "(", Emergency = "[";
    Mission* current;
    int Psize = 0;
    int Esize = 0;
    while (temp->peek(current))
    {
        if (current->getType() == 'E')
        {
            if (Esize == 0)
            {
                Emergency;
            }
            else
                Emergency += ',';
            Emergency += to_string(current->getID());
            Esize++;
        }
        else if (current->getType() == 'P')
        {
            if (Psize == 0)
            {
                PolarMissions;
            }
            else
                PolarMissions += ',';
            PolarMissions += to_string(current->getID());
            Psize++;
        }
        temp->dequeue(current);
    }
    PolarMissions += ')';
    Emergency += ']';
    cout << Emergency << PolarMissions;
    /*Mission* M;
    int c=CM->getSize();
    int sizeCM = 0;
    if (CM->peek(M))
    {
        PriorityQueue<Mission*>* temp = new PriorityQueue<Mission*>();
        for (int i = 0; i < c; i++)
        {
            CM->dequeue(M);
            if (M->getStatus() == 'C' && sizeCM == 0 && M->getType()=='E')
            {
                cout << "[" << M->getID();
                sizeCM++;
                temp->enqueue(M, M->getCompletedDay());
            }
            else if (M->getStatus()== 'C' && M->getType()=='E')
            {
                temp->enqueue(M, M->getCompletedDay());
                cout << ", " << M->getID();
                sizeCM++;
            }
        }
        if (sizeCM != 0)
            cout << "]  ";
        for (int i = 0; i < c; i++)
        {
            temp->dequeue(M);
            CM->sort_asc_enqueue(M, M->getCompletedDay());
        }
        sizeCM = 0;
        PriorityQueue<Mission*>* temp2 = new PriorityQueue<Mission*>();
        for (int i = 0; i < c; i++)
        {
            CM->dequeue(M);
            if (M->getStatus() == 'C' && sizeCM == 0 && M->getType() == 'P')
            {
                cout << "(" << M->getID();
                sizeCM++;
                temp2->enqueue(M, M->getCompletedDay());
            }
            else if (M->getStatus() == 'C' && M->getType() == 'P')
            {
                temp2->enqueue(M, M->getCompletedDay());
                cout << ", " << M->getID();
                sizeCM++;
            }
        }
        if (sizeCM != 0)
            cout << ")";
        for (int i = 0; i < c; i++)
        {
            temp2->dequeue(M);
            CM->sort_asc_enqueue(M, M->getCompletedDay());
        }
    }*/
}

void MarsStation::checkEvents()
{
    Event* E;
    Mission* M;
    EV->peek(E);
    while ((EV->peek(E)) && (E->getDay() == CurrentDay))
    {
            EV->dequeue(E);
            E->Execute(M);
            if (M->getType() == 'E')
            {
                EM->enqueue(M, M->calcWeight());
            }
            else if (M->getType() == 'P')
            {
                PM->enqueue(M);
            }
            EV->peek(E);

    }
}


//Mai
void MarsStation::CheckCompleted()
{
    Rover* R;
    Mission* M;
    bool ans;

    while ((RIE->peek(R)))
    {
        if ((R->getDayToLeaveFromExecution() == CurrentDay))
        {
            RIE->dequeue(R);
            if (!isFailed(R->getptrToMission(), R))
            {
                R->IncrementMissionsCompleted(1);
                (R->getptrToMission())->setCompletedDay(CurrentDay);
                (R->getptrToMission())->setStatus('C');
                ans = NeedsCheckUp(R, 'C');
                if (!ans)
                {
                    if (R->getType() == 'E')
                    {
                        ER->enqueue(R, R->getSpeed());
                        R->setStatus('A');
                    }
                    else if (R->getType() == 'P')
                    {
                        PR->enqueue(R, R->getSpeed());
                        R->setStatus('A');
                    }

                }
                M = R->getptrToMission();
                CM->enqueue(R->getptrToMission(), -1*(R->getptrToMission())->getCompletedDay());
            }

        }
        else
        {
            break;
        }
        
    }
}

//Mai
bool MarsStation::isFailed(Mission* M, Rover* R)
{

    srand(time(NULL));
    int failure = rand() % 100 + 1;
    if ((failure == 71) || (failure == 88) || (failure == 3) || (failure == 50))
    {
        NeedsCheckUp(R, 'F');
        M->setStatus('F');
        char c = M->getType();
        if (c == 'P')
        {
            PFAIL->enqueue(M);
        }
        else if (c == 'E')
        {
            EM->enqueue(M, M->calcWeight());
        }
        return true;
    }
    else
        return false;
}


//Omar AbdelAzeem
int MarsStation::GetED(Mission* M, char rovertype) //To get the Execution Days 
{
    int Day=10000000;
    Rover* r;
    if ((M->getType() == 'E') && (rovertype=='E') && (ER->peek(r))) //if it was an Emergency mission with an emergency rover assigned to it
    {
        ER->peek(r);
        Day = ceil((float)(M->getDuration() + ((((float)(M->getTargetLocation() / (float)r->getSpeed())) / 25) * 2)));    //(the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station)
    }
    else if ((M->getType() == 'E') && (rovertype == 'P') &&(PR->peek(r))) //if it was an Emergency mission with a polar rover assigned to it
    {
        PR->peek(r);
        Day = ceil((float)(M->getDuration() + ((((float)(M->getTargetLocation() / (float)r->getSpeed())) / 25) * 2)));      //(the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station)
    }
    else if ((M->getType() == 'P') && (rovertype=='P') && (PR->peek(r))) //if it was a Polar mission it must have a polar rover
    {
        PR->peek(r);
        Day = ceil((float)(M->getDuration() + ((((float)(M->getTargetLocation() / (float)r->getSpeed())) / 25) * 2)));      //(the days it takes to reach the target location, fulfill mission requirements, and then get back to the base station)
    }
    return Day;
}


MarsStation::~MarsStation()
{
    //Delete Missions
    Mission* M;
    while (!EM->isEmpty())
    {
        EM->dequeue(M);
        delete M;
    }
    while (!PM->isEmpty())
    {
        PM->dequeue(M);
        delete M;
    }
    while (!CM->isEmpty())
    {
        CM->dequeue(M);
        delete M;
    }
    while (!PFAIL->isEmpty())
    {
        PFAIL->dequeue(M);
        delete M;
    }

    //Rovers
    Rover* R;
    while (!PR->isEmpty())
    {
        PR->dequeue(R);
        delete R;
    }
    while (!ER->isEmpty())
    {
        ER->dequeue(R);
        delete R;
    }
    while (!ERCH->isEmpty())
    {
        ERCH->dequeue(R);
        delete R;
    }
    while (!PRCH->isEmpty())
    {
        PRCH->dequeue(R);
        delete R;
    }
    while (!RIE->isEmpty())
    {
        RIE->dequeue(R);
        delete R;
    }

    //Events
    Event* E;
    while (!EV->isEmpty())
    {
        EV->dequeue(E);
        delete E;
    }

    //Dynamically Allocated Members
    delete uiobj;

}
