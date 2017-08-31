#include "Shoulder.h"

using namespace AltEncoder;

Shoulder::Shoulder(Motor* _motor, Encoder* _encoder)
	:encoder(_encoder), motor(_motor)
{
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