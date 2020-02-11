#include "Euler.h"

using namespace frc;

void Robot::RobotInit() 
{
	m_xbox 			= new frc::XboxController(0);
  	m_leftStick  	= new frc::Joystick(1);
  	m_rightStick 	= new frc::Joystick(2);
  	m_drive      	= new DalekDrive(1, 2, 3, 4, DalekDrive::driveType::kDifferential);
	m_auton			= new Ball_Follow(m_drive);
}

void Robot::RobotPeriodic()
{

}

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
		} else {
        	m_drive->TankDrive(m_leftStick, m_rightStick, true);
		}
	}
}

void Robot::TestPeriodic()
{

}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
