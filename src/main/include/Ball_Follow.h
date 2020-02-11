#pragma once

#define offsetCoefficient	0.0208

using namespace std;
using namespace frc;

class Ball_Follow {
	public:
	Ball_Follow(DalekDrive *drive);
	
	bool FollowBall(); // returns false if ball not found
	
	private:
	DalekDrive *m_drive;
};