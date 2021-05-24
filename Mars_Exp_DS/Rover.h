#pragma once
#include<iostream>
using namespace std;

class Rover
{
private:
	char type;
	int speed;
	int checkupDuration;
public:
	//setters
	void setType();
	void setSpeed();
	void setCheckupDuration();

	//getters
	void getType();
	void getSpeed();
	void getCheckupDuration();
};