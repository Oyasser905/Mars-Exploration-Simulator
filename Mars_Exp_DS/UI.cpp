#pragma once
#include"priorityQueue.h"
#include"Queue.h"
#include"UI.h"
#include <iostream>
#include <fstream>
#include <string>
#include"Mission.h"
#include"Rover.h"
#include"FormulationEvent.h"
#include"priorityQueue.h"
#include"windows.h"
#include "MarsStation.h"

using namespace std;


UI::UI(MarsStation* st)
{
    obj = st;
}

void UI::input_contents_console(string i_file)
{
    string line;
    ifstream fptr(i_file);
    if (fptr.is_open())
    {
        while (getline(fptr, line))
        {
            cout << line << '\n';
        }
        fptr.close();
    }
    else 
    {
        cout << "Unable to open file";
    }
}

void UI::r_input()
{
    string i_file;
    ifstream fptr;
    cout << "(Please include file extension)\nEnter input file name: ";
    cin >> i_file;
    fptr.open(i_file);

    //Check if input of file name is correct and in directory
    while (!fptr.is_open())
    {
        cout << "\n\n(Please include file extension)\nError! Re-Enter input file name: ";
        cin >> i_file;
        fptr.open(i_file);
    }
    system("CLS");

    //Input file name is correct 
    if (fptr.is_open())
    {
        cout << "File opened successfully...\nFile Contents...\n\n";
        input_contents_console(i_file);
        cout << "\nPress any key to continue...\n\n";
        while (cin.get() && !fptr.eof())
        {
            char event_type; //Event type (formulation, cancellation, promotion)
            char mission_type; //Type of rover (mountainous, polar, emergency)
            int event_day; //Event day
            int ID; //Mission ID
            int tloc; //Target Location
            int mdur; //Mission Duration
            int sig; //Mission Significance
            //Read input in variables
            fptr >>
                num_er >> num_pr;

            LinkedQueue<int>* ERSpd = new LinkedQueue<int>();
            LinkedQueue<int>* PRSpd = new LinkedQueue<int>();

            for (int i = 0; i < num_er; i++)
            {
                int x;
                fptr >> x;
                ERSpd->enqueue(x);
            }

            for (int i = 0; i < num_pr; i++)
            {
                int x;
                fptr >> x;
                PRSpd->enqueue(x);
            }
            fptr >>
                num_missions >> er_ch >> pr_ch >>
                no_events;

            LinkedQueue<Event*>* EV = obj->GetEV();
            for (int i = 0; i < no_events; i++)
            {
                fptr >> event_type >> mission_type >> event_day >> ID >> tloc >> mdur >> sig;

                if (event_type == 'F')
                {
                    Event* f = new FormulationEvent(mission_type, event_day, ID, tloc, mdur, sig);
                    EV->enqueue(f);
                }
            }
            obj->setEV(EV);
            int k;
            for (int i = 0; i < num_er; i++)
            {
                int x;
                ERSpd->dequeue(x);
                Rover* er = new Rover('E', x, er_ch, num_missions, i);
                er->setStatus('A');
                obj->GetER()->enqueue(er, x);
                if (i == num_er - 1)
                    k = i + 1;

            }
            for (int i = 0; i < num_pr; i++)
            {
                int x;
                PRSpd->dequeue(x);
                Rover* pr = new Rover('P', x, er_ch, num_missions, k + i);
                pr->setStatus('A');
                obj->GetPR()->enqueue(pr, x);
            }
        }
        fptr.close();
        system("CLS");
        cout << "File successfully closed...\n\n";
        Sleep(2500);
    }
    else
    {
        cout << "\nError! Unable to open input file successfully.\n\n";
    }
}

int UI::getNum_of_events()
{
    return no_events;
}

void UI::Interactive_mode()
{
    char x;
    cin.get(x);
    system("CLS");
    cout << "Current Day: " << obj->getCurrentDay() << "\n";
    cout << (obj->GetEM()->getSize())+(obj->GetPM()->getSize()) << " Waiting Missions: "; obj->O_Waiting(); cout << "\n";
    cout << "------------------------------------------\n";
    cout << (obj->GetRIE())->getSize() << " In-Execution Missions/Rovers: "; obj->O_InExec(); cout << "\n";
    cout << "------------------------------------------\n";
    cout << (obj->GetER()->getSize()) + (obj->GetPR()->getSize()) << " Available Rovers: "; obj->O_AvailableRovers(); cout << "\n";
    cout << "------------------------------------------\n";
    cout << (obj->GetERCH()->getSize()) + (obj->GetPRCH()->getSize()) << " In-Checkup Rovers: "; obj->O_InCheckupRovers(); cout << "\n";
    cout << "------------------------------------------\n";
    cout << (obj->GetCM())->getSize() << " Completed Missions: "; obj->O_CompletedMissions(); cout << "\n\n\n";
    
}

