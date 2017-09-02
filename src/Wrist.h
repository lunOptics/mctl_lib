#pragma once

class Arm;
class PID;
class Motor;

class mctlEncoder;
class Controller;


class Wrist
{
public:
	Wrist(Motor* leftMotor, Motor* rightMotor, mctlEncoder* leftEncoder, mctlEncoder* rightEncoder);

	//private:
public:
	Motor* leftMotor;
	Motor* rightMotor;
	mctlEncoder* leftEncoder;
	mctlEncoder* rightEncoder;

	float outLeft, outRight, inLeft, inRight, targetLeft, targetRight;
	PID* leftPID;
	PID* rightPID;

	inline void calcPID()
	{
		//tbd
	}

	friend Arm;
};


