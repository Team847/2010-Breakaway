#include "Hardware.h"

Hardware * Hardware::instance = 0;

Hardware::Hardware()
{
	frontLeftMotor = new SafeJaguar(frontLeftMotorChannel);
	rearLeftMotor = new SafeJaguar(rearLeftMotorChannel);
	frontRightMotor = new SafeJaguar(frontRightMotorChannel);
	rearRightMotor = new SafeJaguar(rearRightMotorChannel);
	drive = new RobotDrive(frontLeftMotor, rearLeftMotor, 
			frontRightMotor, rearRightMotor);
	// Invert the motors on the right side, using a zero-based index
	drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	
	driverStation = DriverStation::GetInstance();
	gyro = new Gyro(gyroChannel);
	cameraVision = new CameraVision();
	compressor = new Compressor(compressorPressureSwitchChannel, compressorRelayChannel);
	compressor->Start();
	kicker1 = new Solenoid(kicker1Channel);
	kicker2 = new Solenoid(kicker2Channel);
	pressureControl1 = new Solenoid(pressureControl1Channel);
	pressureControl2 = new Solenoid(pressureControl2Channel);
	cameraVision = new CameraVision();
	cameraMovement = new CameraMovement(cameraMovementServoChannel, cameraMovementRelayChannel);
	ballSwitch = new DigitalInput(ballSwitchChannel);
	lineSensor = new DigitalInput(lineSensorChannel);
	fanMotor = new Victor(fanMotorChannel);
}

Hardware::~Hardware()
{
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;
	delete drive;
	delete driverStation;
	delete gyro;
	delete cameraVision;
	delete cameraMovement;
	delete compressor;
	delete kicker1;
	delete kicker2;
	delete pressureControl1;
	delete pressureControl2;
	delete cameraVision;
	delete ballSwitch;
	delete lineSensor;
	delete fanMotor;
}

Hardware * Hardware::GetInstance()
{
	if (instance == 0)
		instance = new Hardware();
	
	return instance;
}

RobotDrive * Hardware::GetRobotDrive()
{
	return drive;
}

DriverStation * Hardware::GetDriverStation()
{
	return driverStation;
}

unsigned char Hardware::GetDriverStationInputNumber()
{
	return (char)
			(driverStation->GetDigitalIn(1) << 7
			| driverStation->GetDigitalIn(2) << 6
			| driverStation->GetDigitalIn(3) << 5
			| driverStation->GetDigitalIn(4) << 4
			| driverStation->GetDigitalIn(5) << 3
			| driverStation->GetDigitalIn(6) << 2
			| driverStation->GetDigitalIn(7) << 1
			| driverStation->GetDigitalIn(8));
}

CameraVision * Hardware::GetCameraVision()
{
	return cameraVision;
}

CameraMovement * Hardware::GetCameraMovement()
{
	return cameraMovement;
}

Gyro * Hardware::GetGyro()
{
	return gyro;
}

Solenoid * Hardware::GetKicker1()
{
	return kicker1;
}

Solenoid * Hardware::GetKicker2()
{
	return kicker2;
}

Solenoid * Hardware::GetPressureControl1()
{
	return pressureControl1;
}

Solenoid * Hardware::GetPressureControl2()
{
	return pressureControl2;
}

DigitalInput * Hardware::GetBallSwitch()
{
	return ballSwitch;
}

DigitalInput * Hardware::GetLineSensor()
{
	return lineSensor;
}

Victor * Hardware::GetFanMotor()
{
	return fanMotor;
}
