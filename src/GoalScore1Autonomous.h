#ifndef HAVE_GoalScore1Autonomous_H
#define HAVE_GoalScore1Autonomous_H

#include "Hardware.h"
#include "AutonomousInterface.h"
#include "CameraMovement.h"
#include "Autopilot.h"
#include "Manipulator.h"

class GoalScore1Autonomous : public AutonomousInterface
{
private:
	RobotDrive * drive;
	CameraVision * camera;
	Autopilot pilot;
	Manipulator manip;
	bool sleepTest;
	bool killDead;
	bool firstTimeThrough;
	bool seenBall;
	
public:
	//! Constructor
	GoalScore1Autonomous();
	
	//! Deconstructor
	virtual ~GoalScore1Autonomous();
	
	virtual void Init();
	
	virtual void Periodic();

	virtual void Continuous();
};

#endif
