//Douglas Cantrell
//Feb 14, 2010, 12:20 PM
//FarZone1Autonomous.cpp
//Move forward until ball encountered. Shoot ball. Move to side for specified duration. Repeat.

#include "FarZone1Autonomous.h"
#define startDelay 0.0
#define fanStopDelay 0.0
#define leftDuration 1.5
#define bumpSafety 1.0
#define iterationCount 3

FarZone1Autonomous::FarZone1Autonomous() :
	pilot(), manip() {
	drive = Hardware::GetInstance()->GetRobotDrive();
	camera = Hardware::GetInstance()->GetCameraVision();
	sleepTest = false;
	firstTimeThrough = true;
	killDead = iterationCount;
}

FarZone1Autonomous::~FarZone1Autonomous() {
	delete drive;
	delete camera;
}

void FarZone1Autonomous::Init() {
	Hardware::GetInstance()->GetFanMotor()->Set(-1.0);
	Hardware::GetInstance()->GetKicker1()->Set(false);
	Hardware::GetInstance()->GetKicker2()->Set(true);
	Hardware::GetInstance()->GetPressureControl1()->Set(false);
	Hardware::GetInstance()->GetPressureControl2()->Set(true);
}

void FarZone1Autonomous::Periodic() {
}

void FarZone1Autonomous::Continuous() {
	if (firstTimeThrough == true)
		Wait(startDelay);
	if (killDead > 0) {	
		if (sleepTest == false)	{
			if (Hardware::GetInstance()->GetBallSwitch()->Get() == false) {
				if (bumpTimer.Get() < bumpSafety || firstTimeThrough == true) {
					drive->HolonomicDrive(0.5f,0.0f,0.0f);
					bumpTimer.Start();
					firstTimeThrough = false;
				}
				else
					drive->HolonomicDrive(0.0f,0.0f,0.0f);
			}
			else {
				if (penaltyTimer.Get() > 2.125 || killDead == iterationCount) {
					drive->HolonomicDrive(0.5f,0.0f,0.0f);
					Wait(0.1);
					manip.UseManip(true);
					Wait(0.1);
					penaltyTimer.Stop();
					penaltyTimer.Reset();
					sleepTest = true;
				}
				drive->HolonomicDrive(0.0f,0.0f,0.0f);
				bumpTimer.Stop();
				bumpTimer.Reset();
			}
		}
		else {
			Wait(0.375);
			manip.UseManip(false);
			penaltyTimer.Start();
			Hardware::GetInstance()->GetFanMotor()->Set(-1.0);
			sleepTest = false;
			killDead = killDead - 1;
			if (killDead > 0) {
				drive->HolonomicDrive(0.5f,-90.0f,0.0f);
				Wait(leftDuration);
			}
		}
	}
	else {
		drive->HolonomicDrive(0.0f,0.0f,0.0f);
	}
	manip.UseManip(false);
}
