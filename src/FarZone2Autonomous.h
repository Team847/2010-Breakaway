#ifndef HAVE_FarZone2Autonomous_H
#define HAVE_FarZone2Autonomous_H

#include "Hardware.h"
#include "AutonomousInterface.h"
#include "CameraMovement.h"
#include "Autopilot.h"
#include "Manipulator.h"

class FarZone2Autonomous : public AutonomousInterface
{
private:
	RobotDrive * drive;
	CameraVision * camera;
	Autopilot pilot;
	Manipulator manip;
	Timer penaltyTimer;
	Timer bumpTimer;
	bool sleepTest;
	bool firstTimeThrough;
	bool backupCheck;
	double bumpDelay;
	int killDead;
	
public:
	//! Constructor
	FarZone2Autonomous();
	
	//! Deconstructor
	virtual ~FarZone2Autonomous();
	
	virtual void Init();
	
	virtual void Periodic();

	virtual void Continuous();
};

#endif
