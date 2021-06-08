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
#include <cmath>
using namespace std;

int main()
{
    MarsStation mars;
    mars.UI_r();
    mars.initialize();
    int currentday = 0;
   // mars.SetRoverIDs();
    mars.chooseMode();

    while (!mars.CheckAreWeDone())
    {
        currentday++;
        mars.setCurrentDay(currentday);
        mars.checkEvents();
        mars.CheckCompleted();
        mars.ReturnFromCheckUp(); //returns rovers that have completed check up as some could have high speeds and hence higher priority
        mars.Assign_M_to_R();
        mars.UI_p();
        //mars.test();

    }
    mars.initialize2();
    mars.UI_w();
}