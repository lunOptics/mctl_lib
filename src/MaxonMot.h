#pragma once
#include "Arduino.h"
#include "Motor.h"

// Motor: Maxon 2008808, with included encoders (400 cts/rev)
// Motors driven by to TLE52005 Bridges, 12V

template<int in1, int in2>
class MaxonMotor : public Motor
{
public:
	virtual void setSpeed(int s)
	{
		speed = s;
	}
	static void begin()
	{
		pinMode(in1, OUTPUT);
		pinMode(in2, OUTPUT);

		cnt = 0;
		speed = 0;
		timer.begin(isr, 5);
	}

private:
	static int32_t speed;
	static constexpr int maxSpeed = 150;

	static void isr()
	{
		if (cnt < (speed < 0 ? -speed : speed))
		{
			digitalWriteFast(in1, LOW);
			digitalWriteFast(in2, speed > 0 ? 1 : 0);
		}
		else
		{
			digitalWriteFast(in1, HIGH);
			digitalWriteFast(in2, HIGH);
		}
		cnt = (cnt + 1) % maxSpeed;
	}

	static IntervalTimer timer;
	static int cnt;
};



template<int i1, int i2>
int32_t MaxonMotor<i1, i2>::speed = 0;

template<int i1, int i2>
IntervalTimer MaxonMotor<i1, i2>::timer;

template<int i1, int i2>
int MaxonMotor<i1, i2>::cnt = 0;








