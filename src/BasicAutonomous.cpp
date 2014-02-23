#include "BasicAutonomous.h"

BasicAutonomous::BasicAutonomous() :
	timer()
{}

BasicAutonomous::~BasicAutonomous() {}

void BasicAutonomous::Init()
{
	timer.Reset();
	timer.Start();
	drive = Hardware::GetInstance()->GetRobotDrive();
}

void BasicAutonomous::Periodic() {}

void BasicAutonomous::Continuous()
{
	if (timer.Get() < 5.0)
	{
		drive->HolonomicDrive(1.0f, 90.0f, 0.0f);
	}
	else
	{
		drive->HolonomicDrive(0.0f, 0.0f, 0.0f);
	}
}




