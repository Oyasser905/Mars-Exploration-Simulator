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
    mars.UI_file();
    int currentday = 1;

    while (!mars.CheckAreWeDone())
    {
        mars.setCurrentDay(currentday);
        mars.ReturnFromCheckUp(); //returns rovers that have completed check up as some could have high speeds and hence higher priority
        mars.Assign_M_to_R();


        currentday++;
    }
}