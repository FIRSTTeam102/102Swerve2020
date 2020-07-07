/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveWheel.h"

SwerveWheel::SwerveWheel(int drivePort, int turnPort, int encAPort, int encBPort, int angleScale) : mDriveMotor{drivePort}, mTurnMotor{turnPort}, mEnc{encAPort, encBPort}, mAngleScale{angleScale} {
    
}

void SwerveWheel::setAngle(double angle) {
    target = angle;
    min = target - kSwerveThresh;
    if (min < 0) {
        min += mAngleScale;
    }
    max = target + kSwerveThresh;
    if (max > mAngleScale) {
        max -= mAngleScale;
    }
}

// This method will be called once per scheduler run
void SwerveWheel::Periodic() {
    //Keep within usable bounds
    if (mEnc.Get() >= mAngleScale || mEnc.Get() <= -mAngleScale) {
        mEnc.Reset();
    }
    
    //Set wheels to target directions
    scaledPos = (double) mEnc.Get() / (double) mAngleScale * 360.0;
    posCurrent = (scaledPos + 360) % 360;
    if (min < max) {
        if (posCurrent > min && posCurrent < max) {
            mTurnMotor.Set(0);
        }
        //Implement a way to go faster direction
        else {
            mTurnMotor.Set(0.5);
        }
    }
    else if (target < 180) {
        if (posCurrent > min + 360 || posCurrent < max) {
            mTurnMotor.Set(0);
        }
        //Implement a way to go faster direction
        else {
            mTurnMotor.Set(0.5);
        }
    }
    else {
        if (posCurrent > min || posCurrent < max - 360) {
            mTurnMotor.Set(0);
        }
        //Implement a way to go faster direction
        else {
            mTurnMotor.Set(0.5);
        }
    }
}
