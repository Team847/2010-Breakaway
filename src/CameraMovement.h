//!This code allows tilting of the camera and will activate the camera safety.
#ifndef HAVE_CameraMovement_H
#define HAVE_CameraMovement_H
#include "WPILib.h"
#define LOW_CAMERA_SERVO 0.63f
#define HIGH_CAMERA_SERVO 0.39f
#define NEUTRAL_CAMERA_SERVO 0.48f

class CameraMovement {
public:
	enum CameraPosition {Ball, Target};
	CameraMovement(UINT32 servoport, UINT32 solport);
	void SetServoPosition(float pos);
	void SetPosition(CameraPosition pos);
	void RaiseCamera();
	void LowerCamera();
	bool isUp;
	
private:
	Servo tiltServo;
	Relay liftRelay;
	float LerpJoystick(float lowValue, float highValue, float joystick);
};
#endif
