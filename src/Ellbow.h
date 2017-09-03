#pragma once

#include "SimpleActuator.h"

class Ellbow : public SimpleActuator
{
public:
	Ellbow(Motor* motor, MctlEncoder* encoder) : SimpleActuator(motor, encoder) {};

	friend Arm;
};