void UI::SbS_mode()
{
        system("CLS");
        cout << "Current Day: " << obj->getCurrentDay() << "\n";
        cout << (obj->GetEM()->getSize()) + (obj->GetPM()->getSize()) << " Waiting Missions: "; obj->O_Waiting(); cout << "\n";
        cout << "------------------------------------------\n";
        cout << (obj->GetRIE())->getSize() << " In-Execution Missions/Rovers: "; obj->O_InExec(); cout << "\n";
        cout << "------------------------------------------\n";
        cout << (obj->GetER()->getSize())+(obj->GetPR()->getSize()) << " Available Rovers: "; obj->O_AvailableRovers(); cout << "\n";
        cout << "------------------------------------------\n";
        cout << (obj->GetERCH()->getSize()) + (obj->GetPRCH()->getSize()) << " In-Checkup Rovers: "; obj->O_InCheckupRovers(); cout << "\n";
        cout << "------------------------------------------\n";
        cout << (obj->GetCM())->getSize() << " Completed Missions: "; obj->O_CompletedMissions(); cout << "\n\n\n";
        Sleep(1000);
}

void UI::Silent_mode()
{
    system("CLS");
    cout << "Silent Mode\nSimulation Starts...\nSimulation Ends, Output file created\n\n\n";
}

void UI::w_file()
{
    system("CLS");
    string o_file;
    cout << "(Please include file extension)\nEnter output file name: ";
    cin >> o_file;
    int j=obj->GetCM()->getSize();
    ofstream myfile(o_file);
    PriorityQueue<Mission*>* temp = new PriorityQueue<Mission*>(*(obj->GetCM()));
    if (myfile.is_open())
    {
        Mission* M;
        myfile << "CD\tID\tFD\tWD\tED\n";
        int k;
        int o;
        for (int i = 0; i < j; i++)
        {
            obj->GetCM()->dequeue(M);
            k = M->getWaitingDays();
            o = M->getExecutionDays();
            obj->SetWaitingTotal(k);
            obj->SetExecutionDays(o);
            myfile << M->getCompletedDay() << "\t" << M->getID() << "\t" << M->getDay() << "\t" << M->getWaitingDays() << "\t" << M->getExecutionDays() << "\n";
            temp->enqueue(M,M->getCompletedDay());
        }
        for (int i = 0; i < j; i++)
        {
            temp->dequeue(M);
            obj->GetCM()->enqueue(M, (-1*M->getCompletedDay()));
        }
        myfile << "...................................................................................................." << endl;
        myfile << endl;
        myfile << "...................................................................................................." << endl;
        myfile << "Missions " << (obj->GetNumberEMissions()) + (obj->GetNumberPMissions()) << " [P :" << obj->GetNumberPMissions() << ", E:" << obj->GetNumberEMissions() << "]" << endl;
        myfile<<"Rovers " << (obj->GetNumberERovers()) + (obj->GetNumberPRovers()) << " [P :" << obj->GetNumberPRovers() << ", E:" << obj->GetNumberERovers() << "]" << endl;
        float b=0;
        if (obj->GetEventsWaiting() == 0)
            b = 0;
        else
            b = ((obj->GetWaitingTotal()) / (obj->GetEventsWaiting()));
        myfile << "Avg Wait=" << b << ", Avg Exec="<< ((obj->GetExecutionDays() / obj->GetNumberEMissions()));
        myfile.close();
    }
    else cout << "Unable to write to file...";
}


void UI::p_output()
{
    if (mode == 1)
    {
        Interactive_mode();
    }
    else if (mode == 2)
    {
        SbS_mode();
    }
    else if (mode == 3)
    {
        Silent_mode();
    }
}

void UI::chooseMode()
{
    int choice;
    cout << "1.Interactive mode\n2.Step-by-Step mode\n3.Silent mode\n\n";
    cin >> choice;
    if (choice == 1)
    {
        system("CLS");
        mode = 1;
    }
    else if (choice == 2)
    {
        system("CLS");
        mode = 2;
    }
    else if (choice == 3)
    {
        system("CLS");
        mode = 3;
    }
    else
    {
        system("CLS");
        cout << "Error! Incorrect input re-enter your choice...\n\n";
    }
}
