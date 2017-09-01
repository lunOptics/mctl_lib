#pragma once

#include "AltEncoder.h"
#include "Module.h"

class Arm;
class Motor;

class Base : public Module
{
public:
	Base(Motor* motor, AltEncoder::Encoder* encoder) : Module(motor, encoder) {};

	friend Arm;
};