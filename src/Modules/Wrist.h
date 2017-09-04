#pragma once

#include "Actuators\DifferentialActuator.h"

class RM_501;
class PID;
class Motor;

class MctlEncoder;
class Controller;


class Wrist : public DifferentialActuator
{
public:
	Wrist(Motor* leftMotor, Motor* rightMotor, MctlEncoder* leftEncoder, MctlEncoder* rightEncoder)
		:DifferentialActuator(leftMotor, rightMotor, leftEncoder, rightEncoder)
	{}

	friend RM_501;
};


