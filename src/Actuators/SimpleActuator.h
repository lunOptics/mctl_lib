#pragma once
#include "mctlEncoder.h"
#include "Motor.h"
#include "mctlPID.h"
#include "wiring.h"
#include "math.h"

//#include "usb_serial.h"

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

        float vcur = 0;

        if (pidTarget < ae)
        {
            vcur = sqrtf(2.0*a*pidTarget+10);
        }
        else if (pidTarget < ds)
        {
            vcur = v;
        }
        else if (pidTarget < target)
        {
            vcur = sqrtf(2.0*a*(target - pidTarget));
        }
        else vcur = 0; 


        pidTarget += (vcur * 0.001f);

        /*if (movementTarget - pidTarget >= moveDelta)
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
    */
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


    unsigned startTime = 0;
    int target = 0;
    float a = 0.0f;
    float v = 0.0f;
    unsigned ae, ds;
};

