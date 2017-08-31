#pragma once

#include "Base.h"
#include "Shoulder.h"
#include "Wrist.h"
#include "Ellbow.h"

class IntervalTimer;

namespace AltEncoder { class Encoder; class Controller; }
class PID;
class IntervalTimer;


class Arm
{
public:
	Arm(Base*, Shoulder* _shoulder, Wrist* wrist, Ellbow* ellbow);

	static Base* base;
	static Shoulder* shoulder;
	static Ellbow* ellbow;
	static Wrist* wrist;

private:

	IntervalTimer* pidTimer;

	inline static void pidISR()
	{
		wrist->calcPID();
		ellbow->calcPID();
	}

};

