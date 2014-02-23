#include "CameraMovement.h"

CameraMovement::CameraMovement(UINT32 servoport, UINT32 solport):tiltServo(servoport),liftRelay(solport, Relay::kForwardOnly)
{
	liftRelay.Set(Relay::kOff);
	isUp = false;
}
void CameraMovement::SetServoPosition(float pos)
{
	if (isUp)
		tiltServo.Set(LerpJoystick(LOW_CAMERA_SERVO, HIGH_CAMERA_SERVO, pos));
}
void CameraMovement::SetPosition(CameraPosition pos)
{
	if (isUp)
	{
		switch(pos){
			case Ball:
				tiltServo.Set(LOW_CAMERA_SERVO);
			case Target:
				tiltServo.Set(HIGH_CAMERA_SERVO);
		}
	}
}
void CameraMovement::RaiseCamera()
{
liftRelay.Set(Relay::kOn);
isUp = true;
}
void CameraMovement::LowerCamera()
{
	tiltServo.Set(NEUTRAL_CAMERA_SERVO);
	liftRelay.Set(Relay::kOff);
	isUp = false;
}

float CameraMovement::LerpJoystick(float lowValue, float highValue, float joystick)
{
	return (highValue - lowValue) * (-0.5f * joystick + 0.5f) + lowValue;
}
