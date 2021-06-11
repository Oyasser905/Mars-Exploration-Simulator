#pragma once
#include "UI.h"
#include <cmath>
class MarsStation
{

private:
	int CurrentDay;
	int NumberEMissions;
	int NumberPMissions;
	int NumberFMissions = 0;
	int NumberPRovers;
	int NumberERovers;
	int eventsWaiting;
	int WaitingTotal;
	int TotalExecution;
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
	~MarsStation();

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
	void SetNumberEMissions(int s);
	void SetNumberPMissions(int s);
	void SetNumberPRovers(int s);
	void SetNumberERovers(int s);
	void SetEventsWaiting();
	void SetWaitingTotal(int s);
	void SetExecutionDays(int s);

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
	int GetEventsWaiting();
	int GetWaitingTotal();
	int GetNumberEMissions();
	int GetNumberPMissions();
	int GetNumberFMissions();
	int GetNumberPRovers();
	int GetNumberERovers();
	int GetExecutionDays(); //Total
	int GetED(Mission* M, char c); //To get the Execution Days 
	//int GetCD(Mission* M, char rovertype); //To get the Completion Day
	//int getCompletedMissions();

	//functions
	void initialize();
	void initialize2();
	bool NeedsCheckUp(Rover* R, char s); //If character sent is "C" it sends rover to Check-Up if needed and returns true if rover went to checkup and false if it did not need to. If character sent is "F" it immediately sends rover to checkup
	void ReturnFromCheckUp(); //Checks if there are rovers that finished checkup and gets them back
	void Assign_M_to_R();
	void UI_r();
	void chooseMode();
	void UI_p();
	void UI_w();
	bool CheckAreWeDone(); //function to check if there are no missions to be assigned or no missions to execute, so we can exit the program, returns 0 or 1
	void CheckCompleted();
	bool isFailed(Mission* m, Rover* R);
	void O_Waiting();
	void O_InExec();
	void O_AvailableRovers();
	void O_InCheckupRovers();
	void O_CompletedMissions();
	void checkEvents(); //distributes the events
	int getMode();
	void p_SilentMode();
};