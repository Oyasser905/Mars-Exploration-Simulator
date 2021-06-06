#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Mission.h"
#include "Rover.h"
#include "FormulationEvent.h"
#include "priorityQueue.h"
#include "Queue.h"
using namespace std;

class MarsStation;


class UI
{
	int num_pr; //No. of polar rovers
	int num_er; //No. of emergency rovers

	int pr_sp; //Polar rover speed
	int er_sp; //Emergency rover speed

	int num_missions; //No. of missions before check up
	int pr_ch; //Polar check up duration
	int er_ch; //Emergency check up duration

	int no_events; //No. of events
	int mode;
	MarsStation* obj;

public:
	UI(MarsStation*);
	void input_contents_console(string i_file);
	void r_input();
	void Interactive_mode();
	void SbS_mode();
	void Silent_mode();
	void w_file();
	void p_output();
	void chooseMode();
};