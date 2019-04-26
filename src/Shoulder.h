#pragma once
//test

#include "AltEncoder.h"
#include "Module.h"

class Arm;
class Motor;

class Shoulder : public Module
{
public:
	Shoulder(Motor* motor, AltEncoder::Encoder* encoder) : Module(motor, encoder) {};

	friend Arm;
};
