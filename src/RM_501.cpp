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

void RM_501::moveAcc(uint32_t targett, int maxSpeed, unsigned acc)
{    
    unsigned vMin = 10;
    float v = maxSpeed;
    float a = acc;
    float tgt = targett; 

    float ae, ds;
   
    if (v == 0) return;
        
    if (v > vMin) // acceleration required
    {
        float dv = v - vMin;
        ae = dv * dv / (2.0f * a);  // length of acceleration phase
     //   Serial.println(ae);

      //  if (ae > std::numeric_limits<uint32_t>::max()) return;  ///TBD Add error handling

        if (ae > tgt / 2.0f)
        {
            ae = tgt / 2.0f;
        }

      
        ds = tgt - ae;

     //   sqrt_2a = sqrtf(a * 2.0f);
    }
    else  // constant velocity, no acceleration necessary
    {
        ae = 0;
        ds = tgt;     
    }
       
    Serial.printf("ae %f, ds %f\n", ae, ds);

    shoulder->a = a;
    shoulder->v = v;
    shoulder->ae = ae;
    shoulder->ds = ds;
    shoulder->target = tgt;
}

//void Arm::syncMoveAbsolute(int baseTarget, int shoulderTarget, int EllbowTarget)
//{
//	TBD//
//}



Base* RM_501::base;
Shoulder* RM_501::shoulder;
Wrist* RM_501::wrist;
Ellbow* RM_501::ellbow;


