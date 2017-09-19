#include "RM_501.h"
#include "mctlEncoder.h"
#include "mctlPID.h"

#include <math.h>
#include <limits>
#include <algorithm>

#include "usb_serial.h"


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

void RM_501::moveAcc(uint32_t target, int maxSpeed, unsigned acc)
{    
    unsigned vMin = 0;
    uint32_t v = maxSpeed;
    uint32_t a = acc;
    this->target = target;
    if (v == 0) return;
        
    if (v > vMin) // acceleration required
    {
        float dv = v - vMin;
        float ae = dv * dv / (2.0f * a);  // length of acceleration phase

      //  if (ae > std::numeric_limits<uint32_t>::max()) return;  ///TBD Add error handling

        accelerationEnd = std::min((uint32_t)ae, target / 2);
        decelerationStart = target - accelerationEnd;

        sqrt_2a = sqrtf(a * 2.0f);
    }
    else  // constant velocity, no acceleration necessary
    {
        accelerationEnd = 0;
        decelerationStart = target;     
    }
       
    Serial.printf("ae %d, ds %d, sqrt %f", accelerationEnd, decelerationStart, sqrt_2a);

    shoulder->a = a;
    shoulder->v = v;
    shoulder->ae = sqrtf((2.0f*accelerationEnd)/a );
    shoulder->ds = 3 * shoulder->ae;
    shoulder->target = target;
}

//void Arm::syncMoveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget)
//{
//	TBD//
//}



Base* RM_501::base;
Shoulder* RM_501::shoulder;
Wrist* RM_501::wrist;
Ellbow* RM_501::ellbow;


