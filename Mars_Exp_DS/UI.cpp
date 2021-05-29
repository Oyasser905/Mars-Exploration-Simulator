#pragma once
#include"priorityQueue.h"
#include"UI.h"
#include <iostream>
#include <fstream>
#include <string>
#include"Mission.h"
#include"Rover.h"
#include"FormulationEvent.h"
#include"priorityQueue.h"
#include"windows.h"
using namespace std;

int num_pr; //No. of polar rovers
int num_er; //No. of emergency rovers

int pr_sp; //Polar rover speed
int er_sp; //Emergency rover speed

int num_missions; //No. of missions before check up
int pr_ch; //Polar check up duration
int er_ch; //Emergency check up duration

int no_events; //No. of events

PriorityQueue<Rover*>* ER; //Emergency Rovers Priority Queue
PriorityQueue<Rover*>* PR; //Polar Rovers Priority Queue

PriorityQueue<Mission*>* EM; //Emergency Missions Priority Queue
PriorityQueue<Mission*>* PM; //Polar Missions Priority Queue

PriorityQueue<Mission>* WL; //Waiting list Priority Queue


void Assign_M_to_R(PriorityQueue<Mission*>*& EM, PriorityQueue<Mission*>*& PM, PriorityQueue<Rover*>*& ER, PriorityQueue<Rover*>*& PR, PriorityQueue<Mission*>*& WL)
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

void r_input(string file)
{
    string line;
    ifstream fptr(file);
    if (fptr.is_open())
    {
        cout << "\nFile opened successfully...\nFile Contents...\n\n";
        while (cin.get() && !fptr.eof())
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

            for (int i = 0; i <= no_events; i++)
            {
                fptr >> event_type >> rover_type >> event_day >> ID >> tloc >> mdur >> sig;

                if (event_type == 'F')
                {
                    Event* e = new FormulationEvent();
                    e->Execute(rover_type, event_day, ID, tloc, mdur, sig, EM, PM);
                }
            }
            for (int i = 0; i < num_er; i++)
            {
                Rover* er = new Rover(rover_type, er_sp, er_ch, num_missions);
                ER->enqueue(er, er_sp);
            }
            for (int i = 0; i < num_pr; i++)
            {
                Rover* pr = new Rover(rover_type, er_sp, er_ch, num_missions);
                PR->enqueue(pr, pr_sp);
            }
            //Assign_M_to_R(EM, PM, ER, PR, WL);

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
        cout << "File successfully closed...\n";
    }
    else
    {
        cout << "\nError! Unable to open input file successfully.\n\n";
    }
}

void Interactive_mode()
{
    char x;
    for (int d = 0; d < 2; d++)
    {
        int w_m = 7, i_e = 4, a_r = 4, i_c = 2, c_m = 3;
        cout << "Current Day: " << d << "\n";
        cout << w_m << " Waiting Missions: " << "[11, 13] (6, 8)\n";
        cout << "------------------------------------------\n";
        cout << a_r << " In-Execution Missions/Rovers: " << "[2/1, 10/7] (3/5)\n";
        cout << "------------------------------------------\n";
        cout << w_m << " Available Rovers: " << "[4, 6] (10)\n";
        cout << "------------------------------------------\n";
        cout << i_c << " In-Checkup Rovers: " << "[2] (3)\n";
        cout << "------------------------------------------\n";
        cout << c_m << " Completed Missions: " << "(4) [1]\n\n\n";
        //cin.get(x);
        cin >> x;
    }
}

void SbS_mode()
{
    for (int d = 0; d < 2; d++)
    {
        int w_m = 7, i_e = 4, a_r = 4, i_c = 2, c_m = 3;
        cout << "Current Day: " << d << "\n";
        cout << w_m << " Waiting Missions: " << "[11, 13] (6, 8)\n";
        cout << "------------------------------------------\n";
        cout << a_r << " In-Execution Missions/Rovers: " << "[2/1, 10/7] (3/5)\n";
        cout << "------------------------------------------\n";
        cout << w_m << " Available Rovers: " << "[4, 6] (10)\n";
        cout << "------------------------------------------\n";
        cout << i_c << " In-Checkup Rovers: " << "[2] (3)\n";
        cout << "------------------------------------------\n";
        cout << c_m << " Completed Missions: " << "(4) [1]\n\n\n";
        Sleep(3000);
    }
}

void Silent_mode()
{
    cout << "Silent Mode\nSimulation Starts...\nSimulation Ends, Output file created\n";
}

void w_file(string fname)
{
    ofstream myfile(fname);
    if (myfile.is_open())
    {
        myfile << "This is a line.\n";
        myfile << "This is another line.\n";
        myfile.close();
    }
    else cout << "Unable to write to file...";
}


void p_output(string fname)
{
    int choice;
    while (true)
    {
        system("CLS");
        cout << "1.Interactive mode\n2.Step-by-Step mode\n3.Silent mode\n4.Exit Program\n\n";
        cin >> choice;
        if (choice == 1)
        {
            w_file(fname);
            Interactive_mode();
        }
        else if (choice == 2)
        {
            w_file(fname);
            SbS_mode();
        }
        else if (choice == 3)
        {
            w_file(fname);
            Silent_mode();
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "Error! Incorrect input re-enter your choice...\n\n";
        }
    }
}

int main()
{
    string i_file, o_file;
    cout << "(Please include file extension)\nEnter file name: ";
    cin >> i_file;
    r_input(i_file);

    cout << "(Please include file extension)\nEnter file name: ";
    cin >> o_file;
    p_output(o_file);
}