#ifndef HAVE_BasicTeleop_H
#define HAVE_BasicTeleop_H

#include "Hardware.h"
#include "TeleopInterface.h"

class BasicTeleop : public TeleopInterface
{
private:
	Joystick leftJoystick, rightJoystick;
	
public:
	BasicTeleop();
	virtual ~BasicTeleop();
	virtual void Init();
	virtual void Periodic();
	virtual void Continuous();
};

#endif
