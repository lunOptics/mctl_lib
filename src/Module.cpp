#include "Module.h"
#include "AltEncoder.h"
#include "PID_v1.h"

using namespace AltEncoder;

Module::Module(Motor* motor, Encoder* encoder)
	:encoder(encoder), motor(motor)
{
	pid = new PID(&pidInput, &pidOutput, &target, 1, 0, 0, DIRECT);
	pid->SetMode(AUTOMATIC);
	
	encoder->counter = 0;
	target = 0;
}


void Module::setPidParameters(float kP, float kD, float kI, float limitLow, float limitHigh)
{
	pid->SetTunings(kP, kD, kI);
	pid->SetOutputLimits(limitLow, limitHigh);
}


void Module::rotateTo(float angle, float speed)
{
	if (angle > target)
	{
		while (angle > target)
		{
			target = (int)(target + speed / 1000.0);
			delay(1);
		}
	}
	else
	{
		while (angle < target)
		{
			target = (int)(target - speed / 1000.0);
			delay(1);
		}
	}
}
