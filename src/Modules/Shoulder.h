#pragma once

#include "../Actuators/SimpleActuator.h"


class Shoulder : public SimpleActuator
{
public:
	Shoulder(Motor* motor, MctlEncoder* encoder) : SimpleActuator(motor, encoder) {};
};