#include "Euler.h"

Auton::Auton(DalekDrive *drive, AHRS * ahrs, RaspberryPi *pi, BallIntake *ballIntake)
{
	m_drive			= drive;
	m_ahrs			= ahrs;
	m_pi            = pi; 
	m_ballIntake    = ballIntake;

	auton_phase = 0;
	pickupBallStart = frc::SmartDashboard::GetData("Pickup Ball Start");
	pickupBallEnd   = frc::SmartDashboard::GetData("Pickup Ball End");
}

void Auton::AutonCase(int begin, int end)
{
	switch (begin) {
		case 1: //right sensor
		enter_target_x = -2; //need sensor
		break;
		case 2: //straight on
		enter_target_x = 0;
		break;
		case 3: //left sensor
		enter_target_x = 5; //need sensor
		break;
	}

	enter_target_y = lineToWall;
	
	switch (end) {
		case 1: //Our trench
			exit_target_x = -2.009775;
			exit_target_y = 3.048;
			break;
		case 2: //Shield Generator
			exit_target_x = 3.17931851816;
			exit_target_y = 5.248275;
			break;
		case 3: //Enemy trench
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
	if (!m_ahrs->IsCalibrating()) {
		switch (auton_phase) {
			case 0:
				if(!pickupBallStart) {
					auton_phase = 2;
				}	else if(m_pi->FollowBall()) {
						m_ballIntake->StartIntake();
						if (m_ballIntake->GetBallCount() == 5)
							auton_phase++;
					}
				break;
			case 1:
			//this is when the case will wait
				break;
			case 2: // turn to target
				if (m_pi->turnToFace(enter_target_ang)) {
					auton_phase++;
				}
				break;
			case 3: // drive to target
				if (driveToCoordinates(enter_target_x, enter_target_y, enter_target_ang)) {
					auton_phase++;;
				}
				break;
			case 4: // turn straight
				if (m_pi->turnToFace(0)) {
					auton_phase++;
				}
				break;
			case 5: // drive to wall
				if (driveToCoordinates(enter_target_x, 0.762, 0)) {
					auton_phase++;
				}
				break;
			case 6: //delivers balls
				m_ballIntake->Yeet();
				auton_phase++;
				break;
			case 7: //give us a little space to turn around (can be lowered)
				if (driveToCoordinates(0, 0.762, 0)) {
					auton_phase++;
				}
				break;
			case 8: //turn around
				if (m_pi->turnToFace(PI)) {
					auton_phase++;
				}
				break;		
			case 9: //face exit
				if (m_pi->turnToFace(exit_target_ang)) {
					auton_phase++;
				}
				break;
			case 10: //drive towards exit
				if (driveToCoordinates(exit_target_x, exit_target_y, exit_target_ang)) {
					auton_phase++;
					if (!pickupBallEnd)
						auton_phase++;
				}
				break;
			case 11: //collect balls if warrented
				//I don't know if the followBall will work the way I put it
				if (m_pi->FollowBall()) {
					m_ballIntake->StartIntake();
					if (m_ballIntake->GetBallCount() == 3)
						auton_phase++;
				}
				break;
			// default: //end
			// 	//return true;
			// 	break;
			// add more once we get there
		}
	}
	
	frc::SmartDashboard::PutNumber ("Auton Phase", auton_phase);
	//frc::SmartDashboard::PutNumber("enterance angle offset", angleOffset(enter_target_ang) * 180 / PI);
	//frc::SmartDashboard::PutNumber("exit angle offset", angleOffset(exit_target_ang) * 180 / PI);
	frc::SmartDashboard::PutNumber("ahrs_ang", m_ahrs->GetAngle() + 90);
	frc::SmartDashboard::PutNumber("enter_target_ang", enter_target_ang);
	frc::SmartDashboard::PutNumber("exit_target_ang", exit_target_ang);
	frc::SmartDashboard::PutNumber("enter_target_x", enter_target_x);
	frc::SmartDashboard::PutNumber("exit_target_x", exit_target_x);
	frc::SmartDashboard::PutNumber("enter_target_y", enter_target_y);
	frc::SmartDashboard::PutNumber("exit_target_y", exit_target_y);
	frc::SmartDashboard::PutNumber("displ_x", m_ahrs->GetDisplacementX());
	frc::SmartDashboard::PutNumber("displ_y", m_ahrs->GetDisplacementY());
	frc::SmartDashboard::PutNumber("enter dist offset", sqrt(pow(enter_target_x - m_ahrs->GetDisplacementX(), 2) + pow(enter_target_y - m_ahrs->GetDisplacementY(), 2)));
	frc::SmartDashboard::PutNumber("exit dist offset", sqrt(pow(exit_target_x - m_ahrs->GetDisplacementX(), 2) + pow(exit_target_y - m_ahrs->GetDisplacementY(), 2)));

	//return false;
}

bool Auton::driveToCoordinates(double x, double y, double angle)
{
	SmartDashboard::PutNumber("angle offset", m_pi->angleOffset(angle) * 180 / PI);
	SmartDashboard::PutNumber("dist offset", sqrt(pow(x - m_ahrs->GetDisplacementX(), 2) + pow(y - m_ahrs->GetDisplacementY(), 2))); // this is not correct currently
	return m_pi->driveAdjusted(m_pi->angleOffset(angle), sqrt(pow(x - m_ahrs->GetDisplacementX(), 2) + pow(y - m_ahrs->GetDisplacementY(), 2)), angleOffsetCoefficient);
}