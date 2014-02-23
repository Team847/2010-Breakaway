//Douglas Cantrell
//Feb 14, 2010, 12:20 PM
//GoalScore2Autonomous.cpp
//Move forward until ball encountered. Shoot ball. Move to side for specified duration. Repeat.

#include "GoalScore2Autonomous.h"
#define startDelay 0.0
#define fanStopDelay 0.0
#define leftDuration 0
#define bumpSafety 2.0
#define iterationCount 1

GoalScore2Autonomous::GoalScore2Autonomous() :
	pilot(), manip() {
	drive = Hardware::GetInstance()->GetRobotDrive();
	camera = Hardware::GetInstance()->GetCameraVision();
	sleepTest = false;
	firstTimeThrough = true;
	killDead = iterationCount;
}

GoalScore2Autonomous::~GoalScore2Autonomous() {
	delete drive;
	delete camera;
}

void GoalScore2Autonomous::Init() {
	Hardware::GetInstance()->GetFanMotor()->Set(-1.0);
	Hardware::GetInstance()->GetKicker1()->Set(false);
	Hardware::GetInstance()->GetKicker2()->Set(true);
	Hardware::GetInstance()->GetPressureControl1()->Set(false);
	Hardware::GetInstance()->GetPressureControl2()->Set(true);
}

void GoalScore2Autonomous::Periodic() {
}

void GoalScore2Autonomous::Continuous() {
	if (firstTimeThrough == true)
		Wait(startDelay);
	if (killDead > 0) {	
		if (sleepTest == false)	{
			if (Hardware::GetInstance()->GetBallSwitch()->Get() == false) {
				if (bumpTimer.Get() < bumpSafety || firstTimeThrough == true) {
					drive->HolonomicDrive(0.375f,0.0f,0.0f);
					bumpTimer.Start();
					firstTimeThrough = false;
				}
				else
					drive->HolonomicDrive(0.0f,0.0f,0.0f);
			}
			else {
				drive->HolonomicDrive(0.0f,0.0f,0.0f);
				bumpTimer.Stop();
				bumpTimer.Reset();
				if (penaltyTimer.Get() > 2.125 || killDead == iterationCount) {
					penaltyTimer.Stop();
					penaltyTimer.Reset();
					Hardware::GetInstance()->GetFanMotor()->Set(0.0);
					Wait(fanStopDelay);
					manip.UseManip(true);
					sleepTest = true;
				}
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
