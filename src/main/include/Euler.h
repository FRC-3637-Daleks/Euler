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

class Robot : public frc::TimedRobot {
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
	DalekDrive *m_drive;
	Auton *m_auton;

	double waitSeconds;
};