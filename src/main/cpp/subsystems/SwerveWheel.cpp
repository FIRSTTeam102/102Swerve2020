/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveWheel.h"

SwerveWheel::SwerveWheel(int drivePort, int turnPort, int encPort, int encOffset, int id = 0) : mDriveMotor{drivePort}, mTurnMotor{turnPort}, mEnc{encPort}, mAngleOffset{encOffset}, mId{id} {
    
}

void SwerveWheel::setAngle(double angle) {
    target = 360-angle;
}

void SwerveWheel::setSpeed(double speed) { //Gears on the left (away from battery)
    if (!inverted) {
        mDriveMotor.Set(speed);
    }
    else {
        mDriveMotor.Set(-speed);
    }
}

int SwerveWheel::circScale(int i) {
    return (i + 720) % 360;
}

// This method will be called once per scheduler run
void SwerveWheel::Periodic() {
    scaledPos = (double) (mEnc.GetValue() - mAngleOffset) * 360.0 / 4096.0;
    posCurrent = circScale(scaledPos);
    scaledTarg = circScale(target - posCurrent);
    if (scaledTarg > 90 && scaledTarg < 270) {
		scaledTarg += 180;
		scaledTarg = circScale(scaledTarg);
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
