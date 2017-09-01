#include "Arm.h"
#include "AltEncoder.h"
#include "Base.h"
#include "Shoulder.h"
#include "Ellbow.h"
#include "Wrist.h"

#include "PID_v1.h"

#include "Arduino.h"

using namespace AltEncoder;

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



Base* Arm::base;
Shoulder* Arm::shoulder;
Wrist* Arm::wrist;
Ellbow* Arm::ellbow;


