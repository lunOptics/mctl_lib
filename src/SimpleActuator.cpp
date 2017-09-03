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


