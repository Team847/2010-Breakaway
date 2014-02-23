#include "Autopilot.h"
#define marginOfError 1.25
#define baseRotationRate 0.75
#define offsetModifier 0.1f

Autopilot::Autopilot() :
pid()
{
	camera = Hardware::GetInstance()->GetCameraVision();
	drive = Hardware::GetInstance()->GetRobotDrive();
	pVariable = 0.0f;
	iVariable = 0.0f;
	dVariable = 0.0f;
}
Autopilot::~Autopilot() {
	delete camera;
	delete drive;
}
int Autopilot::AutoAlign(bool triggerAlign) {
	pVariable = Hardware::GetInstance()->GetDriverStation()->GetAnalogIn(1) - 2.5f;
	iVariable = Hardware::GetInstance()->GetDriverStation()->GetAnalogIn(2) - 2.5f;
	dVariable = Hardware::GetInstance()->GetDriverStation()->GetAnalogIn(3) - 2.5f;
	// If the class is passed a value of true and...
	if (triggerAlign == true) {
		targetOffset = camera->GetTargetHeading();
		/* If target is to the left of center, determined by a predefined
		acceptable offset, and the target is seen, then...*/
		if (targetOffset < -marginOfError && targetOffset > -1000) {
			/* Rotate left at a rate defined by the base rotation speed,
			a set modifier, and the distance between the target and the view center */
			drive->HolonomicDrive(0.0f, 0.0f, baseRotationRate*pid.PID((float)targetOffset*offsetModifier,pVariable,iVariable,dVariable));
			// Return a zero to indicate it is working as expected
			return 0;
		}
		
		/* If the target is to the right of center, then... (If the target isn't
		seen, a value meaning 'Far left' is returned, so it's only checked above) */
		else if (targetOffset > marginOfError) {
			/* Rotate right at a rate defined by the base rotation speed,
			a set modifier, and the distance between the target and the view center */
			drive->HolonomicDrive(0.0f, 0.0f, baseRotationRate*pid.PID((float)targetOffset*offsetModifier,pVariable,iVariable,dVariable));
			//Return a zero to indicate it is working as expected
			return 0;
		}
		// If the target isn't seen, then...
		else if (targetOffset == -1000) {
			// Stop moving
			drive->HolonomicDrive(0,0,0);
			//Return a two to indicate that the target isn't in the field of view
			return 2;
		}
		
		// Else the target is more or less in front of the bot, and so...
		else {
			// Stop doing anything
			drive->HolonomicDrive(0.0f, 0.0f, baseRotationRate*pid.PID((float)targetOffset*offsetModifier,pVariable,iVariable,dVariable));
			// And return a one to indicate that the robot is done orienting itself
			return 1;
		}
	}
	// Else the program has nothing much to do, so...
	else {
		// Return a negative one to indicate as much.
		return -1;
	}
}
