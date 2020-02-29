#include "Euler.h"

BallIntake::BallIntake()
{
    m_belt = new WPI_TalonSRX(6);
    m_pickupSensor = new frc::DigitalInput(0);
    m_conveyorSensor = new frc::DigitalInput(1);
    m_coutput = new frc::DigitalInput(2);
    m_intake = new WPI_TalonSRX(5);
    m_ramp = new frc::Solenoid(0);
    //m_stick = joy;
    isPressed = false;
    ballCount = (int)frc::SmartDashboard::GetData("Starting # of Balls");
    pickupPhase = 2;
}

BallIntake::~BallIntake()
{
    free(m_belt);
    free(m_pickupSensor);
    free(m_coutput);
    free(m_intake);
    free(m_ramp);
}

int BallIntake::GetBallCount()
{
    return ballCount;
}