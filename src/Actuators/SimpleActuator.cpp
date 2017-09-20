#include "SimpleActuator.h"

SimpleActuator::SimpleActuator(Motor* motor, MctlEncoder* encoder)
	: motor(motor), encoder(encoder)
{
	pid = new PID(&pidInput, &pidOutput, &pidTarget, 1, 0, 0, DIRECT);
	pid->SetMode(AUTOMATIC);
	
	encoder->counter = 0;
	pidTarget = 0;
}

void SimpleActuator::setPidParameters(float kP, float kD, float kI, float limitLow, float limitHigh)
{
	pid->SetTunings(kP, kD, kI);
	pid->SetOutputLimits(limitLow, limitHigh);
}

void SimpleActuator::moveAcc(int32_t targett, unsigned maxSpeed, unsigned acc)
{
    encoder->counter = 0; 
    pidTarget = 0; 

    target = targett;
    v = maxSpeed;
    a = acc;
    unsigned vMin = 10;
  
    if (v == 0) return;

    if (v > vMin) // acceleration required
    {
        float dv = v - vMin;
        ae = dv * dv / (2.0f * a);  // length of acceleration phase
                                    //   Serial.println(ae);

       //  if (ae > std::numeric_limits<uint32_t>::max()) return;  ///TBD Add error handling

        if (ae > fabs(target) / 2.0f)
        {
            ae = fabs(target) / 2.0f;
        }

        ds = fabs(target) - ae;

        //   sqrt_2a = sqrtf(a * 2.0f);
    }
    else  // constant velocity, no acceleration necessary
    {
        ae = 0;
        ds = fabs(target);
    }

   // Serial.printf("ae %f, ds %f\n", ae, ds);
        
    
}


