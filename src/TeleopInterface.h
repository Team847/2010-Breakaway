#ifndef HAVE_TeleopInterface_H
#define HAVE_TeleopInterface_H

#include "WPILib.h"

//! Interface that teleop modes must implement
class TeleopInterface
{
public:
	//! Called when teleop mode is entered
	virtual void Init() = 0;
	
	//! When in teleop mode, this is called 200 times a second
	virtual void Periodic() = 0;
	
	//! When in teleop mode, this is called as fast as possible
	virtual void Continuous() = 0;
};

#endif
