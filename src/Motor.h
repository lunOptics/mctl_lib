#pragma once


// Abstraction of a motor
// Allows to switch motor types without touching high level code

class Motor
{
public:
	virtual void setSpeed(int speed) = 0;
};