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

class Base
{
public:
	Base(Motor* motor, AltEncoder::Encoder* encoder);

	//void rotateTo(int position, float speed);


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
	
	friend Arm;

	Motor* motor;
};

