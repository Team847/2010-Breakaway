#ifndef HAVE_Autopilot_H
#define HAVE_Autopilot_H

#include "WPILib.h"
#include "Hardware.h"
#include "PID.h"

//! This code automatically orients the robot to point it at the target
class Autopilot
{
private:
	RobotDrive * drive;
	CameraVision * camera;
	PID_Class pid;
	double targetOffset;
	float pVariable;
	float iVariable;
	float dVariable;
public:
	Autopilot();
	~Autopilot();
	int AutoAlign (bool triggerAlign=false);
};

#endif
