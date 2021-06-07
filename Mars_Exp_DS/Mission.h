#pragma once
#include<iostream>
using namespace std;

class Mission 
{
private:
	int ID;
	int day;
	char type;
	int targetLocation;
	int duration;
	int significance;
	char status; //I : In-Execution    C: Completed    W: Waiting    N: Not assigned
	int weight;
	int ED;
	int WD; 
	int CD;
public:
	//constructors
	Mission();
	Mission(char t, int d, int id, int tloc, int dur, int sig);
	//setters
	void setID(int id);
	void setDay(int d);
	void setType(char t);
	void setTargetLocation(int tloc);
	void setDuration(int dur);
	void setSignificance(int sig);
	void setStatus(char s);
	void setExecutionDays(int S);
	void setWaitingDays(int W);
	void setCompletedDay(int C);

	//getters
	int getID();
	int getDay();
	char getType();
	int getTargetLocation();
	int getDuration();
	int getSignificance();
	char getStatus();
	int getWeight();
	int getExecutionDays();
	int getWaitingDays();
	int getCompletedDay();

	//member functions
	int calcWeight();
};