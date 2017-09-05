#pragma once

#include "Modules/Base.h"
#include "Modules/Shoulder.h"
#include "Modules/Ellbow.h"
#include "Modules/Wrist.h"

class IntervalTimer;

class MctlEncoder; class Controller;
class PID;
class IntervalTimer;


class RM_501
{
public:
	RM_501(Base*, Shoulder*, Ellbow*, Wrist*);

	void pidOn();
	void pidOff();

	static Base* base;
	static Shoulder* shoulder;
	static Ellbow* ellbow;
	static Wrist* wrist;

	inline bool isMoving() { return base->isMoving() || shoulder->isMoving() || ellbow->isMoving() || wrist->isMoving(); }

	void moveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget,int wristRotTarget, int wristTiltTarget);
	void waitMoveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget, int wristRotTarget, int wristTiltTarget);
	//	void syncMoveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget);


private:

	IntervalTimer* pidTimer;

	inline static void pidISR()
	{
		base->calcPID();
		shoulder->calcPID();
		ellbow->calcPID();
		wrist->calcPID();
	}

	static constexpr int sampleTime = 1; //ms

};

