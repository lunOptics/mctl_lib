#include "Wrist.h"
#include "mctlEncoder.h"
#include "mctlPID.h"



//Wrist::Wrist(int outL, int outR, int encLeftA, int encLeftB, int encRightA, int encRightB)
//	:outPinLeft(outL), outPinRight(outR)
//{
//	leftEncoder = new Encoder(encLeftA, encLeftB);
//	rightEncoder = new Encoder(encRightA, encRightB);
//
//	leftPID = new PID(&inLeft, &outLeft, &targetLeft, 0.0009, 0.0, 0.0, DIRECT);
//	rightPID = new PID(&inLeft, &outLeft, &targetLeft, 0.0009, 0.0, 0.0, DIRECT);
//}

Wrist::Wrist(Motor* leftM, Motor* rightM , MctlEncoder* leftE, MctlEncoder* rightE)
	:  leftMotor(leftM), rightMotor(rightM), leftEncoder(leftE), rightEncoder(rightE)
{	
	leftPID = new PID(&inLeft, &outLeft, &targetLeft, 0.0009, 0.0, 0.0, DIRECT);
	rightPID = new PID(&inLeft, &outLeft, &targetLeft, 0.0009, 0.0, 0.0, DIRECT);
}

