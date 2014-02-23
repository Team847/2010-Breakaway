/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef SAFEJAGUAR_H
#define SAFEJAGUAR_H

#include "PWM.h"
#include "SpeedController.h"
#include "PIDOutput.h"

/**
 * Luminary Micro Jaguar Speed Control
 */
class SafeJaguar : public PWM, public SpeedController, public PIDOutput
{
public:
	explicit SafeJaguar(UINT32 channel);
	SafeJaguar(UINT32 slot, UINT32 channel);
	virtual ~SafeJaguar();
	float Get();
	void Set(float value);
	
	void PIDWrite(float output);

private:
	void InitSafeJaguar();
	static bool lastValPos;
};
#endif

