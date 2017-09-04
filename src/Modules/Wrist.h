#pragma once

#include "Actuators\DifferentialActuator.h"

class Wrist : public DifferentialActuator
{
public:
	Wrist(Motor* leftMotor, Motor* rightMotor, MctlEncoder* leftEncoder, MctlEncoder* rightEncoder)
		:DifferentialActuator(leftMotor, rightMotor, leftEncoder, rightEncoder)
	{}

	friend RM_501;
};


