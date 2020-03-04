#include "Euler.h"

RaspberryPi::RaspberryPi(DalekDrive *drive, AHRS * ahrs) {
    m_drive			= drive;
	m_ahrs         	= ahrs;
    
    p_temp = 0; i_temp = 0; d_temp = 0;
}

bool RaspberryPi::FollowBall()
{
	int offset = frc::SmartDashboard::GetNumber("X Offset", 100000), distance = frc::SmartDashboard::GetNumber("Distance", -1);
	if (offset == 100000 || distance == -1) {
		m_drive->TankDrive(0.0, 0.0, false);
		return false;
	}
    return driveAdjusted(offset, distance, pixelOffsetCoefficient);
}

bool RaspberryPi::turnToFace(double angle)
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

double RaspberryPi::angleOffset(double angle)
{
	double offset = fmod(angle - (m_ahrs->GetAngle()) * PI / 180, 2 * PI);
	//Josh's function = fmod(angle - (m_ahrs->GetAngle()) * PI / 180, 360)
	if (offset > PI) {
		offset -= PI * 2;
	}
	return offset;
}

bool RaspberryPi::driveAdjusted(double offset, double distance, double coefficient)
{
	if (distance < distanceErrorThreshold) {
		m_drive->TankDrive(0.0, 0.0, false);
		return true;
	}
	double ratio = exp(coefficient * offset / distance), magnatude = (distance + .3) / -8.0; // this needs to be changed
	// seans formula ->  = -.4 / (1 + 4 * exp(-distanceCoefficient * distance));
	if (magnatude < -.5) {
		magnatude = -.5;
	}
	if (ratio < 1) {
		m_drive->TankDrive(magnatude, magnatude * ratio, false);
	} else {
		m_drive->TankDrive(magnatude / ratio, magnatude, false);
	}
	return false;
}