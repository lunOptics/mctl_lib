#pragma once

#include "Wrist.h"
#include "Ellbow.h"

class IntervalTimer;

namespace AltEncoder { class Encoder; class Controller; }
class PID;
class IntervalTimer;


class Arm
{
public:
	Arm(Wrist* wrist, Ellbow* ellbow);	

	static Wrist* wrist;
	static Ellbow* ellbow;
	
private:	

	IntervalTimer* pidTimer;

	inline static void pidISR()
	{
		wrist->calcPID();
		ellbow->calcPID();
	}

};

