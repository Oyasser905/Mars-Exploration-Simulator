#pragma once
#include "UI.h"

class MarsStation
{

private:
	int CurrentDay;
	LinkedQueue<Event*>* EV;

	PriorityQueue<Rover*>* ER; //Emergency Rovers Priority Queue
	PriorityQueue<Rover*>* PR;//Polar Rovers Priority Queue

	PriorityQueue<Mission*>* EM; //Emergency Missions Priority Queue
	LinkedQueue<Mission*>* PM ; //Polar Missions Queue

	LinkedQueue<Rover*>* ERCH ; //Emergency Rovers Check-Up Queue;
	LinkedQueue<Rover*>* PRCH ; //Polar Rovers Check-Up Queue;


	PriorityQueue<Rover*>* RIE ; //Rovers executing missions priority queue

	LinkedQueue<Mission*>* PFAIL ; //Queue for failed polar missions

	PriorityQueue<Mission*>* CM ; //Priority Queue for completed missions
	UI* uiobj;
public:

	MarsStation();

	//setters
	void setCurrentDay(int day);
	void setEV(LinkedQueue<Event*>* e);
	void setEM(PriorityQueue<Mission*>* ME);
	void setPM(LinkedQueue<Mission*>* MP);
	void setER(PriorityQueue<Rover*>* RE);
	void setPR(PriorityQueue<Rover*>* RP);
	void setERCH(LinkedQueue<Rover*>* CHER);
	void setPRCH(LinkedQueue<Rover*>* CHPR);
	void setRIE(PriorityQueue<Rover*>* RI);
	void setPFAIL(LinkedQueue<Mission*>* PF);
	void setCM(PriorityQueue<Mission*>* C);

	//getters
	int getCurrentDay();
	PriorityQueue<Mission*>* GetEM();
	LinkedQueue<Mission*>* GetPM();
	PriorityQueue<Rover*>* GetER();
	PriorityQueue<Rover*>* GetPR();
	LinkedQueue<Rover*>* GetERCH();
	LinkedQueue<Event*>* GetEV();
	LinkedQueue<Rover*>* GetPRCH();
	PriorityQueue<Rover*>* GetRIE();
	LinkedQueue<Mission*>* GetPFAIL();
	PriorityQueue<Mission*>* GetCM();
	Rover* GetEmergencyRover();
	Rover* GetPolarRover();
	int GetED(Mission* M, char c); //To get the Execution Days 
	//int GetCD(PriorityQueue<Mission*>* m, Mission M, PriorityQueue<Rover*>* ER, PriorityQueue<Rover*>* PR, FormulationEvent e); To get the Completion Day
	//int getCompletedMissions();

	//functions
	bool NeedsCheckUp(Rover* R, char s); //If character sent is "C" it sends rover to Check-Up if needed and returns true if rover went to checkup and false if it did not need to. If character sent is "F" it immediately sends rover to checkup
	void ReturnFromCheckUp(); //Checks if there are rovers that finished checkup and gets them back
	void Assign_M_to_R();
	void UI_r();
	void UI_w();
	bool CheckAreWeDone(); //function to check if there are no missions to be assigned or no missions to execute, so we can exit the program, returns 0 or 1
	void CheckCompleted();
	bool isFailed(Mission* m, Rover* R);
	void O_WaitingEM();
	void checkEvents(); //distributes the events
	void chooseMode();
};