#pragma once

#include "core_pins.h"
#include "Motor.h"

class MitchsMotor : public Motor
{
public:
	MitchsMotor(unsigned _upPin, unsigned _downPin)
		:upPin(_upPin), downPin(_downPin)
	{
		pinMode(upPin, OUTPUT);
		pinMode(downPin, OUTPUT);
	}
	
	/// Set raw motor speed (PWM output) in the range from -256...256	
	inline void setPWM(int speed)
	{
		if (speed > 0)
		{
			if (speed > 256) speed = 256; 
			analogWrite(downPin, 256);
			analogWrite(upPin, 256 - speed);  
		}
		else
		{
			if (speed < -256) speed = -256;
			analogWrite(upPin, 256 + speed);  
			analogWrite(downPin, 256); 
		}
	}

private:
	const unsigned upPin, downPin;
};
