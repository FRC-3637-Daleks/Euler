#pragma once

#define offsetCoefficient	0.0208

using namespace std;
using namespace frc;

class Auton {
	public:
	SendableChooser<string> m_chooser;
	string m_autoSelected;
    string kAutoNameDefault;
    string kAutoNameCustom;

	Auton(DalekDrive *drive);

	bool FollowBall(); // returns false if ball not found
	
	private:
	DalekDrive *m_drive;
};