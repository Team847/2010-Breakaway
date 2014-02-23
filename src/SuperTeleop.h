#ifndef HAVE_SuperTeleop_H
#define HAVE_SuperTeleop_H

#include "Hardware.h"
#include "TeleopInterface.h"
#include "CameraMovement.h"
#include "Autopilot.h"
#include "Manipulator.h"
#include <math.h>
#include "DashboardDataSender.h"

//! Implements a simple teleop mecanum drive mode
class SuperTeleop : public TeleopInterface
{
private:
	Joystick leftJoystick, rightJoystick;
	RobotDrive * drive;
	CameraVision * camera;
	Autopilot pilot;
	Manipulator manip;
	CameraMovement * cameraMovement;
	Timer fanRestartTimer;
	DashboardDataSender dds;
	bool fanPower;
	bool ballSensorRequirement;
	bool timerStopped;
	int result;
	Solenoid * pressure1;
	Solenoid * pressure2;
	
public:
	//! Constructor
	/*! Reads from joystick at port one. */
	SuperTeleop();
	
	//! Deconstructor
	virtual ~SuperTeleop();
	
	virtual void Init();
	
	virtual void Periodic();
	//! Reads from joystick
	virtual void Continuous();
};

#endif
