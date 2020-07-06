/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveWheel.h"

SwerveWheel::SwerveWheel(int drivePort, int turnPort, int encAPort, int encBPort) : mDriveMotor{drivePort}, mTurnMotor{turnPort}, mEnc{encAPort, encBPort} {
    
}

// This method will be called once per scheduler run
void SwerveWheel::Periodic() {}
