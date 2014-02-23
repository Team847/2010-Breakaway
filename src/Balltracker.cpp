#include "Balltracker.h"
#define marginOfError 3
#define baseRotationRate 0.75
#define offsetModifier 0.1

Balltracker::Balltracker() {
	camera = Hardware::GetInstance()->GetCameraVision();
	drive = Hardware::GetInstance()->GetRobotDrive();
}
Balltracker::~Balltracker() {
	delete camera;
	delete drive;
}
int Balltracker::AutoBallAlign(bool triggerBallAlign) {
	// If the class is passed a value of true and...
	if (triggerBallAlign == true) {
		targetOffset = camera->GetBallHeading();
		/* If target is to the left of center, determined by a predefined
		acceptable offset, and the target is seen, then...*/
		if (targetOffset < -marginOfError && targetOffset > -1000) {
			/* Rotate left at a rate defined by the base rotation speed,
			a set modifier, and the distance between the target and the view center */
			drive->HolonomicDrive(0, 0, baseRotationRate*offsetModifier*targetOffset);
			// Return a zero to indicate it is working as expected
			return 0;
		}
		
		/* If the target is to the right of center, then... (If the target isn't
		seen, a value meaning 'Far left' is returned, so it's only checked above) */
		else if (targetOffset > marginOfError) {
			/* Rotate right at a rate defined by the base rotation speed,
			a set modifier, and the distance between the target and the view center */
			drive->HolonomicDrive(0, 0, baseRotationRate*offsetModifier*targetOffset);
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
			drive->HolonomicDrive(0, 0, 0);
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
