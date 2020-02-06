#include "Euler.h"

using namespace frc;

void Robot::RobotInit() 
{
	m_xbox 			= new frc::XboxController(0);
  	m_leftStick  	= new frc::Joystick(1);
  	m_rightStick 	= new frc::Joystick(2);
  	m_drive      	= new DalekDrive(1, 2, 3, 4, DalekDrive::driveType::kDifferential);
	m_auton			= new Auton(m_drive);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{

}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit()
{
	
}

void Robot::AutonomousPeriodic() 
{
	
}

void Robot::TeleopInit()
{

}

void Robot::TeleopPeriodic()
{
    if (m_drive) {
		if (m_rightStick->GetTrigger() || m_leftStick->GetTrigger()) { // JUST FOR TESTING
			m_auton->FollowBall();
		}
        m_drive->TankDrive(m_leftStick, m_rightStick, true);
	}
}

void Robot::TestPeriodic()
{

}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
