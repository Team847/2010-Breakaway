#ifndef HAVE_Hardware_H
#define HAVE_Hardware_H

#include "WPILib.h"
#include "CameraVision.h"
#include "CameraMovement.h"
#include "SafeJaguar.h"

//! This class represents the physical robot and driver station
/*!
 * It provides access to all hardware.
 */
class Hardware
{
private:
	SpeedController * frontLeftMotor, * rearLeftMotor,
		* frontRightMotor, * rearRightMotor;
	RobotDrive * drive;
	static const UINT32 frontLeftMotorChannel = 1;
	static const UINT32 rearLeftMotorChannel = 2;
	static const UINT32 frontRightMotorChannel = 3;
	static const UINT32 rearRightMotorChannel = 4;
	
	DriverStation * driverStation;
	
	Gyro * gyro;
	static const UINT32 gyroChannel = 1;
	
	Compressor * compressor;
	static const UINT32 compressorRelayChannel = 1;
	static const UINT32 compressorPressureSwitchChannel = 13;
	
	Solenoid * kicker1;
	static const UINT32 kicker1Channel = 1;
	
	Solenoid * kicker2;
	static const UINT32 kicker2Channel = 2;
	
	Solenoid * pressureControl1;
	static const UINT32 pressureControl1Channel = 3;
	
	Solenoid * pressureControl2;
	static const UINT32 pressureControl2Channel = 4;

	CameraVision * cameraVision;
	
	CameraMovement * cameraMovement;
	static const UINT32 cameraMovementServoChannel = 6;
	static const UINT32 cameraMovementRelayChannel = 2;
	
	DigitalInput * ballSwitch;
	static const UINT32 ballSwitchChannel = 9;
	
	DigitalInput * lineSensor;
	static const UINT32 lineSensorChannel = 10;
	
	Victor * fanMotor;
	static const UINT32 fanMotorChannel = 5;
	
	static Hardware * instance;
	
	Hardware();
	~Hardware();
	
public:
	//! Gets the single instance of Hardware
	/*!
	 * \return The single instance of Hardware class
	 */
	static Hardware * GetInstance();
	
	//! Gets the drive system of the robot
	/*!
	 * \return A pointer to the drive system of the robot
	 */
	RobotDrive * GetRobotDrive();
	
	//! Gets the driver station
	/*!
	 * \return A pointer to the driver station
	 */
	DriverStation * GetDriverStation();
	
	//! Gets a number from driver station digital input values
	/*!
	 * \return An unsigned char where each bit corresponds to an input
	 * on the driver station. Input 1 is most significant.
	 */
	unsigned char GetDriverStationInputNumber();
	
	//! Gets the gyro
	/*!
	 * \return A pointer to the gyro of the robot
	 */
	Gyro * GetGyro();
	
	//! Gets the first kicker solenoid
	/*!
	 * \return A pointer to the solenoid on the robot
	 */
	Solenoid * GetKicker1();
	
	//! Gets the second kicker solenoid
	/*!
	 * \return A pointer to the solenoid on the robot
	 */
	Solenoid * GetKicker2();
	
	//! Gets the first pressure control solenoid
	/*!
	 * \return A pointer to the solenoid on the robot
	 */
	Solenoid * GetPressureControl1();
	
	//! Gets the second pressure control solenoid
	/*!
	 * \return A pointer to the solenoid on the robot
	 */
	Solenoid * GetPressureControl2();
	
	//! Gets the CameraVision object
	/*!
	 * \return A pointer to the CameraVision object, which allows for high level targeting
	 */
	CameraVision * GetCameraVision();
	
	//! Gets the CameraMovement object
	/*!
	 * \return A pointer to the CameraMovement object, which controls the tilt of the camera
	 */
	CameraMovement * GetCameraMovement();

	//! Gets the switch that senses the ball
	/*!
	 * \return A pointer to the switch on channel 13 that senses the ball
	 */
	DigitalInput * GetBallSwitch();
	
	//! Gets the IR sensor to detect the line
	/*!
	 * \return A pointer to the IR line sensor
	 */
	DigitalInput * GetLineSensor();
	
	//! Gets the fan motor
	/*!
	 * \return A pointer to the Victor motor controller for the fan
	 */
	Victor * GetFanMotor();
};

#endif
