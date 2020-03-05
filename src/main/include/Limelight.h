#pragma once

#include "Euler.h"

class Limelight {
    public:
        Limelight(DalekDrive *drive);
        void Deposit();
    private:
        DalekDrive *m_drive;
};