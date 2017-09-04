#include "RM_501.h"
#include "Modules\Base.h"
#include "Modules\Shoulder.h"
#include "Modules\Ellbow.h"
#include "Modules\Wrist.h"


#include "mctlEncoder.h"
#include "mctlPID.h"



//#include "Arduino.h"



RM_501::RM_501(Base* _base, Shoulder* _shoulder, Ellbow* _ellbow, Wrist* _wrist)
{
	base = _base;
	shoulder = _shoulder;
	wrist = _wrist;
	ellbow = _ellbow;

	base->pid->SetSampleTime(sampleTime);
	shoulder->pid->SetSampleTime(sampleTime);
	ellbow->pid->SetSampleTime(sampleTime);
	wrist->pid1->SetSampleTime(sampleTime);
	wrist->pid2->SetSampleTime(sampleTime);

	pidTimer = new IntervalTimer();
}

void RM_501::pidOn()
{
	pidTimer->begin(pidISR, sampleTime * 1000);
}

void RM_501::pidOff()
{
	pidTimer->end();
}

void RM_501::moveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget, int wristRotTarget, int wristTiltTarget)
{
	base->moveDelta = 0.001*sampleTime * base->maxSpeed;
	base->movementTarget = baseTarget;

	shoulder->moveDelta = 0.001*sampleTime * shoulder->maxSpeed;
	shoulder->movementTarget = shoulderTarget;

	ellbow->moveDelta = 0.001*sampleTime *ellbow->maxSpeed;
	ellbow->movementTarget = EllbowTarget;

	wrist->moveDelta1 = 0.001*sampleTime * wrist->maxSpeed;
	wrist->moveDelta2 = 0.001*sampleTime * wrist->maxSpeed;

	wrist->movementTarget1 = wristTiltTarget + wristRotTarget;
	wrist->movementTarget2 = wristTiltTarget- wristRotTarget;

}

void RM_501::waitMoveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget, int wristRotTarget, int wristTiltTarget)
{
	moveAbsolute(baseTarget, shoulderTarget, EllbowTarget, wristRotTarget, wristTiltTarget);
	while (isMoving())
	{
		delay(10);
	}
}

//void Arm::syncMoveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget)
//{
//	TBD//
//}



Base* RM_501::base;
Shoulder* RM_501::shoulder;
Wrist* RM_501::wrist;
Ellbow* RM_501::ellbow;


