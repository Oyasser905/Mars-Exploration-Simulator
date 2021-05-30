#pragma once

class MarsStation
{
public:
	PriorityQueue<Rover*>* ER = new PriorityQueue<Rover*>(); //Emergency Rovers Priority Queue
	PriorityQueue<Rover*>* PR = new PriorityQueue<Rover*>(); //Polar Rovers Priority Queue

	PriorityQueue<Mission*>* EM = new PriorityQueue<Mission*>(); //Emergency Missions Priority Queue
	PriorityQueue<Mission*>* PM = new PriorityQueue<Mission*>(); //Polar Missions Priority Queue

	PriorityQueue<Mission*>* WL = new PriorityQueue<Mission*>(); //Waiting list Priority Queue

	MarsStation();
	void Assign_M_to_R(PriorityQueue<Mission*>*& EM, PriorityQueue<Mission*>*& PM, PriorityQueue<Rover*>*& ER, PriorityQueue<Rover*>*& PR, PriorityQueue<Mission*>*& WL);

};