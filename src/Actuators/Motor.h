#pragma once


// Abstraction of a motor
// Allows to switch motor types without touching high level code

class Motor
{
public:
	virtual void setPWM(int speed) = 0;
};