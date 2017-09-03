#pragma once

#include "IntervalTimer.h"
#include "core_pins.h"


class Controller;

//--------------------------------------------------------------------------------------------

class MctlEncoder
{
public:
	MctlEncoder(int pinA, int pinB, int mode = INPUT) : counter(0), _pinA(pinA), _pinB(pinB)
	{
		pinMode(_pinA, INPUT);
		pinMode(_pinB, INPUT);
	}
	volatile int counter;

private:
	const int _pinA, _pinB;
	unsigned last;

	friend Controller;
};

//--------------------------------------------------------------------------------------------

class Controller
{
public:

	static void begin(MctlEncoder** _encList, int t)
	{
		encList = _encList;
		timer.begin(isrEncoderRead, t);
		timer.priority(16);
	}

	static void isrEncoderRead(void)
	{
		int current;
		int diff;
		MctlEncoder** encoder = encList;

		while (*encoder != nullptr)
		{
			current = 0;
			if (digitalReadFast((*encoder)->_pinA)) current = 3;
			if (digitalReadFast((*encoder)->_pinB)) current ^= 1;
			diff = (*encoder)->last - current;
			if (diff & 1)
			{
				(*encoder)->last = current;
				(*encoder)->counter += (diff & 2) - 1;
			}
			encoder++;
		}
	}

private:
	static MctlEncoder** encList;
	static IntervalTimer timer;
};

