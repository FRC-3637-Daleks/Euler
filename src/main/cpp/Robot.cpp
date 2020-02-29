#include "Euler.h"

using namespace frc;

void Robot::RobotInit() 
{
  int i;
  try {
    m_xbox       = new frc::XboxController(XBOX);
    m_leftStick  = new frc::Joystick(LEFT_JOY);
    m_rightStick = new frc::Joystick(RIGHT_JOY);
    m_drive      = new DalekDrive(LEFT_FRONT_DRIVE, LEFT_REAR_DRIVE, RIGHT_FRONT_DRIVE, RIGHT_REAR_DRIVE, DalekDrive::driveType::kDifferential);
    m_ahrs       = new AHRS(SPI::Port::kMXP);
    m_auton      = new Auton(m_drive);
    m_compressor = new frc::Compressor(PCM);
<<<<<<< HEAD
	  m_ball_intake  = new BallIntake(m_xbox);
    for(i=0; i<NUM_SOLENOIDS; i++) {
      m_solenoids[i] = new frc::Solenoid(PCM, i);
      m_solenoids[i]->Set(true);
    }
=======
	m_ball_intake= new BallIntake(m_xbox, 0);
>>>>>>> 7264a1c74d4c1bb1c56cd99629d1c18251756f6c
  }
  catch (std::exception& e) {
    std::string err_string = "Error instantiating components:  ";
    err_string += e.what();
    DriverStation::ReportError(err_string.c_str());
  }

  frc::SmartDashboard::PutNumber("Start Auton", 2);
  frc::SmartDashboard::PutNumber("End Auton", 2);
  frc::SmartDashboard::PutNumber("Delay", 0);
  frc::SmartDashboard::PutNumber("Delay Phase", 0);
  frc::SmartDashboard::PutNumber("Auton Phase", 0);
  frc::SmartDashboard::PutBoolean("Pickup Ball", false);
  frc::SmartDashboard::PutNumber("Starting # of Balls", 3);

  m_ahrs->ZeroYaw();
  m_compressor->Start();
}

void Robot::RobotPeriodic()
{

}

// I think I have some errors here, I wanna test this
void Robot::AutonomousInit()
{
  auton_start = (int)frc::SmartDashboard::GetData("Start Auton");
  auton_end =   (int)frc::SmartDashboard::GetData("End Auton");
  waitSeconds = (int)frc::SmartDashboard::GetData("Delay");
	m_auton->AutonCase((double)auton_start, (double)auton_end); // the parameters change based on what auton sequence we are going to use
}

void Robot::AutonomousPeriodic() 
{
	//waitSeconds += (double)this->GetPeriod();
	if (waitSeconds <= (double)this->GetPeriod()) { // the number 0 change based on how long we want to wait in the auton sequence
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
			m_pi->FollowBall();
		} else {
        	m_drive->TankDrive(m_leftStick, m_rightStick, true);
		}
	}
<<<<<<< HEAD

  m_ball_intake->Tick();
=======
	m_ball_intake->Tick();
	SmartDashboard::PutNumber("ballCount", m_ball_intake->GetBallCount());

>>>>>>> 7264a1c74d4c1bb1c56cd99629d1c18251756f6c
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
