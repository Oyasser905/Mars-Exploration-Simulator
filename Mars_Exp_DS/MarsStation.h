#pragma once

class MarsStation
{
public:
	PriorityQueue<Rover*>* ER = new PriorityQueue<Rover*>(); //Emergency Rovers Priority Queue
	PriorityQueue<Rover*>* PR = new PriorityQueue<Rover*>(); //Polar Rovers Priority Queue

	PriorityQueue<Mission*>* EM = new PriorityQueue<Mission*>(); //Emergency Missions Priority Queue
	PriorityQueue<Mission*>* PM = new PriorityQueue<Mission*>(); //Polar Missions Priority Queue

	LinkedQueue<Rover*>* ERCH = new LinkedQueue<Rover*>(); //Emergency Rovers Check-Up Queue;
	LinkedQueue<Rover*>* PRCH = new LinkedQueue<Rover*>(); //Polar Rovers Check-Up Queue;


	PriorityQueue<Rover*>* RIE = new PriorityQueue<Rover*>(); //Rovers executing missions

	MarsStation();

	//functions
	bool NeedsCheckUp(Rover* R); //sends rover to Check-Up if needed. Returns true if rover went to checkup and false if it did not need to
	void ReturnFromCheckUp(); //Checks if there are rovers that finished checkup and gets them back
	Rover* GetEmergencyRover();
	Rover* GetPolarRover();
	void Assign_M_to_R(PriorityQueue<Mission*>*& EM, PriorityQueue<Mission*>*& PM, PriorityQueue<Rover*>*& ER, PriorityQueue<Rover*>*& PR, PriorityQueue<Mission*>*& WL);
	void UI_file();
};