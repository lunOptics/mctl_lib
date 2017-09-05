#include "DifferentialActuator.h"



DifferentialActuator::DifferentialActuator(Motor* m1, Motor* m2, MctlEncoder* e1, MctlEncoder* e2)
	: motor1(m1), motor2(m2),encoder1(e1), encoder2(e2)
{
	pid1 = new PID(&pidInput1, &pidOutput1, &pidTarget1, 1, 0, 0, DIRECT);
	pid1->SetMode(AUTOMATIC);

	pid2 = new PID(&pidInput2, &pidOutput2, &pidTarget2, 1, 0, 0, DIRECT);
	pid2->SetMode(AUTOMATIC);


	encoder1->counter = 0;
	encoder2->counter = 0;
	pidTarget1 = 0.0f;
	pidTarget2 = 0.0f;
}


void DifferentialActuator::setPidParameters(float kP, float kD, float kI, float limitLow, float limitHigh)
{
	pid1->SetTunings(kP, kD, kI);
	pid1->SetOutputLimits(limitLow, limitHigh);

	pid2->SetTunings(kP, kD, kI);
	pid2->SetOutputLimits(limitLow, limitHigh);
}


