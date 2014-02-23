#include "MidScorer1Autonomous.h"

MidScorer1Autonomous::MidScorer1Autonomous() :
	manip()
{
	camMove = Hardware::GetInstance()->GetCameraMovement();
	Hardware::GetInstance()->GetFanMotor()->Set(-1.0);
	drive = Hardware::GetInstance()->GetRobotDrive();
	camera = Hardware::GetInstance()->GetCameraVision();
	pressure1 = Hardware::GetInstance()->GetPressureControl1();
	pressure2 = Hardware::GetInstance()->GetPressureControl2();
	seenBall = false;
}

MidScorer1Autonomous::~MidScorer1Autonomous() {
	delete camMove;
	delete camera;
	delete drive;
	delete pressure1;
	delete pressure2;
}

void MidScorer1Autonomous::Init(){
	state = FindBall;
	pressure1->Set(false);
	pressure2->Set(true);
	camMove->RaiseCamera();
	Hardware::GetInstance()->GetKicker1()->Set(false);
	Hardware::GetInstance()->GetKicker2()->Set(true);
}

void MidScorer1Autonomous::Periodic() {}

void MidScorer1Autonomous::Continuous()
{
	camMove->SetPosition(CameraMovement::Ball);
	switch (state)
	{
		//FindBall is the mode that finds the ball
		case FindBall:	{
			    Hardware::GetInstance()->GetFanMotor()->Set(-1.0);
				targetOffset = camera->GetBallHeading();
				//if it does see the ball, it starts the timer
				if (targetOffset != -1000 || seenBall == true) {
					seenBall = true;
					MissTimer.Start();
					if (MissTimer.Get() > 2.0) {
						drive->HolonomicDrive(0.0f, 0.0f, 0.0f);
					} else {
						drive->HolonomicDrive(0.5f, 0.0f, 0.0f);
					}
					if (Hardware::GetInstance()->GetBallSwitch()->Get() == true)
					{
						//if the ball is in the robot it will go to shoot
						seenBall = false;
						MissTimer.Stop();
						MissTimer.Reset();
						drive->HolonomicDrive(0.1f, 0.0f, 0.0f);
						state = Shoot;
					}
				} else {
					drive->HolonomicDrive(0.0f, 0.0f, 0.0f);
				}
/* The previous block of code was modified in an attempt to more accurately represent the
intention of the original programmer, so far as it could be deduced from available data.*/
		}
		break;
		//Shoots the ball
		case Shoot:		{
				Hardware::GetInstance()->GetFanMotor()->Set(0.0);
				manip.UseManip(true);
				drive->HolonomicDrive(0.0f, 0.0f, 0.0f);
				Wait(0.375);
				manip.UseManip(false);
				Hardware::GetInstance()->GetFanMotor()->Set(-1.0);
				ScoreTimer.Start();
				state = Back;

		}
		break;
		//Resets the positions of the robot to infront of the next ball
		case Back:		{
				drive->HolonomicDrive(-0.5f, 90.0f, 0.0f);
// The line of code immediately below this comment was modified for purposes of testing.
				if (ScoreTimer.Get() > 1.0) {
					drive->HolonomicDrive(0.5f, -90.0f, 0.0f);
					if (ScoreTimer.Get() > 2.5) {
						ScoreTimer.Stop();
						ScoreTimer.Reset();
						drive->HolonomicDrive(0.0f, 0.0f, 0.0f);
						state = FindBall;
					}
				}
		}
		break;
	}
}

