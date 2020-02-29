#pragma once

using namespace frc;

class BallIntake {
	public:
    BallIntake(frc::XboxController *xbox);
	~BallIntake();
    void Tick();
	int GetBallCount();

	
	private:
	WPI_TalonSRX *m_intake, *m_conveyor;
	DigitalInput *m_pickupSensor, *m_releaseSensor;
	Solenoid *m_ramp;
	XboxController *m_xbox;

    int ballCount, pickupPhase;
    bool triggerHeld, triggerOn;
};