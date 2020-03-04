#pragma once

using namespace frc;

class Spinner {
	public:
	Spinner(frc::XboxController *xbox);
	~Spinner();
    void Tick();
	void Reinit();

	private:
	WPI_TalonSRX *m_spinner;
	XboxController *m_xbox;
   	frc::DoubleSolenoid *m_spinner_solenoid;

	void init(frc::XboxController *xbox);
};