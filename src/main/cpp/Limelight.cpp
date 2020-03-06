#include "Euler.h"

Limelight::Limelight(DalekDrive *drive) {
    m_drive = drive;
}

void Limelight::Deposit() {
    SmartDashboard::PutNumber("tv", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0));
    SmartDashboard::PutNumber("tshort", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tshort", 0.0));
    double limeAngle = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);
    SmartDashboard::PutNumber("tx", limeAngle);
    
    if(limeAngle > 0) {
      m_drive->TankDrive(0.15, -0.15, false);
    }
    else if(limeAngle < 0) {
      m_drive->TankDrive(-0.15, 0.15, false);
    }
    else {
      m_drive->TankDrive(0.15, 0.15, false);
    }
    SmartDashboard::PutNumber("Limelight Angle", limeAngle);

}