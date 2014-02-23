#ifndef HAVE_PID_H
#define HAVE_PID_H

#include "WPILib.h"
#include "Hardware.h"

class PID_Class
{
private:

public:
	PID_Class();
	~PID_Class();
	float PID (float error, float KP, float KI, float KD);
};

#endif
