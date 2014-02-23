#ifndef HAVE_Manipulator_H
#define HAVE_Manipulator_H

#include "WPILib.h"
#include "Hardware.h"

//! Controls ball manipulator
class Manipulator
{
private:
	Timer firingPauseTimer;
	Timer failSafeTimer;
	bool extendTest;
	bool firstPassTest;
public:
	//! Constructor
	/*! \param manipChannel Channel ball manipulator solenoid is connected on
	 */
	Manipulator();
	~Manipulator();
	//! Manage trigger system
	/*! Activates ball manipulator, deactivates it, then waits two seconds before allowing further use.
	 * \param triggerManip Trigger for ball manipulator, true to activate, else false
	 */
	void UseManip (bool triggerManip=false);
};

#endif
