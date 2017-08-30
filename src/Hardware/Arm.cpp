#include "Arm.h"
#include "AltEncoder.h"
#include "Ellbow.h"
#include "Wrist.h"
#include "PID_v1.h"

using namespace AltEncoder;

Arm::Arm(Wrist* _wrist, Ellbow* _ellbow)
{
	wrist = _wrist;
	ellbow = _ellbow;
		

//	// setup all PIDs and start regulating -----------------
//	constexpr int sampleTime = 1; //ms
//	//wrist->leftPID->SetSampleTime(sampleTime);
//	//wrist->rightPID->SetSampleTime(sampleTime);
//	ellbow->pid->SetSampleTime(sampleTime);
//	pidTimer = new IntervalTimer();
//	pidTimer->begin(pidISR, sampleTime * 1000);
}


Wrist* Arm::wrist;
Ellbow* Arm::ellbow;




////float m_Kp = 0.9, m_Ki = 0.0, m_Kd = 0.0;	// master: just move the motor, p only -> will not reach target, doesn't matter for this experiment
//float m_Kp = 5000, m_Ki = 0, m_Kd = 5;  // slave: try to follow master as close as possible, note: settings are close to instable
//float s_Kp = 2000, s_Ki = 5000, s_Kd = 5;  // slave: try to follow master as close as possible, note: settings are close to instable
//
//PID pidLeft(&masterInput, &masterOutput, &masterTarget, m_Kp / 1000.0, m_Ki / 1000.0, m_Kd / 1000.0, DIRECT);
//PID pidRight(&slaveInput, &slaveOutput, &slaveTarget, s_Kp / 1000.0, s_Ki / 1000.0, s_Kd / 1000.0, DIRECT);
