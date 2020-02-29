#pragma once

#include <iostream>
#include <string>
#include <frc/WPILib.h> // this creates a warning that increases compilation time, eventually replace with many smaller includes
#include <AHRS.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
// #include <frc/Joystick.h>
// #include <frc/TimedRobot.h>
// #include <frc/smartdashboard/SendableChooser.h>
// #include <frc/smartdashboard/SmartDashboard.h>
// #include <frc/shuffleboard/Shuffleboard.h>
// #include <frc/shuffleboard/ShuffleboardLayout.h>
// #include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include "DalekDrive.h"
#include "Auton.h"

#define PI					3.14159265358979323846

using namespace frc;

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
	XboxController *m_xbox;
	Joystick *m_leftStick;
	Joystick *m_rightStick;
	DalekDrive *m_drive;
	Auton *m_auton;
	rev::CANSparkMax *spark;
    rev::CANEncoder *sparkEncoder;
    WPI_TalonSRX *talon;
	WPI_TalonSRX *m_talon1;
	WPI_TalonSRX *m_talon2;
	frc::DigitalInput *m_pickupSensor, *m_converyorSensor;


	double waitSeconds;
};