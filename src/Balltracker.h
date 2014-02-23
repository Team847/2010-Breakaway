#ifndef HAVE_Balltracker_H
#define HAVE_Balltracker_H

#include "WPILib.h"
#include "Hardware.h"

//! This is an auto ball-targeting code
class Balltracker
{
private:
	RobotDrive * drive;
	CameraVision * camera;
	double targetOffset;
public:
	Balltracker();
	~Balltracker();
	int AutoBallAlign (bool triggerBallAlign=false);
};

#endif
