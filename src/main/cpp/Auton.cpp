#include "Euler.h"

Auton::Auton(DalekDrive *drive)
{
	m_drive			= drive;
	m_ahrs         	= new AHRS(SPI::Port::kMXP);
	m_ahrs->Reset();
	m_ahrs->ResetDisplacement();

	p_temp = 0; i_temp = 0; d_temp = 0;
	auton_phase = 0;
}

void Auton::AutonCase(int begin, int end)
{
	switch (begin) {
		case 0:
		target_x = 2; // obviously change all of these as needed
		target_y = 2; // this can probably be taken out of the ifs if its the same every time
		break;
		case 1:
		target_x = 0;
		target_y = 0;
		break;
		case 2:
		target_x = 0;
		target_y = 0;
		break;
	}
	target_ang = atan2(target_y, target_x);
	// here set up what happens at the end (after delivery)
}

void Auton::AutonDrive()
{
	switch (auton_phase) {
		case 0: // turn to target
		if (turnToFace(target_ang)) {
			auton_phase++;
		}
		break;
		case 1: // drive to target
		if (driveToCoordinates(target_x, target_y)) {
			auton_phase++;;
		}
		break;
		case 2: // turn straight
		if (turnToFace(0)) {
			auton_phase++;
		}
		break;
		case 3: // drive to wall

		break;
		// add more once we get there
	}
}

bool Auton::FollowBall()
{
	int offset = frc::SmartDashboard::GetNumber("X Offset", 100000), distance = frc::SmartDashboard::GetNumber("Distance", -1);
	if (offset == 100000 || distance == -1) {
		m_drive->TankDrive(0.0, 0.0, false);
		return false;
	}
    return driveAdjusted(offset, distance, pixelOffsetCoefficient);
}

bool Auton::turnToFace(double angle)
{
	double prev_error = p_temp;
	p_temp = angleOffset(angle);
	if (abs(p_temp) < turningErrorThreshold) {
		return true;
	}
	i_temp += p_temp;
	d_temp = p_temp - prev_error;
	double pid_result = pTurn * p_temp + iTurn * i_temp + dTurn * d_temp;
	if (pid_result > 0) {
		m_drive->TankDrive(min(pid_result, maxTurnSpeed), -min(pid_result, maxTurnSpeed), false);
	} else {
		m_drive->TankDrive(max(pid_result, -maxTurnSpeed), -max(pid_result, -maxTurnSpeed), false);
	}
	return false;
}

bool Auton::driveToCoordinates(double x, double y)
{
	return driveAdjusted(angleOffset(target_ang), sqrt(pow(target_x - m_ahrs->GetDisplacementX(), 2) + pow(target_y - m_ahrs->GetDisplacementY(), 2)), angleOffsetCoefficient);
}

bool Auton::driveAdjusted(double offset, double distance, double coefficient)
{
	if (distance < distanceErrorThreshold) {
		m_drive->TankDrive(0.0, 0.0, false);
		return true;
	}
	double ratio = exp(coefficient * offset / distance), magnatude = -.2; // keep this for now, change later
	// seans formula ->  = -.4 / (1 + 4 * exp(-distanceCoefficient * distance));
	if (ratio < 1) {
		m_drive->TankDrive(magnatude, magnatude * ratio, false);
	} else {
		m_drive->TankDrive(magnatude / ratio, magnatude, false);
	}
	return false;
}

double Auton::angleOffset(double angle)
{
	double offset = fmod(angle - (m_ahrs->GetAngle() + 90) * PI / 180, 360);
	if (offset > PI) {
		offset -= PI * 2;
	}
	return offset;
}