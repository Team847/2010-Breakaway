#ifndef HAVE_PHREDRobot_H
#define HAVE_PHREDRobot_H

#include "WPILib.h"
#include "AutonomousInterface.h"
#include "TeleopInterface.h"
#include "Hardware.h"
#include "SuperTeleop.h"
#include "BasicAutonomous.h"
#include "GoalScore1Autonomous.h"
#include "MidScorer1Autonomous.h"
#include "FarZone1Autonomous.h"
#include "FarZone2Autonomous.h"
#include "MidZone2Autonomous.h"
#include "GoalScore2Autonomous.h"

//! This is the main robot class in the framework 
class PHREDRobot : public IterativeRobot
{
private:
	AutonomousInterface * autonomous;
	TeleopInterface * teleop;
	static DigitalInput * lineSensor;
	static bool centerlineLeashEnabled;
	static bool detectedCenterline;
	
public:
	//! Constructor for the PHREDRobot class
	PHREDRobot();
	
	//! Deconstructor for the PHREDRobot class
	~PHREDRobot();
	
	//! Override of AutonomousInit() in IterativeRobot class
	virtual void AutonomousInit();
	
	//! Override of TeleopInit() in IterativeRobot class
	virtual void TeleopInit();
	
	//! Override of AutonomousPeriodic() in IterativeRobot class
	/*! This function is called 200 times a second. */
	virtual void AutonomousPeriodic();
	
	//! Override of TeleopPeriodic() in IterativeRobot class
	/*! This function is called 200 times a second. */
	virtual void TeleopPeriodic();
	
	//! Override of AutonomousContinuous() in IterativeRobot class
	/*! This function is called as often as possible. */
	virtual void AutonomousContinuous();
	
	//! Override of TeleopContinous() in IterativeRobot class
	/*! This function is called as often as possible. */
	virtual void TeleopContinuous();
	
	//! Override of DisabledInit() 
	virtual void DisabledInit();
	
	//! Enables of disables the centerline leash
	/*!
	 * \param setValue The value to set the leash to. True means enabled.
	 */
	static void SetCenterlineLeashEnabled(bool setValue);
};

START_ROBOT_CLASS(PHREDRobot);

#endif
