#ifndef HAVE_AutonomousInterface_H
#define HAVE_AutonomousInterface_H

#include "WPILib.h"

//! Interface that autonomous modes must implement
class AutonomousInterface
{
public:	
	//! Called when autonomous mode is entered
	virtual void Init() = 0;
	
	//! When in autonomous mode, this is called 200 times a second
	virtual void Periodic() = 0;
	
	//! When in autonomous mode, this is called as fast as possible
	virtual void Continuous() = 0;
};

#endif
