#pragma once

class Arm;
class PID;
class Motor;

class MctlEncoder;
class Controller;


class Wrist
{
public:
	Wrist(Motor* leftMotor, Motor* rightMotor, MctlEncoder* leftEncoder, MctlEncoder* rightEncoder);

	//private:
public:
	Motor* leftMotor;
	Motor* rightMotor;
	MctlEncoder* leftEncoder;
	MctlEncoder* rightEncoder;

	float outLeft, outRight, inLeft, inRight, targetLeft, targetRight;
	PID* leftPID;
	PID* rightPID;

	inline void calcPID()
	{
		//tbd
	}

	friend Arm;
};


