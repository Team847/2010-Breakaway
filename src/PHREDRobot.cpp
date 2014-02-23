#include "PHREDRobot.h"

bool PHREDRobot::centerlineLeashEnabled = true;
DigitalInput * PHREDRobot::lineSensor = 0;
bool PHREDRobot::detectedCenterline = false;

PHREDRobot::PHREDRobot()
{
	GetWatchdog().SetEnabled(false);
	teleop = new SuperTeleop();
	lineSensor = Hardware::GetInstance()->GetLineSensor();
	centerlineLeashEnabled = Hardware::GetInstance()->GetDriverStation()->GetDigitalIn(1);
	detectedCenterline = false;
}

PHREDRobot::~PHREDRobot()
{
	delete autonomous;
	delete teleop;
	delete lineSensor;
}

void PHREDRobot::AutonomousInit()
{
	GetWatchdog().SetEnabled(false);
	
	// Pick an autonomous mode based on driver station input
	switch (Hardware::GetInstance()->GetDriverStationInputNumber())
	{
	case 1:
		autonomous = new GoalScore1Autonomous();
		Hardware::GetInstance()->GetDriverStation()->SetDigitalOut(8, true);
		break;
	case 2:
		autonomous = new GoalScore2Autonomous();
		Hardware::GetInstance()->GetDriverStation()->SetDigitalOut(7, true);
		break;
	case 4:
		autonomous = new MidScorer1Autonomous();
		Hardware::GetInstance()->GetDriverStation()->SetDigitalOut(6, true);
		break;
	case 8:
		autonomous = new MidZone2Autonomous();
		Hardware::GetInstance()->GetDriverStation()->SetDigitalOut(5, true);
		break;
	case 16:
		autonomous = new FarZone1Autonomous();
		Hardware::GetInstance()->GetDriverStation()->SetDigitalOut(4, true);
		break;
	case 32:
		autonomous = new FarZone2Autonomous();
		Hardware::GetInstance()->GetDriverStation()->SetDigitalOut(3, true);
		break;
	}
	
	detectedCenterline = false;
	autonomous->Init();
}

void PHREDRobot::AutonomousPeriodic()
{
	GetWatchdog().Feed();
	if (centerlineLeashEnabled)
	{
		if (detectedCenterline)
		{
			// Do nothing, motors already stopped
		}
		else if (!lineSensor->Get())
		{
			Hardware::GetInstance()->GetRobotDrive()->HolonomicDrive(0.0f, 0.0f, 0.0f);
			detectedCenterline = true;
		}
		else
		{
			autonomous->Periodic();
		}
	}
	else
	{
		autonomous->Periodic();
	}
}

void PHREDRobot::AutonomousContinuous()
{
	if (centerlineLeashEnabled)
	{
		if (detectedCenterline)
		{
			// Do nothing, motors already stopped
		}
		else if (!lineSensor->Get())
		{
			Hardware::GetInstance()->GetRobotDrive()->HolonomicDrive(0.0f, 0.0f, 0.0f);
			detectedCenterline = true;
		}
		else
		{
			autonomous->Continuous();
		}
	}
	else
	{
		autonomous->Continuous();
	}
}

void PHREDRobot::TeleopInit()
{
	GetWatchdog().SetEnabled(false);
	teleop->Init();
}

void PHREDRobot::TeleopPeriodic()
{
	teleop->Periodic();
}

void PHREDRobot::TeleopContinuous()
{
	teleop->Continuous();
}

void PHREDRobot::DisabledInit()
{
	GetWatchdog().SetEnabled(false);
}

void PHREDRobot::SetCenterlineLeashEnabled(bool setValue)
{
	centerlineLeashEnabled = setValue;
}
