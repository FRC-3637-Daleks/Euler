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
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <AHRS.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <DalekDrive.h>
#include <Auton.h>
#include <BallIntake.h>

#define PI	3.14159265358979323846

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
	DalekDrive *m_drive;
	Auton *m_auton;
	AHRS *m_ahrs;
	double waitSeconds;
};
