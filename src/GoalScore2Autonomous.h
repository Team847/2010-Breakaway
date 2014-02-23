#ifndef HAVE_GoalScore2Autonomous_H
#define HAVE_GoalScore2Autonomous_H

#include "Hardware.h"
#include "AutonomousInterface.h"
#include "CameraMovement.h"
#include "Autopilot.h"
#include "Manipulator.h"

class GoalScore2Autonomous : public AutonomousInterface
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
	GoalScore2Autonomous();
	
	//! Deconstructor
	virtual ~GoalScore2Autonomous();
	
	virtual void Init();
	
	virtual void Periodic();

	virtual void Continuous();
};

#endif
