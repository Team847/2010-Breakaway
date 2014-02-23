#ifndef HAVE_FarZone1Autonomous_H
#define HAVE_FarZone1Autonomous_H

#include "Hardware.h"
#include "AutonomousInterface.h"
#include "CameraMovement.h"
#include "Autopilot.h"
#include "Manipulator.h"

class FarZone1Autonomous : public AutonomousInterface
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
	int killDead;
	
public:
	//! Constructor
	FarZone1Autonomous();
	
	//! Deconstructor
	virtual ~FarZone1Autonomous();
	
	virtual void Init();
	
	virtual void Periodic();

	virtual void Continuous();
};

#endif
