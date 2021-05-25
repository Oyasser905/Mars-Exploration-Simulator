#pragma once
#include<iostream>
using namespace std;

class Rover
{
private:
	char R_type;
	int speed;
	int checkupDuration;
	char R_status;
public:
	//constructors
	Rover();
	Rover(char t, int sp, int ch, char st);
	//setters
	void setType(char t);
	void setSpeed(int s);
	void setCheckupDuration(int ch);
	void setStatus(char s);

	//getters
	char getType();
	int getSpeed();
	int getCheckupDuration();
	char getStatus();
};