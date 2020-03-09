#pragma once

using namespace frc;

class Spinner {
	public:
	Spinner(frc::XboxController *xbox, frc::DoubleSolenoid *climb_solenoid);
	~Spinner();
    void Tick();
	void Reinit();

	private:
	WPI_TalonSRX *m_spinner;
	XboxController *m_xbox;
   	frc::DoubleSolenoid *m_spinner_solenoid, *m_climb_solenoid;

	void init(frc::XboxController *xbox, frc::DoubleSolenoid *climb_solenoid);
};