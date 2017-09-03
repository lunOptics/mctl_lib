#pragma once

#include "SimpleActuator.h"

class Arm;
class Motor;
class MctlEncoder;

class Base : public SimpleActuator
{
public:
	Base(Motor* motor, MctlEncoder* encoder) : SimpleActuator(motor, encoder) {};

	friend Arm;
};