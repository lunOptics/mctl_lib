#pragma once

#include "../Actuators/SimpleActuator.h"

class Ellbow : public SimpleActuator
{
public:
	Ellbow(Motor* motor, MctlEncoder* encoder) : SimpleActuator(motor, encoder) {};

	friend RM_501;
};

