#include "Euler.h"

using namespace frc;

void Robot::RobotInit() 
{
  cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera("10.36.37.16");  // Initialize Camera
  // camera.SetResolution(160, 90);    // Only use these two lines if needed
  // camera.SetFPS(15);
  try {
    m_xbox        = new frc::XboxController(XBOX);
    m_leftStick   = new frc::Joystick(LEFT_JOY);
    m_rightStick  = new frc::Joystick(RIGHT_JOY);
    m_drive       = new DalekDrive(LEFT_FRONT_DRIVE, LEFT_REAR_DRIVE, RIGHT_FRONT_DRIVE, RIGHT_REAR_DRIVE, DalekDrive::driveType::kDifferential);
    m_ahrs        = new AHRS(SPI::Port::kMXP);
    m_pi          = new RaspberryPi(m_drive);
    m_compressor  = new frc::Compressor(PCM);
	  m_ballIntake  = new BallIntake(m_xbox);
    m_auton       = new Auton(m_drive, m_ahrs, m_pi, m_ballIntake);
    m_climber     = new Climber(m_xbox);
    m_spinner     = new Spinner(m_xbox);
    m_limelight   = new Limelight(m_drive);
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
  frc::SmartDashboard::PutBoolean("Pickup Ball End", false);
  frc::SmartDashboard::PutBoolean("Pickup Ball Start", false);
  //frc::SmartDashboard::PutNumber("Starting # of Balls", 3);

  m_ahrs->ZeroYaw();
  m_ahrs->Reset();
	m_ahrs->ResetDisplacement();
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
  m_climber->Reinit();
  m_spinner->Reinit();
  m_ballIntake->Reinit();
}

void Robot::AutonomousPeriodic() 
{
  if (m_auton->auton_phase == 1) {
    if (!timeChanged) {
      timeOffset = (double)this->GetPeriod();
      timeChanged = true;
    }
	  if (waitSeconds <= (double)(this->GetPeriod()) - timeOffset) // the number 0 change based on how long we want to wait in the auton sequence
      m_auton->auton_phase++;
  }
  m_auton->AutonDrive();
}

void Robot::TeleopInit()
{
   m_climber->Reinit();
   m_spinner->Reinit();
   m_ballIntake->Reinit();
}

void Robot::TeleopPeriodic()
{
    if (m_drive) {
		  if (m_rightStick->GetTrigger() || m_leftStick->GetTrigger()) { // JUST FOR TESTING
		    m_pi->FollowBall();
      } else if (m_xbox->GetStartButton()) {
        m_drive->TankDrive(-0.3, -0.3, false);
      } else {
        m_drive->TankDrive(m_leftStick, m_rightStick, true);
      }
    }


	m_ballIntake->Tick();  
  m_spinner->Tick();
  m_climber->Tick();


}

void Robot::TestInit()
{

}

void Robot::TestPeriodic()
{

}

void Robot::DisabledInit()
{
  m_climber->DisabledInit();
}


#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
