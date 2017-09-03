#include "Arm.h"
#include "Base.h"
#include "Shoulder.h"
#include "Ellbow.h"
#include "Wrist.h"

#include "mctlEncoder.h"
#include "mctlPID.h"



//#include "Arduino.h"



Arm::Arm(Base* _base, Shoulder* _shoulder, Ellbow* _ellbow, Wrist* _wrist)
{
	base = _base;
	shoulder = _shoulder;
	wrist = _wrist;
	ellbow = _ellbow;

	base->pid->SetSampleTime(sampleTime);
	shoulder->pid->SetSampleTime(sampleTime);
	ellbow->pid->SetSampleTime(sampleTime);
	//wrist->pid->SetSampleTime(sampleTime);

	pidTimer = new IntervalTimer();
}

void Arm::pidOn()
{
	pidTimer->begin(pidISR, sampleTime * 1000);
}

void Arm::pidOff()
{
	pidTimer->end();
}

void Arm::moveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget)
{
	base->moveDelta = 0.001*sampleTime * base->maxSpeed;
	base->movementTarget = baseTarget;

	shoulder->moveDelta = 0.001*sampleTime * shoulder->maxSpeed;
	shoulder->movementTarget = shoulderTarget;

	ellbow->moveDelta = 0.001*sampleTime *ellbow->maxSpeed,
	ellbow->movementTarget = EllbowTarget;
}

//void Arm::syncMoveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget)
//{
//	TBD//
//}



Base* Arm::base;
Shoulder* Arm::shoulder;
Wrist* Arm::wrist;
Ellbow* Arm::ellbow;


