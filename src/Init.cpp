#include "init.h"
#include "arm.h"
#include "Ellbow.h"
#include "Wrist.h"
#include "AltEncoder.h"
#include "MaxonMot.h"
#include "MitchsMotor.h"

using namespace AltEncoder;

//------------------------------
// Select used pinouts here
//------------------------------

//#define MITCHS_SETUP
#define LUNIS_SETUP

Arm* arm;

void setupMisc()
{
	Serial.begin(0);
	pinMode(LED_BUILTIN, OUTPUT);
}

void setupArm()
{

#if defined(MITCHS_SETUP)
	// Adjust to your pin settings here

	Motor* motEllbow = new MitchsMotor(37, 38);
	Motor* motWristLeft = new MitchsMotor(7, 6);
	Motor* motWristRight = new MitchsMotor(9, 8);

	Encoder* encEllbow = new Encoder(33, 34);
	Encoder* encWristLeft = new Encoder(27, 26);
	Encoder* encWristRight = new Encoder(30, 31);

#elif defined(LUNIS_SETUP)		

	Motor* motEllbow = nullptr;
	auto* motWristLeft = new MaxonMotor<5, 7>();
	auto* motWristRight = new MaxonMotor<10, 12>();

	motWristLeft->begin();
	motWristRight->begin();

	Encoder* encEllbow = new Encoder(33, 34);
	Encoder* encWristLeft = new Encoder(14, 15);
	Encoder* encWristRight = new Encoder(16, 17);

#else
#error "Please define a valid setup in init.h"
#endif

	Wrist* wrist = new Wrist(motWristLeft, motWristRight, encWristLeft, encWristRight);
	Ellbow* ellbow = new Ellbow(motEllbow, encEllbow);

	arm = new Arm(wrist, ellbow);

	//setup the encoder controller
	Encoder** encList = new Encoder*[4]
	{
		encEllbow,
		encWristLeft,
		encWristRight,
		nullptr,
	};
	(new Controller())->begin(encList, 25);
}

