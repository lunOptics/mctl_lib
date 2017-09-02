#pragma once


#include "Module.h"

class Arm;
class Motor;
class mctlEncoder;


class Ellbow : public Module
{
public:
	Ellbow(Motor* motor, mctlEncoder* encoder) : Module(motor, encoder) {};

	friend Arm;
};

