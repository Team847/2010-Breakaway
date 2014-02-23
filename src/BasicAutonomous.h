#ifndef HAVE_BasicAutonomous_H
#define HAVE_BasicAutonomous_H

#include "AutonomousInterface.h"
#include "Hardware.h"

//! This is a very basic autonomous mode
/*! 
 * This simply gets out of the way to allow
 * other robots on the alliance to attempt to score.
 */
class BasicAutonomous : public AutonomousInterface
{
private:
	RobotDrive * drive;
	Timer timer;
	
public:
	//! Constructor for the BasicAutonomous class
	/*!
	 * Initializes the class, and creates a timer.
	 */
	BasicAutonomous();
	
	//! Deconstructor for the BasicAutonomous class
	virtual ~BasicAutonomous();
	
	//! Restatrs the timer and retrives the drive from Hardware
	virtual void Init();

	virtual void Periodic();
	
	//! Drives to the left for the first 5 seconds of autonomous
	virtual void Continuous();
};

#endif
