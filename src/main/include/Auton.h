// some of this should be in the DalekDrive class, but whatever

#pragma once
// literally every single #define is a guess, so test one at a time
#define pixelOffsetCoefficient	0.0208 // this is an estimate, however it was using feet, so change to meters
#define angleOffsetCoefficient	0.01
#define distanceCoefficient		0.3
#define turningErrorThreshold	2
#define distanceErrorThreshold	0.2
#define pTurn					0.1
#define iTurn					0 // probably unnecessary and won't be used
#define dTurn					0 // probably unnecessary and won't be used
#define maxTurnSpeed			0.5

using namespace std;
using namespace frc;

// all angles are in radians
// all measurements are in meters
class Auton {
	public:
	Auton(DalekDrive *drive);
	
	void AutonCase(int begin, int end); // this must be called before AutonDrive()
	void AutonDrive();
	bool FollowBall(); // returns false if ball not found [maybe change this to print to dashboard, then return if we can pick up a ball]

	private:
	DalekDrive *m_drive;
	AHRS *m_ahrs;
	// eventually will need delivery mechanism

	double p_temp, i_temp, d_temp, target_x, target_y, target_ang;
	int auton_phase;

	bool turnToFace(double angle);
	bool driveToCoordinates(double x, double y);
	bool driveAdjusted(double offset, double distance, double coefficient);
	double angleOffset(double angle);

};