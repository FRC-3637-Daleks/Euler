#pragma once

using namespace frc;

class BallIntake {
	public:
    BallIntake(frc::XboxController *xbox);
	~BallIntake();
    void Tick();
	int GetBallCount();

	
	private:
	WPI_TalonSRX *m_belt, *m_intake;
	frc::DigitalInput *m_conveyorSensor, *m_pickupSensor, *m_coutput;
	frc::Solenoid *m_ramp;
    int pickupPhase;
    bool isPressed;
	int ballCount;
};