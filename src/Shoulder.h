#pragma once

#include "Module.h"

class Arm;
class Motor;
class mctlEncoder;

class Shoulder : public Module
{
public:
	Shoulder(Motor* motor, mctlEncoder* encoder) : Module(motor, encoder) {};

	friend Arm;
};