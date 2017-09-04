#pragma once

#include "mctlEncoder.h"
#include "Motor.h"
#include "mctlPID.h"
#include "wiring.h"

class DifferentialActuator
{
public:
	DifferentialActuator(Motor* motor1, Motor* motor2, MctlEncoder* encoder1, MctlEncoder* encoder2);

	virtual void setPidParameters(float kP, float kD, float kI, float limitLow, float limitHigh);
	virtual void setMaxSpeed(float stepsPerSecond) { maxSpeed = max(0.0f, min(10000.0f, stepsPerSecond)); }
	inline bool isMoving() { return pidTarget1 != movementTarget1 || pidTarget2 != movementTarget2; }
	inline void calcPID()
	{
		if (movementTarget1 - pidTarget1 >= moveDelta1)
		{
			pidTarget1 += moveDelta1;
		}
		else if (pidTarget1 - movementTarget1 >= moveDelta1)
		{
			pidTarget1 -= moveDelta1;
		}
		else
		{
			pidTarget1 = movementTarget1;
		}

		pidInput1 = encoder1->counter;
		

		//---------------------------

		if (movementTarget2 - pidTarget2 >= moveDelta2)
		{
			pidTarget2 += moveDelta2;
		}
		else if (pidTarget2 - movementTarget2 >= moveDelta2)
		{
			pidTarget2 -= moveDelta2;
		}
		else
		{
			pidTarget2 = movementTarget2;
		}

		pidInput2 = encoder2->counter;

		//-----------------------------

		pid1->Compute();
		pid2->Compute();
		motor1->setPWM(pidOutput1);
		motor2->setPWM(pidOutput2);
	}

	//private:

	Motor *motor1, *motor2;
	MctlEncoder *encoder1, *encoder2;
	PID *pid1, *pid2;
	float pidOutput1, pidInput1, pidTarget1;
	float pidOutput2, pidInput2, pidTarget2;

	float moveDelta1 = 0, movementTarget1 = 0;
	float moveDelta2 = 0, movementTarget2 = 0;
	float maxSpeed = 5000;
};


