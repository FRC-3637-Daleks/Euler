#include "Euler.h"

using namespace frc;

void Robot::RobotInit() 
{
  try {
    m_xbox       = new frc::XboxController(XBOX);
    m_leftStick  = new frc::Joystick(LEFT_JOY);
    m_rightStick = new frc::Joystick(RIGHT_JOY);
    m_drive      = new DalekDrive(LEFT_FRONT_DRIVE, LEFT_REAR_DRIVE, RIGHT_FRONT_DRIVE, RIGHT_REAR_DRIVE, DalekDrive::driveType::kDifferential);
    m_ahrs       = new AHRS(SPI::Port::kMXP);
    m_auton      = new Auton(m_drive);
    m_belt       = new WPI_TalonSRX(CONVEYOR_BELT);
    m_roller     = new WPI_TalonSRX(ROLLER_BAR);
    m_converyorSensor = new frc::DigitalInput(CONVEYOR_STOP);
	  m_pickupSensor    = new frc::DigitalInput(CONVEYOR_INPUT);
    m_compressor = new frc::Compressor(PCM);
  }
  catch (std::exception& e) {
    std::string err_string = "Error instantiating components:  ";
    err_string += e.what();
    DriverStation::ReportError(err_string.c_str());
  }
  m_ahrs->ZeroYaw();
  m_compressor->Start();
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
		m_roller->Set(1.0);
		SmartDashboard::PutBoolean("b button pressed", true);
	} else {
		m_roller->Set(0.0);
		SmartDashboard::PutBoolean("b button pressed", false);
	}

	if (m_xbox->GetAButtonPressed()) {
		m_belt->Set(1.0);
		SmartDashboard::PutBoolean("a button pressed", true);
	} else {
		m_belt->Set(0.0);
		SmartDashboard::PutBoolean("a button pressed", false);
	}

	if (m_xbox->GetYButtonPressed()) {
		m_roller->Set(-0.5);
		SmartDashboard::PutBoolean("y button pressed", true);
	} else {
		m_roller->Set(0.0);
		SmartDashboard::PutBoolean("y button pressed", false);
	}
	
	if (m_xbox->GetXButtonPressed()) {
		m_belt->Set(-0.5);
		SmartDashboard::PutBoolean("x button pressed", true);
	} else {
		m_belt->Set(0.0);
		SmartDashboard::PutBoolean("x button pressed", false);
	}

	if (m_converyorSensor->Get()) {
		m_belt->Set(1.0);
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
