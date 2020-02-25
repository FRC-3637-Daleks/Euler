#include "Euler.h"

BallIntake:: BallIntake () {

    m_belt = new WPI_TalonSRX(6);
    m_pickupSensor = new frc::DigitalInput(0);
    m_conveyorSensor = new frc::DigitalInput(1);
    m_coutput = new frc::DigitalInput(2);
    m_intake = new WPI_TalonSRX(5);
    m_ramp = new frc::Solenoid(0);
    isPressed = false;
    ballCount = 0;
    pickupPhase = 2;

}

BallIntake:: Tick () {

    if (m_rightStick->GetTrigger()) {
        pickupPhase = 0;
        isPressed->true;
       m_intake-> Set(0.5);
    }

     if (pickupPhase<2) {
         m_ramp-> Set(true);
    switch (pickupPhase) {
        case 0: 
        m_intake->Set(0.5);
	if (m_pickupSensor()->Get()) {
        ballCount++;
        pickupPhase++;
        //SmartDashboard::
    }
    break;
    case 1:
      m_belt-> Set(0.5);
      m_intake-> Set(0.5);

      if (!(m_conveyorSensor->Get())) {
          pickupPhase++;
      }
   /* if (m_coutput()->Get()) {
      m_
    }*/
    }
    break;
    }
    else {
        m_ramp->Set(false);
    }

}