#pragma once
//#include "core_pins.h"
#include "AltEncoder.h"
#include "Motor.h"
#include "PID_v1.h"
#include "Module.h"

#include "usb_serial.h"

class Arm;
class PID;
//class Motor;

namespace AltEncoder
{
	class Encoder;
	class Controller;
}

class Module
{
public:
	Module(Motor*, AltEncoder::Encoder*);

	virtual void setPidParameters(float kP, float kD, float kI, float limitLow, float limitHigh);

	void rotateTo(float angle, float speed);

	AltEncoder::Encoder* encoder;
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

