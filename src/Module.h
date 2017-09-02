#pragma once
//#include "core_pins.h"
#include "mctlEncoder.h"
#include "Motor.h"
#include "mctlPID.h"
#include "Module.h"

#include "usb_serial.h"

class Arm;
class PID;
//class Motor;


class mctlEncoder;
class Controller;


class Module
{
public:
	Module(Motor*, mctlEncoder*);

	virtual void setPidParameters(float kP, float kD, float kI, float limitLow, float limitHigh);

	void rotateTo(float angle, float speed);

	mctlEncoder* encoder;
	PID* pid;
	float pidOutput, pidInput, target;


	Motor* motor;

	inline void calcPID()
	{
		pidInput = encoder->counter;
		pid->Compute();
		motor->setPWM(pidOutput);
	}

};

