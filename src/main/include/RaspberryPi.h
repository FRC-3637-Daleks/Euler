#pragma once

#include "Euler.h"

using namespace std;
using namespace frc;

#define angleOffsetCoefficient	0.01

class RaspberryPi {
	public:
    RaspberryPi(DalekDrive *drive, AHRS * ahrs);

	bool FollowBall(); // returns false if ball not found [maybe change this to print to dashboard, then return if we can pick up a ball]
    bool turnToFace(double angle);
    double angleOffset(double angle);
	bool driveAdjusted(double offset, double distance, double coefficient);

	private:
    DalekDrive *m_drive;
	AHRS *m_ahrs;

    double p_temp, i_temp, d_temp, target_x, target_y, target_ang;
};