#pragma once
#include"priorityQueue.h"
#include"UI.h"
#include <iostream>
#include <fstream>
#include <string>
#include"Mission.h"
#include"Rover.h"
#include"FormulationEvent.h"
#include"MarsStation.h"
#include"priorityQueue.h"
#include"windows.h"
using namespace std;

int main()
{
    MarsStation mars;
    mars.UI_r();
    int currentday = 1;
    mars.setCurrentDay(currentday);
   // mars.SetRoverIDs();
    mars.chooseMode();
    //step 1: read info and distribute 3ashan ye2dar yed5ol fel while
    //step 2: output yezhar ma3 el currentday
    //therefore create link
    while (!mars.CheckAreWeDone())
    {
        mars.checkEvents();
        mars.CheckCompleted();
        mars.ReturnFromCheckUp(); //returns rovers that have completed check up as some could have high speeds and hence higher priority
        mars.Assign_M_to_R();
        mars.UI_p();
        mars.test();
        currentday++;
        mars.setCurrentDay(currentday);
    }
    mars.UI_w();
}

//Number 1 ne2ra awel wa7da
//Number 2 el ID el zero fel awel
//no