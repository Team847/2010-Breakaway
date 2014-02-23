#ifndef HAVE_CameraVision_H
#define HAVE_CameraVision_H
#include "Vision/AxisCamera.h"
#include "Vision/HSLImage.h"
#include "PIDController.h"
#include "Target.h"
#include "Ball.h"
#include "DashboardDataSender.h"
#include "WPILib.h"

#define MINIMUM_SCORE 0.01

class CameraVision {
private:
	//! Creates Location For images
	AxisCamera &camera;
	//! Sends image data to dashboard
	DashboardDataSender dds;
	
public:
	//! Finds Horizontal Position of Target
	/*!
	 *\return returns value offset from centerline
	 * -1000 means no target found
	 */
	double GetTargetHeading();
	//! Finds Horizontal Position of Ball
	/*!
	 *\return returns value offset from centerline
	 * -1000 means no ball found
	 * not active
	 */
	double GetBallHeading();

	//!Constructs the camera vision class
	CameraVision();
};

#endif
