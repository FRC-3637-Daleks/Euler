#include "Euler.h"

using namespace frc;

void Robot::RobotInit() 
{
  try {
    m_xbox       = new frc::XboxController(0);
    m_leftStick  = new frc::Joystick(1);
    m_rightStick = new frc::Joystick(2);
    m_drive = new DalekDrive(1, 2, 3, 4, DalekDrive::driveType::kDifferential);
    m_ahrs  = new AHRS(SPI::Port::kMXP);
    m_auton = new Auton(m_drive);
    m_belt = new WPI_TalonSRX(6);
    m_cinput = new frc::DigitalInput(0);
  }
  catch (std::exception& e) {
    std::string err_string = "Error instantiating components:  ";
    err_string += e.what();
    DriverStation::ReportError(err_string.c_str());
  }

  m_ahrs->ZeroYaw();
}

void Robot::RobotPeriodic()
{

}

// I think I have some errors here, I wanna test this
void Robot::AutonomousInit()
{
	m_auton->AutonCase(2, 0); // the parameters change based on what auton sequence we are going to use
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
      if (m_cinput->Get()) {
        m_belt-> Set(1.0);
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
