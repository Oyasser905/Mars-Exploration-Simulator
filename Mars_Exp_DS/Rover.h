#pragma once
#include<iostream>
using namespace std;

class Rover
{
private:
	char R_type;
	int speed;
	int checkupDuration;
public:
	//setters
	void setType(char t);
	void setSpeed(int s);
	void setCheckupDuration(int ch);

	//getters
	char getType();
	int getSpeed();
	int getCheckupDuration();
};