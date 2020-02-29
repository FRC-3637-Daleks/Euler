#pragma once

#include <iostream>
#include <string>
#include <frc/AnalogGyro.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/DigitalInput.h>
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <AHRS.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <DalekDrive.h>
#include <RaspberryPi.h>
#include <BallIntake.h>
#include <Auton.h>

#define PI	3.14159265358979323846

// CAN BUS devices
enum CAN_IDS {
	LEFT_FRONT_DRIVE = 1,
	LEFT_REAR_DRIVE = 2, 
	RIGHT_FRONT_DRIVE = 3, 
	RIGHT_REAR_DRIVE = 4,
	ROLLER_BAR = 5, 
	CONVEYOR_BELT = 6, 
	LIFT = 7, 
	TROLLEY = 8, 
	SPINNER = 9,
	PCM = 10
 };

// Devices connected to driverstation
enum DRIVER_STATION_IO {
	XBOX = 0, 
	LEFT_JOY = 1, 
	RIGHT_JOY = 2
};

// Digitial Input
enum DIGITAL_IO {
	CONVEYOR_INPUT = 0,
	CONVEYOR_STOP = 1
};

class Robot : public TimedRobot {
	public:
	void RobotInit() override;
	void RobotPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestInit() override;
	void TestPeriodic() override;
	
	private:
	frc::XboxController *m_xbox;
	frc::Joystick *m_leftStick;
	frc::Joystick *m_rightStick;
	frc::DigitalInput *m_cinput;
	frc::Compressor *m_compressor;
	WPI_TalonSRX *m_belt;
	WPI_TalonSRX *m_roller;
	DalekDrive *m_drive;
	RaspberryPi *m_pi;
	BallIntake *m_ballIntake;
	Auton *m_auton;
	AHRS *m_ahrs;
	rev::CANSparkMax *spark;
    rev::CANEncoder *sparkEncoder;
	frc::DigitalInput *m_pickupSensor, *m_converyorSensor;

	double waitSeconds;
	int auton_start, auton_end;
	bool pickupBall;
};
