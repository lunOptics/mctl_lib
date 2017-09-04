#pragma once
#include "mctlEncoder.h"
#include "Motor.h"
#include "mctlPID.h"
#include "wiring.h"

class RM_501;

class SimpleActuator
{
public:
	SimpleActuator(Motor*, MctlEncoder*);

	virtual void setPidParameters(float kP, float kD, float kI, float limitLow, float limitHigh);
	virtual void setMaxSpeed(float stepsPerSecond) { maxSpeed = max(0.0f, min(10000.0f, stepsPerSecond)); }
	inline bool isMoving() { return pidTarget != movementTarget; }

	inline void calcPID()
	{
		if (movementTarget - pidTarget >= moveDelta)
		{
			pidTarget += moveDelta;
		}
		else if(pidTarget - movementTarget >= moveDelta)
		{
			pidTarget -= moveDelta;
		}
		else
		{
			pidTarget = movementTarget;
		}
	
		pidInput = encoder->counter;
		pid->Compute();
		motor->setPWM(pidOutput);
	}

//private:

	Motor* motor;
	MctlEncoder* encoder;
	PID* pid;
	float pidOutput, pidInput, pidTarget;
	float moveDelta = 0, movementTarget = 0;
	float maxSpeed = 5000;
};
