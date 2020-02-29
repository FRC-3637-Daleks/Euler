#pragma once

using namespace frc;

class BallIntake {
	public:
    BallIntake(frc::Joystick *joy);
	~BallIntake();
    void Tick();
	
	private:
	WPI_TalonSRX *m_belt, *m_intake;
	frc::DigitalInput *m_conveyorSensor, *m_pickupSensor, *m_coutput;
	frc::Solenoid *m_ramp;
	frc::Joystick *m_stick;
    int ballCount, pickupPhase;
    bool isPressed;
};