//Paul Atkinson claims this from Ben
//Jan 18, 2010, 9:46 AM
//SuperTeleop.cpp
//This is a basic teleop w/ mechanum drive
//Hi Paul!!!!-Karl

#include "SuperTeleop.h"
#define fanStopDelay 0.0
#define fanRestartDelay 0.375
// Comment out the following line to disable tank drive
#define USING_TANK_DRIVE

SuperTeleop::SuperTeleop() :
	leftJoystick(1), rightJoystick(2), pilot(), manip(), dds() {
	drive = Hardware::GetInstance()->GetRobotDrive();
	camera = Hardware::GetInstance()->GetCameraVision();
	cameraMovement = Hardware::GetInstance()->GetCameraMovement();
	fanPower = true;
	ballSensorRequirement = false;
	timerStopped = true;
	pressure1 = Hardware::GetInstance()->GetPressureControl1();
	pressure2 = Hardware::GetInstance()->GetPressureControl2();
}

SuperTeleop::~SuperTeleop() {
	delete drive;
	delete camera;
	delete cameraMovement;
	delete pressure1;
	delete pressure2;
}

void SuperTeleop::Init() {
	//Sets the kick to High
	pressure1->Set(false);
	pressure2->Set(true);
	Hardware::GetInstance()->GetKicker1()->Set(false);
	Hardware::GetInstance()->GetKicker2()->Set(true);
}

void SuperTeleop::Periodic() {
	if (rightJoystick.GetTrigger()) //raises camera when button pressed
		cameraMovement->RaiseCamera();
	else
		cameraMovement->LowerCamera();	
	if (rightJoystick.GetRawButton(2) || leftJoystick.GetRawButton(3)) //lets you shoot w/out pressing 
		ballSensorRequirement = false;
	else
		ballSensorRequirement = true;
	if (rightJoystick.GetRawButton(3)) //turns fan on or off
		fanPower = false;
	else
		fanPower = true;
	if (rightJoystick.GetRawButton(4)){ //Low kick
		pressure1->Set(true);
		pressure2->Set(false);
	}
	if (rightJoystick.GetRawButton(5)){ //High kick
		pressure1->Set(false);
		pressure2->Set(true);
	}
	if (leftJoystick.GetRawButton(2)) { //turns on autopilot
		result = pilot.AutoAlign(true);
	} else {
		pilot.AutoAlign(false);
		camera->GetTargetHeading();
	}
	cameraMovement->SetServoPosition(rightJoystick.GetThrottle());
	dds.sendIOPortData(rightJoystick.GetRawButton(4), rightJoystick.GetRawButton(5), rightJoystick.GetRawButton(2), Hardware::GetInstance()->GetBallSwitch()->Get());
}

void SuperTeleop::Continuous() {
	if (fanPower == true && (fanRestartTimer.Get() > fanRestartDelay || timerStopped)) {
		Hardware::GetInstance()->GetFanMotor()->Set(-1.0);
		fanRestartTimer.Stop();
		fanRestartTimer.Reset();
		timerStopped = true;
	}
	else
		Hardware::GetInstance()->GetFanMotor()->Set(0.0);
	
	//Drive code
	if (leftJoystick.GetRawButton(2) == false) {
#ifdef USING_TANK_DRIVE
		drive->HolonomicDrive(leftJoystick.GetMagnitude(),
				leftJoystick.GetDirectionDegrees(), 
				0.3125f*(fabs(leftJoystick.GetZ()+0.2f)+fabs(leftJoystick.GetZ()-0.2f)-0.4f)
				*(2.5f*(fabs(leftJoystick.GetZ()+0.2f)-fabs(leftJoystick.GetZ()-0.2f))));
#else
		drive->TankDrive(leftJoystick, rightJoystick);
#endif
	}
	
	//Shooting code
	if ((Hardware::GetInstance()->GetBallSwitch()->Get() || ballSensorRequirement == false) && leftJoystick.GetTrigger()) {
		Hardware::GetInstance()->GetFanMotor()->Set(0.0);
		Wait (fanStopDelay);
		manip.UseManip(true);
		fanRestartTimer.Start();
		timerStopped = false;
	}
	manip.UseManip(false);
}


