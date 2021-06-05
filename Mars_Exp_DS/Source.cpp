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
    mars.chooseMode();
    //step 1: read info and distribute 3ashan ye2dar yed5ol fel while
    //step 2: output yezhar ma3 el currentday
    //therefore create link
    while (!mars.CheckAreWeDone())
    {
        mars.checkEvents();
        mars.UI_w();
        mars.setCurrentDay(currentday);
        mars.CheckCompleted();
        mars.ReturnFromCheckUp(); //returns rovers that have completed check up as some could have high speeds and hence higher priority
        mars.Assign_M_to_R();
        currentday++;
    }
}

//Number 1: Completed Mai          //DONE//
//Number 2: isFailed               //DONE//
//Number 3: ne5ali el 7agaat private kolaha w ne3mel setters w getters lel queues/prqueues el bAS hanesta5demha bara el class
//Number 4: Read from input file different speeds aly.txt
//Number 5: omar: getCD, WD, wel 7agaat el tanya
//Number 6: ye3'ayar fel output yenady 3ala el variables w ye3mel keda l kol youm
//Number 7: law le7e2na bonus 3 
