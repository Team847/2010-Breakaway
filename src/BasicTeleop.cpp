#include "BasicTeleop.h"

BasicTeleop::BasicTeleop() :
	leftJoystick(1),
	rightJoystick(2)
{}

BasicTeleop::~BasicTeleop() {}

void BasicTeleop::Init() {}

void BasicTeleop::Periodic() {}

void BasicTeleop::Continuous()
{
	RobotDrive * drive = Hardware::GetInstance()->GetRobotDrive();
	
	drive->TankDrive(leftJoystick, rightJoystick);
}
