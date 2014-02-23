#include "CameraVision.h"

CameraVision::CameraVision() :
	camera(AxisCamera::GetInstance()) {
	//Wait(10.0);
	//printf("Getting camera instance\n");
	//printf("Setting camera parameters\n");
	camera.WriteResolution(AxisCamera::kResolution_160x120);
	camera.WriteBrightness(0);
	//Wait(1.0);
}

double CameraVision::GetTargetHeading() {
	if (camera.IsFreshImage() /*&& turnController.OnTarget() */) {

		// get the camera image
		ColorImage *image = camera.GetImage();

		// find FRC targets in the image
		vector<Target> targets = Target::FindCircularTargets(image);
		delete image;
		if (targets.size() == 0 || targets[0].m_score < MINIMUM_SCORE) {
			// no targets found. Make sure the first one in the list is 0,0
			// since the dashboard program annotates the first target in green
			// and the others in magenta. With no qualified targets, they'll all
			// be magenta.
			Target nullTarget;
			nullTarget.m_majorRadius = 0.0;
			nullTarget.m_minorRadius = 0.0;
			nullTarget.m_score = 0.0;
			if (targets.size() == 0)
				targets.push_back(nullTarget);
			else
				targets.insert(targets.begin(), nullTarget);
			dds.sendVisionData(0.0, targets);
			//if (targets.size() == 0)
				//printf("No target found\n\n");
			//else
				//printf("No valid targets found, best score: %f\n",
						//targets[0].m_score);
			return -1000;
		} else {
			// We have some targets.
			// set the new PID heading setpoint to the first target in the list
			double horizontalAngle = targets[0].GetHorizontalAngle();
			dds.sendVisionData(targets[0].m_xPos / targets[0].m_xMax, targets);
			return horizontalAngle;

		}
	}
	return -1000;
}

double CameraVision::GetBallHeading() {
	if (camera.IsFreshImage() /*&& turnController.OnTarget() */) {

		// get the camera image
		ColorImage *image = camera.GetImage();

		// find FRC targets in the image000
		vector<Ball> targets = Ball::FindCircularTargets(image);
		delete image;
		if (targets.size() == 0 || targets[0].m_score < MINIMUM_SCORE) {
			// no targets found. Make sure the first one in the list is 0,0
			// since the dashboard program annotates the first target in green
			// and the others in magenta. With no qualified targets, they'll all
			// be magenta.
			Ball nullTarget;
			nullTarget.m_majorRadius = 0.0;
			nullTarget.m_minorRadius = 0.0;
			nullTarget.m_score = 0.0;
			if (targets.size() == 0)
				targets.push_back(nullTarget);
			else
				targets.insert(targets.begin(), nullTarget);
			dds.sendVisionData(0.0, targets);
			if (targets.size() == 0)
				printf("No target found\n\n");
			else
				printf("No valid targets found, best score: %f\n",
						targets[0].m_score);
			return -1000;
		} else {
			// We have some targets.
			// set the new PID heading setpoint to the first target in the list
			double horizontalAngle = targets[0].GetHorizontalAngle();
			dds.sendVisionData(targets[0].m_xPos / targets[0].m_xMax, targets);
			return horizontalAngle;

		}
	}
	return -1000;
}
