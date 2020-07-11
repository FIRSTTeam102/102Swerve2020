/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveWheel.h"

SwerveWheel::SwerveWheel(int drivePort, int turnPort, int encAPort, int encBPort, int angleScale, int id = 0) : mDriveMotor{drivePort}, mTurnMotor{turnPort}, mEnc{encAPort, encBPort}, mAngleScale{angleScale}, mId{id} {
    
}

void SwerveWheel::setAngle(double angle) {
    target = 360-angle;
    min = target - kSwerveThresh;
    if (min < 0) {
        min += mAngleScale;
    }
    max = target + kSwerveThresh;
    if (max > mAngleScale) {
        max -= mAngleScale;
    }
}

void SwerveWheel::setSpeed(double speed) { //Gears on the left (away from battery)
    if (!inverted) {
        mDriveMotor.Set(speed);
    }
    else {
        mDriveMotor.Set(-speed);
    }
}

void SwerveWheel::resetEnc() {
    mEnc.Reset();
}

int SwerveWheel::circScale(int i) {
    return (i + 720) % 360;
}

// This method will be called once per scheduler run
void SwerveWheel::Periodic() {
    //Keep within usable bounds
    if (mEnc.Get() >= mAngleScale || mEnc.Get() <= -mAngleScale) {
        mEnc.Reset();
    }
    
    //Set wheels to target directions
    /*scaledPos = (double) mEnc.Get() / (double) mAngleScale * 360.0;
    posCurrent = circScale(scaledPos);
    if (min < max && (posCurrent > min && posCurrent < max)) {
        mTurnMotor.Set(0);
    }
    else if (target < 180 && (posCurrent > min + 360 || posCurrent < max)) {
        mTurnMotor.Set(0);
    }
    else if (target >= 180 && (posCurrent > min || posCurrent < max - 360)) {
        mTurnMotor.Set(0);
    }
    else { //Go the faster way to get to correct angle
        scaledTarg = circScale(target - posCurrent);
        if (scaledTarg > 90 && scaledTarg < 270) { //Sometimes it is faster to make the wheel go in reverse in order to turn less
            scaledTarg -= 180;
            scaledTarg = circScale(scaledTarg);
            inverted = !inverted;
        }
        if (scaledTarg < 180) {
            mTurnMotor.Set(0.5); //clockwise
        }
        else {
            mTurnMotor.Set(-0.5); //counterclockwise
        }
    }*/
    scaledPos = (double) mEnc.Get() / (double) mAngleScale * 360.0;
    posCurrent = circScale(scaledPos);
    scaledTarg = circScale(target - posCurrent);
    if (scaledTarg > 90 && scaledTarg < 270) {
		scaledTarg += 180;
		scaledTarg = (scaledTarg + 720) % 360;
		inverted = true;
	}
    else {
        inverted = false;
    }
	if (scaledTarg > 180) {
        scaledTarg -= 360;
    }
	mTurnMotor.Set(kMaxSpeed * (double) scaledTarg / 90.0);
    printf("Wheel #%d Going to: %d   At: %d   Speed: %f\n", mId, target, scaledPos, kMaxSpeed * (double) scaledTarg / 90.0);
}
