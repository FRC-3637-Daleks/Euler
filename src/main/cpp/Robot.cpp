#include "Euler.h"

using namespace frc;

void Robot::RobotInit() 
{
	m_xbox 			= new XboxController(0);
  	m_leftStick  	= new Joystick(2);
  	m_rightStick 	= new Joystick(1);
  	m_drive      	= new DalekDrive(1, 2, 3, 4, DalekDrive::driveType::kDifferential);
	m_auton			= new Auton(m_drive);
	m_talon1        = new WPI_TalonSRX(5);
	m_talon2        = new WPI_TalonSRX(6);
	m_xbox       = new frc::XboxController(0);
	m_converyorSensor = new frc::DigitalInput(0);
	m_pickupSensor  = new frc::DigitalInput(1);



}

void Robot::RobotPeriodic()
{

}

// I think I have some errors here, I wanna test this
void Robot::AutonomousInit()
{
	m_auton->AutonCase(1, 0); // the parameters change based on what auton sequence we are going to use
	waitSeconds = 0;
}

void Robot::AutonomousPeriodic() 
{
	waitSeconds += (double)this->GetPeriod();
	if (waitSeconds > 0) { // the number 0 change based on how long we want to wait in the auton sequence
		m_auton->AutonDrive();
	}
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

	if (m_xbox->GetBButtonPressed()) {
		m_talon1->Set(1.0);
		SmartDashboard::PutBoolean("b button pressed", true);
	} else {
		m_talon1->Set(0.0);
		SmartDashboard::PutBoolean("b button pressed", false);
	}

	if (m_xbox->GetAButtonPressed()) {
		m_talon2->Set(1.0);
		SmartDashboard::PutBoolean("a button pressed", true);
	} else {
		m_talon2->Set(0.0);
		SmartDashboard::PutBoolean("a button pressed", false);
	}
	if (m_xbox->GetYButtonPressed()) {
		m_talon1->Set(-0.5);
		SmartDashboard::PutBoolean("y button pressed", true);
	} else {
		m_talon1->Set(0.0);
		SmartDashboard::PutBoolean("y button pressed", false);
	}
	if (m_xbox->GetXButtonPressed()) {
		m_talon2->Set(-0.5);
		SmartDashboard::PutBoolean("x button pressed", true);
	} else {
		m_talon2->Set(0.0);
		SmartDashboard::PutBoolean("x button pressed", false);
	}

	if (m_converyorSensor->Get()) {
		m_talon2->Set(1.0);
		SmartDashboard::PutBoolean("Input Sensed", true);
	}

}

void Robot::TestInit()
{

}

void Robot::TestPeriodic()
{

}

#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
