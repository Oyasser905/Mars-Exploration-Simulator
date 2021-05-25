#include<iostream>
#include "FormulationEvent.h"
using namespace std;

void FormulationEvent::Execute()
{
	//Assign_M_to_R()
	return;
}

Mission* FormulationEvent::Formulate(char f, char t, int d, int id, int tloc, int dur, int sig)
{
	Mission* M;
	M->setType(t); M->setDay(d); M->setID(id); M->setTargetLocation(tloc); M->setDuration(dur); M->setSignificance(sig);
	return M;
}
