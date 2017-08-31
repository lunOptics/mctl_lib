#pragma once


#include "core_pins.h"
#include "AltEncoder.h"
#include "Motor.h"
#include "PID_v1.h"

class Arm;
class PID;
class Motor;

namespace AltEncoder
{
	class Encoder;
	class Controller;
}

class Shoulder
{
public:
	Shoulder(Motor* motor, AltEncoder::Encoder* encoder);
	
public:
	AltEncoder::Encoder* encoder;

	PID* pid;
	float output, input, target;

	inline void calcPID()
	{
		input = encoder->counter;
		pid->Compute();
		motor->setPWM(output);
	}

	Motor* motor;

	friend Arm;
};

