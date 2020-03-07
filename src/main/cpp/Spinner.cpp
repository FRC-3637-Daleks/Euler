#include "Euler.h"

Spinner::Spinner(frc::XboxController *xbox)
{
    init(xbox);
}

void
Spinner:: init(frc::XboxController *xbox)
{
    const int kTimeoutMs = 30;
    const bool kSensorPhase = false;
    const bool kInvert = false;

    m_xbox = xbox;
	m_spinner = new WPI_TalonSRX(SPINNER);
    if(m_spinner == NULL)
        std::bad_alloc();
    m_spinner->ConfigFactoryDefault();
	m_spinner->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, kTimeoutMs);
	m_spinner->SetSensorPhase(kSensorPhase);
	m_spinner->SetInverted(kInvert);
    m_spinner->SetSelectedSensorPosition(0, 0, kTimeoutMs);
   	m_spinner_solenoid = new frc::DoubleSolenoid(PCM, SPINNER_DEPLOY, SPINNER_EXHAUST);
    if(m_spinner_solenoid == NULL)
        std::bad_alloc();
    m_spinner_solenoid->Set(frc::DoubleSolenoid::kReverse);
}


Spinner::~Spinner()
{
    free(m_spinner);
    free(m_spinner_solenoid);
}

void Spinner::Reinit()
{
    const int kTimeoutMs = 30;
    m_spinner->SetSelectedSensorPosition(0, 0, kTimeoutMs);
    m_spinner_solenoid->Set(frc::DoubleSolenoid::kReverse);
}

void
Spinner::Tick()
{
    float encoderCnt = m_spinner->GetSensorCollection().GetQuadraturePosition();

    frc::SmartDashboard::PutNumber("SpinnerEncoder", encoderCnt);
    frc::SmartDashboard::PutNumber("Approx Color Wheel rotations", encoderCnt/32768.0);

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