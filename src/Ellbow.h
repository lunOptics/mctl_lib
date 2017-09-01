#pragma once

#include "AltEncoder.h"
#include "Module.h"

class Arm;
class Motor;

class Ellbow : public Module
{
public:
	Ellbow(Motor* motor, AltEncoder::Encoder* encoder) : Module(motor, encoder) {};

	friend Arm;
};

