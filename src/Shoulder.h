#pragma once

#include "SimpleActuator.h"


class Shoulder : public SimpleActuator
{
public:
	Shoulder(Motor* motor, MctlEncoder* encoder) : SimpleActuator(motor, encoder) {};
};