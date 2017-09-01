#include "Ellbow.h"
#include "AltEncoder.h"
#include "PID_v1.h"

using namespace AltEncoder;



//Ellbow::Ellbow(int out,  int encA, int encB)
//	:outPin(out)
//{
//	/*encoder = new Encoder(encA, encB);
//	pid = new PID(&input, &output, &target, 4, 0.5, 0.005, DIRECT);
//	pid->SetMode(AUTOMATIC);
//	pid->SetOutputLimits(-100, 100);
//	
//	encoder->counter = 0;
//	target = 0;
//
//	pinMode(outPin, OUTPUT);
//
//	motor.begin();	*/
//}

Ellbow::Ellbow(Motor* _motor, Encoder* _encoder)
	:encoder(_encoder), motor(_motor)
{
	pid = new PID(&pidInput, &pidOutput, &target, 1, 0, 0, DIRECT);
	pid->SetMode(AUTOMATIC);
	//pid->SetOutputLimits(-20, 20);

	encoder->counter = 0;
	target = 0;

}

void Ellbow::setPidParameters(float kP, float kD, float kI, float limitLow, float limitHigh)
{
	pid->SetTunings(kP, kD, kI);
	pid->SetOutputLimits(limitLow, limitHigh);
}


void Ellbow::rotateTo(float angle, float speed)
{
	if (angle > target)
	{
		while (angle > target)
		{
			target =(int)(target+ speed / 1000.0);
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
