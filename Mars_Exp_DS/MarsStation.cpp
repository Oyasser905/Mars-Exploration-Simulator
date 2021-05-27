#include"priorityQueue.h"
#include"UI.h"
#include <iostream>
#include <fstream>
#include <string>
#include"Mission.h"
#include"Rover.h"
#include "FormulationEvent.h"
#include"priorityQueue.h"
//#include"Queue.h"
using namespace std;

PriorityQueue<Rover>* ER; //Emergency Rovers Priority Queue
PriorityQueue<Rover>* PR; //Polar Rovers Priority Queue

PriorityQueue<Mission>* EM; //Emergency Missions Priority Queue
PriorityQueue<Mission>* PM; //Polar Missions Priority Queue

PriorityQueue<Mission>* WL; //Waiting list Priority Queue

int num_pr; //No. of polar rovers
int num_er; //No. of emergency rovers

int pr_sp; //Polar rover speed
int er_sp; //Emergency rover speed

int num_missions; //No. of missions before check up
int pr_ch; //Polar check up duration
int er_ch; //Emergency check up duration

int no_events; //No. of events

void r_input(string file)
{
    string line;
    ifstream fptr(file);
    if (fptr.is_open())
    {
        cout << "\nFile opened successfully...\nFile Contents...\n\n";
        while (cin.get())
        {
            char event_type; //Event type (formulation, cancellation, promotion)
            char rover_type; //Type of rover (mountainous, polar, emergency)
            int event_day; //Event day
            int ID; //Mission ID
            int tloc; //Target Location
            int mdur; //Mission Duration
            int sig; //Mission Significance

            //Read input in variables
            fptr >>
                num_pr >> num_er >>
                pr_sp >> er_sp >>
                num_missions >> pr_ch >> er_ch >>
                no_events;

            for (int i = 0; i < no_events; i++)
            {
                fptr >> event_type >> rover_type >> event_day >> ID >> tloc >> mdur >> sig;

                if (event_type == 'F')
                {
                    if (rover_type == 'E')
                    {
                        Mission em(rover_type, event_day, ID, tloc, mdur, sig);
                        int w = em.calcWeight();
                        EM->enqueue(em, w);
                    }
                    else if (rover_type == 'P')
                    {
                        Mission pm(rover_type, event_day, ID, tloc, mdur, sig);
                        PM->enqueue(pm, sig);
                    }
                }
            }
            for (int i = 0; i < (num_er + num_pr); i++)
            {
                fptr >> event_type >> rover_type >> event_day >> ID >> tloc >> mdur >> sig;

                if (rover_type == 'E')
                {
                    Rover er(rover_type, er_sp, er_ch, num_missions);
                    ER->enqueue(er, er_sp);
                }
                else if (rover_type == 'P')
                {
                    Rover pr(rover_type, pr_sp, pr_ch, num_missions);
                    PR->enqueue(pr, pr_sp);
                }
                //Assign_M_to_R(EM, PM, ER, PR, WL);
            }

            cout <<
                num_pr << " " << num_er << "\n" <<
                pr_sp << " " << er_sp << "\n" <<
                num_missions << " " << pr_ch << " " << er_ch << "\n" <<
                no_events << "\n";

            for (int i = 0; i < no_events; i++)
            {
                cout << event_type << " " << rover_type << " " << event_day << " " << ID << " " << tloc << " " << mdur << " " << sig << "\n";
            }
        }
        fptr.close();
    }
    else
    {
        cout << "\nError! Unable to open input file successfully.\n\n";
    }
}

void Assign_M_to_R(PriorityQueue<Mission>*& EM, PriorityQueue<Mission>*& PM, PriorityQueue<Rover>*& ER, PriorityQueue<Rover>*& PR, PriorityQueue<Mission>*& WL)
{
	Mission m;
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
			WL->enqueue(m, m.getWeight());
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
			WL->enqueue(m, m.getWeight());
		}
	}
}


void checkCompletedMissions()
{
	return;
}

void checkDroneRovers()
{
	return;
}

int main()
{
    string file;
    cout << "(Please include file extension)\nEnter file name: ";
    cin >> file;
    r_input(file);
}