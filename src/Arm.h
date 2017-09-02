#pragma once

#include "Base.h"
#include "Shoulder.h"
#include "Wrist.h"
#include "Ellbow.h"

class IntervalTimer;

namespace AltEncoder { class mctlEncoder; class Controller; }
class PID;
class IntervalTimer;


class Arm
{
public:
	Arm(Base*, Shoulder*,  Ellbow*, Wrist*);

	void pidOn();
	void pidOff();

	static Base* base;
	static Shoulder* shoulder;
	static Ellbow* ellbow;
	static Wrist* wrist;


private:

	IntervalTimer* pidTimer;

	inline static void pidISR()
	{
		//wrist->calcPID();
		base->calcPID();
		shoulder->calcPID();
		ellbow->calcPID();
		//wrist->calcPID();
	}

	static constexpr int sampleTime = 1; //ms

};

