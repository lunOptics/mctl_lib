#include <arduino.h>

#include "Hardware\Init.h"


IntervalTimer displayTimer;

void displayISR()
{
	int cnt = arm->wrist->leftEncoder->counter;
	Serial.printf("%d\t%d\n", millis(), cnt);
}


void setup()
{
	setupMisc();
	setupArm();

	Serial.println("Start");
	displayTimer.begin(displayISR, 100000);

	arm->wrist->leftMotor->setSpeed(50);
	arm->wrist->rightMotor->setSpeed(50);
	delay(2000);

	arm->wrist->leftMotor->setSpeed(-50);
	arm->wrist->rightMotor->setSpeed(-50);
	delay(2000);

	arm->wrist->leftMotor->setSpeed(0);
	arm->wrist->rightMotor->setSpeed(0);
}


void loop()
{
	digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
	delay(250);	
}

