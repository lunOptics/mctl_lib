#pragma once

#include "..\Actuators\SimpleActuator.h"

class RM_501;
class Motor;
class MctlEncoder;

class Base : public SimpleActuator
{
public:
	Base(Motor* motor, MctlEncoder* encoder) : SimpleActuator(motor, encoder) {};

	friend RM_501;
};