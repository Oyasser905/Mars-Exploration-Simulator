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
public:
	//setters
	void setID();
	void setDay();
	void setType();
	void setTargetLocation();
	void setDuration();
	void setSignificance();
	void setStatus();

	//getters
	int getID();
	int getDay();
	char getType();
	int getTargetLocation();
	int getDuration();
	int getSignificance();
	int getStatus();

	//member functions
	int calcSignificance();
};