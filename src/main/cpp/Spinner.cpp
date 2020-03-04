#include "Euler.h"

Spinner::Spinner(frc::XboxController *xbox)
{
    init(xbox);
}

void
Spinner:: init(frc::XboxController *xbox)
{
    m_xbox = xbox;
	m_spinner = new WPI_TalonSRX(SPINNER);
   	m_spinner_solenoid = new frc::DoubleSolenoid(PCM, SPINNER_DEPLOY, SPINNER_EXHAUST);
    m_spinner_solenoid->Set(frc::DoubleSolenoid::kReverse);
}


Spinner::~Spinner()
{
    free(m_spinner);
    free(m_spinner_solenoid);
}

void Spinner::reinit()
{
    m_spinner_solenoid->Set(frc::DoubleSolenoid::kReverse);
}

void
Spinner::Tick()
{
    frc::SmartDashboard::PutNumber("SpinnerEncoder", m_spinner->GetSensorCollection().GetQuadraturePosition());
    if (m_xbox->GetYButtonPressed()) {
        if (m_spinner_solenoid->Get() == frc::DoubleSolenoid::kForward){
            m_spinner_solenoid->Set(frc::DoubleSolenoid::kReverse);
        } else {
            m_spinner_solenoid->Set(frc::DoubleSolenoid::kForward);
        }
     }

    if (m_spinner_solenoid->Get() == frc::DoubleSolenoid::kForward) {
        if (m_xbox->GetXButton()) {
            m_spinner->Set(1);
        } else {
            m_spinner->Set(0.0);
        }
    } else {
        m_spinner->Set(0.0);
    }
}