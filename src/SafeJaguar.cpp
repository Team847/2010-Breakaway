/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/


#include "SafeJaguar.h"
#include "DigitalModule.h"
#include "WPILib.h"

#define reverseDelay 0.01  // delay this many seconds when reversing motor direction
bool SafeJaguar::lastValPos = false;

/**
 * Common initialization code called by all constructors.
 *
 * Modified by PHRED Team 847 to delay briefly whenever a motor reverses direction
 *
 */
void SafeJaguar::InitSafeJaguar()
{
	/*
	 * Input profile defined by Luminary Micro.
	 * 
	 * Full reverse ranges from 0.671325ms to 0.6972211ms
	 * Proportional reverse ranges from 0.6972211ms to 1.4482078ms
	 * Neutral ranges from 1.4482078ms to 1.5517922ms
	 * Proportional forward ranges from 1.5517922ms to 2.3027789ms
	 * Full forward ranges from 2.3027789ms to 2.328675ms
	 */
	SetBounds(251, 135, 128, 120, 4);
	SetPeriodMultiplier(kPeriodMultiplier_1X);
	SetRaw(m_centerPwm);
	lastValPos = false;
}

/**
 * Constructor that assumes the default digital module.
 * 
 * @param channel The PWM channel on the digital module that the Jaguar is attached to.
 */
SafeJaguar::SafeJaguar(UINT32 channel) : PWM(channel)
{
	InitSafeJaguar();
}

/**
 * Constructor that specifies the digital module.
 * 
 * @param slot The slot in the chassis that the digital module is plugged into.
 * @param channel The PWM channel on the digital module that the Jaguar is attached to.
 */
SafeJaguar::SafeJaguar(UINT32 slot, UINT32 channel) : PWM(slot, channel)
{
	InitSafeJaguar();
}

SafeJaguar::~SafeJaguar()
{
}

/**
 * Set the PWM value.  
 * 
 * The PWM value is set using a range of -1.0 to 1.0, appropriately
 * scaling the value for the FPGA.
 * 
 * @param speed The speed value between -1.0 and 1.0 to set.
 */
void SafeJaguar::Set(float speed)
{
	if (speed < 0.0){
		if (lastValPos) {
			Wait(reverseDelay);
			SetSpeed(0.0);
			lastValPos = false;
		}
	}
	else
	{
		if (~lastValPos) {
			Wait(reverseDelay);
			SetSpeed(0.0);
			lastValPos = true;
		}
		
	}
	SetSpeed(speed);
}

/**
 * Get the recently set value of the PWM.
 * 
 * @return The most recently set value for the PWM between -1.0 and 1.0.
 */
float SafeJaguar::Get()
{
	return GetSpeed();
}

/**
 * Write out the PID value as seen in the PIDOutput base object.
 * 
 * @param output Write out the PWM value as was found in the PIDController
 */
void SafeJaguar::PIDWrite(float output)
{
	Set(output);
}
