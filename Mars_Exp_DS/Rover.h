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
	int no_check; //No. of missions before check up 
public:
	//constructors
	Rover();
	Rover(char t, int sp, int ch, int n);
	//setters
	void setType(char t);
	void setSpeed(int s);
	void setCheckupDuration(int ch);
	void setStatus(char s);
	void setNo_Check(int n);

	//getters
	char getType();
	int getSpeed();
	int getCheckupDuration();
	char getStatus();
	int getNo_Check();
};