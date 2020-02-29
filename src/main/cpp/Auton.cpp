#include "Euler.h"

Auton::Auton(DalekDrive *drive, RaspberryPi *pi)
{
	m_drive			= drive;
	m_ahrs         	= new AHRS(SPI::Port::kMXP);
	m_ahrs->Reset();
	m_ahrs->ResetDisplacement();
	m_pi            = pi; 

	auton_phase = 0;
	pickupBalls = false;
}

void Auton::AutonCase(int begin, int end)
{
	switch (begin) {
		case 1: //right sensor
		enter_target_x = -2; //need sensor
		break;
		case 2: //staright on
		enter_target_x = 0;
		break;
		case 3: //left sensor
		enter_target_x = 5; //need sensor
		break;
	}

	enter_target_y = START_DIST;
	
	switch (end) {
		case 1:
			exit_target_x = -2.009775;
			exit_target_y = 3.048;
			break;
		case 2:
			exit_target_x = 3.17931851816;
			exit_target_y = 5.248275;
			break;
		case 3:
			exit_target_x = 3.851275;
			exit_target_y = 5.248275;
			break;
	}

	enter_target_ang = atan2(enter_target_y, enter_target_x);
	exit_target_ang  = atan2(exit_target_x, exit_target_y);
	//here set up what happens at the end (after delivery)
}

void Auton::AutonDrive()
{
	// if (auton_phase==frc::SmartDashboard::GetData("Delay Phase"))
	// waitSeconds += (double)this->GetPeriod();
	switch (auton_phase) {
		case 0: // turn to target
		if (m_pi->turnToFace(enter_target_ang)) {
			auton_phase++;
		}
		break;
		case 1: // drive to target
		if (driveToCoordinates(enter_target_x, enter_target_y, enter_target_ang)) {
			auton_phase++;;
		}
		break;
		case 2: // turn straight
		if (m_pi->turnToFace(0)) {
			auton_phase++;
		}
		break;
		case 3: // drive to wall
			if (driveToCoordinates(0, 0.762, 0)) {
				auton_phase++;
			}
			break;
		case 4: //delivers balls
			//Dump balls here
			auton_phase++;
			break;
		case 5: //give us a little space to turn around (can be lowered)
			if (driveToCoordinates(0, -0.762, 0)) {
				auton_phase++;
			}
			break;
		case 6: //turn around
			if (m_pi->turnToFace(PI)) {
				auton_phase++;
			}
			break;		
		case 7: //face exit
			if (m_pi->turnToFace(exit_target_ang)) {
				auton_phase++;
			}
			break;
		case 8: //drive towards exit
			if (driveToCoordinates(exit_target_x, exit_target_y, exit_target_ang)) {
				auton_phase++;
			}
			break;
		case 9: //collect balls if warrented
			if (!pickupBalls || m_pi->FollowBall()) {
				//collect ball
				ballTracker++;//Get true value from Josh
				if (ballTracker == 3)
					auton_phase++;
			}
			break;
		case 10: //end
			//return true;
			break;
		// add more once we get there
	}
	
	frc::SmartDashboard::PutNumber ("Auton Phase", auton_phase);

	//return false;
}

bool Auton::driveToCoordinates(double x, double y, double angle)
{
	SmartDashboard::PutNumber("angle offset", m_pi->angleOffset(angle) * 180 / PI);
	SmartDashboard::PutNumber("dist offset", sqrt(pow(x - m_ahrs->GetDisplacementX(), 2) + pow(y - m_ahrs->GetDisplacementY(), 2))); // this is not correct currently
	return m_pi->driveAdjusted(m_pi->angleOffset(angle), sqrt(pow(x - m_ahrs->GetDisplacementX(), 2) + pow(y - m_ahrs->GetDisplacementY(), 2)), angleOffsetCoefficient);
}