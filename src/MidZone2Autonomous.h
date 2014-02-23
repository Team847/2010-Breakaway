#ifndef HAVE_MidZone2Autonomous_H
#define HAVE_MidZone2Autonomous_H

#include "Hardware.h"
#include "AutonomousInterface.h"
#include "CameraMovement.h"
#include "Autopilot.h"
#include "Manipulator.h"

class MidZone2Autonomous : public AutonomousInterface
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
	double bumpDelay;
	int killDead;
	
public:
	//! Constructor
	MidZone2Autonomous();
	
	//! Deconstructor
	virtual ~MidZone2Autonomous();
	
	virtual void Init();
	
	virtual void Periodic();

	virtual void Continuous();
};

#endif
