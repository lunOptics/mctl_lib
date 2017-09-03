#pragma once

#include "Base.h"
#include "Shoulder.h"
#include "Wrist.h"
#include "Ellbow.h"

class IntervalTimer;

class MctlEncoder; class Controller;
class PID;
class IntervalTimer;


class Arm
{
public:
	Arm(Base*, Shoulder*, Ellbow*, Wrist*);

	void pidOn();
	void pidOff();

	static Base* base;
	static Shoulder* shoulder;
	static Ellbow* ellbow;
	static Wrist* wrist;

	inline bool isMoving() { return base->isMoving() || shoulder->isMoving() || ellbow->isMoving(); }

	void moveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget);
	//	void syncMoveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget);


private:

	IntervalTimer* pidTimer;

	inline static void pidISR()
	{
		base->calcPID();
		shoulder->calcPID();
		ellbow->calcPID();
		//wrist->calcPID();
	}

	static constexpr int sampleTime = 1; //ms

};

