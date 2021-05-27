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
	int status;
	int weight;
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
	void setStatus(int s);

	//getters
	int getID();
	int getDay();
	char getType();
	int getTargetLocation();
	int getDuration();
	int getSignificance();
	int getStatus();
	int getWeight();

	//member functions
	int calcWeight();
};