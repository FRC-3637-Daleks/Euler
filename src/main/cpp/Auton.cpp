#include "Euler.h"

Auton::Auton(DalekDrive *drive)
{
	kAutoNameDefault = "Default";
    kAutoNameCustom = "My Auto";

	m_drive = drive;

	m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
	m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

bool Auton::FollowBall()
{
	int xOffset = frc::SmartDashboard::GetNumber("X Offset", 10000);
    int distance = frc::SmartDashboard::GetNumber("Distance", 10000);
	if (xOffset == 10000 || distance == 10000) {
		return false;
	}
    double ratio = exp(offsetCoefficient * xOffset / distance);
    frc::SmartDashboard::PutNumber("Ratio", ratio);
	double magnatude = .25;
	frc::SmartDashboard::PutNumber("Magnatude", ratio);
	if (ratio < 1) {
		m_drive->TankDrive(magnatude, magnatude / ratio, false);
	} else {
		m_drive->TankDrive(magnatude / ratio, magnatude, false);
	}
	return true;
}