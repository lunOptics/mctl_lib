#include "Base.h"

using namespace AltEncoder;


Base::Base(Motor* _motor, Encoder* _encoder)
	:encoder(_encoder), motor(_motor)
{
	//pid = new PID(&input, &output, &target, 4, 0.5, 0.005, DIRECT);
	//pid->SetMode(AUTOMATIC);
	//pid->SetOutputLimits(-100, 100);

	encoder->counter = 0;
	target = 0;
}


//void Waist::rotateTo(float angle, float speed)
//{
//	/*if (angle > target)
//	{
//		while (angle > target)
//		{
//			target += speed / 1000.0;
//			delay(1);
//		}
//	}
//	else
//	{
//		while (angle < target)
//		{
//			target -= speed / 1000.0;
//			delay(1);
//		}
//	}*/
//}
