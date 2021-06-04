#pragma once

class MarsStation
{

private:
	int CurrentDay;
public:
	PriorityQueue<Rover*>* ER = new PriorityQueue<Rover*>(); //Emergency Rovers Priority Queue
	PriorityQueue<Rover*>* PR = new PriorityQueue<Rover*>(); //Polar Rovers Priority Queue

	PriorityQueue<Mission*>* EM = new PriorityQueue<Mission*>(); //Emergency Missions Priority Queue
	LinkedQueue<Mission*>* PM = new LinkedQueue<Mission*>(); //Polar Missions Queue

	LinkedQueue<Rover*>* ERCH = new LinkedQueue<Rover*>(); //Emergency Rovers Check-Up Queue;
	LinkedQueue<Rover*>* PRCH = new LinkedQueue<Rover*>(); //Polar Rovers Check-Up Queue;


	PriorityQueue<Rover*>* RIE = new PriorityQueue<Rover*>(); //Rovers executing missions priority queue

	LinkedQueue<Mission*>* PFAIL = new LinkedQueue<Mission*>(); //Queue for failed polar missions

	PriorityQueue<Mission*>* CM = new PriorityQueue<Mission*>(); //Priority Queue for completed missions


	MarsStation();

	//functions
	bool NeedsCheckUp(Rover* R, char s); //If character sent is "C" it sends rover to Check-Up if needed and returns true if rover went to checkup and false if it did not need to. If character sent is "F" it immediately sends rover to checkup
	void ReturnFromCheckUp(); //Checks if there are rovers that finished checkup and gets them back
	Rover* GetEmergencyRover();
	Rover* GetPolarRover();
	void Assign_M_to_R();
	void UI_file();
	//int getCompletedMissions();
	bool CheckAreWeDone(); //function to check if there are no missions to be assigned or no missions to execute, so we can exit the program, returns 0 or 1
	int GetED(Mission* M, char c); //To get the Execution Days 
	int GetCD(PriorityQueue<Mission*>* m, Mission M, PriorityQueue<Rover*>* ER, PriorityQueue<Rover*>* PR, FormulationEvent e); //To get the Completion Day
	void setCurrentDay(int day);
	int getCurrentDay();
	void CheckCompleted();
	bool isFailed(Mission* m, Rover* R);

};