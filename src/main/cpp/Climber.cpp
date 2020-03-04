#include "Euler.h"

Climber::Climber(frc::XboxController *xbox)
{
    init(xbox);
}

void
Climber:: init(frc::XboxController *xbox)
{
    m_xbox = xbox;
	m_trolley = new WPI_TalonSRX(TROLLEY);
    m_lift = new WPI_TalonSRX(LIFT);
	m_ratchet_solenoid= new frc::Solenoid(PCM, RATCHET_LOCK);
    m_ratchet_solenoid->Set(false);
	m_climb_solenoid = new frc::DoubleSolenoid(PCM, CLIMB_DEPLOY, CLIMB_EXHAUST);
    m_climb_solenoid->Set(frc::DoubleSolenoid::kReverse);
}


Climber::~Climber()
{
    free(m_trolley);
    free(m_lift);
    free(m_ratchet_solenoid);
    free(m_climb_solenoid);
}

void
Climber::Tick()
{
    if (m_xbox->GetXButtonPressed()) {
        if (m_climb_solenoid->Get() == frc::DoubleSolenoid::kReverse) {
            m_climb_solenoid->Set(frc::DoubleSolenoid::kForward);
            m_ratchet_solenoid->Set(true);
        } else if (m_climb_solenoid->Get() == frc::DoubleSolenoid::kForward)
            m_climb_solenoid->Set(frc::DoubleSolenoid::kOff); //do not set back to kReverse or arm crashes down
    }

    if (m_xbox->GetBumperPressed(frc::GenericHID::kLeftHand)) {
        m_ratchet_solenoid->Set(!m_ratchet_solenoid->Get());
    }

    if (m_climb_solenoid->Get() == frc::DoubleSolenoid::kForward) {
        m_lift->Set(m_xbox->GetX(frc::GenericHID::kLeftHand) * 0.25);
    } else {
        m_lift->Set(0.0);
    }

    if (m_climb_solenoid->Get() == frc::DoubleSolenoid::kForward) {
        m_trolley->Set(m_xbox->GetX(frc::GenericHID::kRightHand));
    } else {
        m_trolley->Set(0.0);
    }
}