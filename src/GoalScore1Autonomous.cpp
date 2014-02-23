//Douglas Cantrell claims this from Paul Atkinson
//Jan 31, 2010, 2:27 PM
//GoalScore1Autonomous.cpp
//This is a basic autonomous to move forward and shoot a ball at the goal

#include "GoalScore1Autonomous.h"
#define delayStart 0.0
#define fanStopDelay 0.0
#define leftDuration 1.5

GoalScore1Autonomous::GoalScore1Autonomous() :
	pilot(), manip() {
	drive = Hardware::GetInstance()->GetRobotDrive();
	camera = Hardware::GetInstance()->GetCameraVision();
	sleepTest = false;
	killDead = false;
	firstTimeThrough = true;
	seenBall = false;
}

GoalScore1Autonomous::~GoalScore1Autonomous() {
	delete drive;
	delete camera;
}

void GoalScore1Autonomous::Init() {
	Hardware::GetInstance()->GetFanMotor()->Set(-1.0);
	Hardware::GetInstance()->GetKicker1()->Set(false);
	Hardware::GetInstance()->GetKicker2()->Set(true);
	Hardware::GetInstance()->GetPressureControl2()->Set(false);
	Hardware::GetInstance()->GetPressureControl1()->Set(true);
	Hardware::GetInstance()->GetCameraMovement()->RaiseCamera();
}

void GoalScore1Autonomous::Periodic() {
}

void GoalScore1Autonomous::Continuous() {
	if (firstTimeThrough == true) {
		Wait(delayStart);
		firstTimeThrough = false;
	}
	if (killDead == false) {	
		if (sleepTest == false)	{
			if (Hardware::GetInstance()->GetBallSwitch()->Get() == false && seenBall == false) {
				drive->HolonomicDrive(0.375f,0.0f,0.0f);
			}
			else {
				//seenBall = true;
				if (pilot.AutoAlign(true) == 1) {
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
			drive->HolonomicDrive(0.5f,-90.0f,0.0f);
			Wait(leftDuration);
			killDead = true;
		}
	}
	else {
		drive->HolonomicDrive(0.0f,0.0f,0.0f);
	}
	manip.UseManip(false);
}
