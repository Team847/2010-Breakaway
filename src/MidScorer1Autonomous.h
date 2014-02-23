#ifndef HAVE_MidScorer1Autonomous_H
#define HAVE_MidScorer1Autonomous_H

#include "AutonomousInterface.h"
#include "Hardware.h"
#include "Manipulator.h"
#include "Ball.h"
#include "Autopilot.h"
#include "Balltracker.h"

//! This is an autonomous mode for mid zone
/*! 
 * 
 */
class MidScorer1Autonomous : public AutonomousInterface
{
private:
	RobotDrive * drive;
	Manipulator manip;
	Ball ball;
	Autopilot pilot;
	CameraMovement * camMove;
	enum MidScoreState { FindBall, Shoot, Back };
	MidScoreState state;
	Timer ScoreTimer;
	Timer MissTimer;
	Balltracker ballfind;
	double targetOffset;
	CameraVision * camera;
	Solenoid * pressure1;
	Solenoid * pressure2;
	bool seenBall;
	
public:
	//! Constructor for the MidScorer1Autonomous class
	/*!
	 * Initializes the class, and creates a timer.
	 */
	MidScorer1Autonomous();
	
	//! Deconstructor for the MidScorer1Autonomous class
	virtual ~MidScorer1Autonomous();
	
	//! Restatrs the timer and retrives the drive from Hardware
	virtual void Init();

	virtual void Periodic();
	
	//! Drives to the left for the first 5 seconds of autonomous
	virtual void Continuous();
};

#endif
