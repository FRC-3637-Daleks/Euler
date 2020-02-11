#include "Euler.h"

Ball_Follow::Ball_Follow(DalekDrive *drive)
{
	m_drive = drive;
	frc::SmartDashboard::PutNumber("Ratio", 0);
	frc::SmartDashboard::PutNumber("Magnatude", 0);
}

bool Ball_Follow::FollowBall()
{
	int xOffset = frc::SmartDashboard::GetNumber("X Offset", 100000);
    double distance = frc::SmartDashboard::GetNumber("Distance", -1);
	if (xOffset == 100000 || distance == -1) {
		return false;
	}
    double ratio = exp(offsetCoefficient * xOffset / distance);
    frc::SmartDashboard::PutNumber("Ratio", ratio);
	double magnatude = distance / 4.0;
	if (magnatude > 1) {
		magnatude = 1;
	}
	frc::SmartDashboard::PutNumber("Magnatude", magnatude);
	if (ratio < 1) {
		m_drive->TankDrive(magnatude, magnatude * ratio, false);
	} else {
		m_drive->TankDrive(magnatude / ratio, magnatude, false);
	}
	return true;
}