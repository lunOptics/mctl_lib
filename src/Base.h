#pragma once

#include "Module.h"

class Arm;
class Motor;
class mctlEncoder;

class Base : public Module
{
public:
	Base(Motor* motor, mctlEncoder* encoder) : Module(motor, encoder) {};

	friend Arm;
};