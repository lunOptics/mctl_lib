#pragma once

class Arm;
class PID;
class Motor;


namespace AltEncoder
{
	class Encoder;
	class Controller;
}

class Wrist
{
public:
	Wrist(Motor* leftMotor, Motor* rightMotor, AltEncoder::Encoder* leftEncoder, AltEncoder::Encoder* rightEncoder);

	//private:
public:
	Motor* leftMotor;
	Motor* rightMotor;
	AltEncoder::Encoder* leftEncoder;
	AltEncoder::Encoder* rightEncoder;

	float outLeft, outRight, inLeft, inRight, targetLeft, targetRight;
	PID* leftPID;
	PID* rightPID;

	inline void calcPID()
	{
		//tbd
	}

	friend Arm;
};


