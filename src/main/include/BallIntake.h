#pragma once

using namespace frc;

class BallIntake {

	public:
    void BallIntake();
    void Tick();
	
	private:
	WPI_TalonSRX *m_belt, m_intake;
	frc::DigitalInput *m_conveyorSensor, *m_pickupSensor, *m_coutput;
	frc::Solenoid::Solenoid *m_ramp;
    int ballCount, pickupPhase;
    bool isPressed;

};