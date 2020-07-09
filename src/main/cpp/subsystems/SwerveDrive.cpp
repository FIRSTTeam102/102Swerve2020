/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <math.h>

#include "subsystems/SwerveDrive.h"

SwerveDrive::SwerveDrive():
mWheelFL{kFLDrive, kFLTurn, kFLEncA, kFLEncB, kFLAngleScale, 1},
mWheelFR{kFRDrive, kFRTurn, kFREncA, kFREncB, kFRAngleScale, 2}, 
mWheelBR{kBRDrive, kBRTurn, kBREncA, kBREncB, kBRAngleScale, 4},
mWheelBL{kBLDrive, kBLTurn, kBLEncA, kBLEncB, kBLAngleScale, 3} {
#ifdef GYRO
    mSerial.EnableTermination();
    mSerial.Write("Start\n");
#endif
}

double SwerveDrive::angleCalc(double x, double y){
  double angle;
  if (x == 0 && y == 0)
      return -1;
  if (y == 0)
      angle = 90.0;
  else
      angle = atanf(abs(x)/abs(y)) * 57.2958; //may be asinf, not quite sure yet
  if (x < 0 && y < 0) {
      angle += 180;
  }
  else if (x < 0) {
      angle += 180 + (2 * (90 - angle));
      if (y < 0)
          angle -= 2 * (90 - angle);
  }
  else if (y < 0)
      angle += 2 * (90 - angle);
  return angle;
}

double SwerveDrive::pythag(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

void SwerveDrive::testSwerve() {
    angle = angleCalc(mpDriverController->GetRawAxis(0), -mpDriverController->GetRawAxis(1));
    printf("Set all to angle: %d\n", angle);
    mWheelFL.setAngle(angle);
    mWheelFR.setAngle(angle);
    mWheelBR.setAngle(angle);
    mWheelBL.setAngle(angle);

    //speed = kMaxSpeed * pythag(mpDriverController->GetRawAxis(0), -mpDriverController->GetRawAxis(1));
    speed = kMaxSpeed * mpDriverController->GetRawAxis(3) - kMaxSpeed * mpDriverController->GetRawAxis(2);
    //speed = 0;
    mWheelFL.setSpeed(speed);
    mWheelFR.setSpeed(speed);
    mWheelBR.setSpeed(speed);
    mWheelBL.setSpeed(speed);
    printf("Set to speed: %f\n", speed);
}

void SwerveDrive::vectorSwerve() { //UNTESTED
    mDriveVector.x = mpDriverController->GetRawAxis(0);
    mDriveVector.y = -mpDriverController->GetRawAxis(1);
    mDriveVector.Rotate(360-offset); //Factor in gyroscope value (subtract from 360 to go from counterclockwise to clockwise)
    mTurnVector.x = cos((mpDriverController->GetRawAxis(0) * 45) + 45) * 57.2958; //I don't think this is gonna work but it's worth a shot
    mTurnVector.y = sin((mpDriverController->GetRawAxis(0) * 45) + 45) * 57.2958; //^^
    for (int i = 0; i < 4; i++) { //For each wheel:
        mSumVector.x = (mDriveVector.x + mTurnVector.x) / 2; //Add the two vectors to get one final vector
        mSumVector.y = (mDriveVector.y + mTurnVector.y) / 2;
        targetEncoder[i] = angleCalc(mDriveVector.x, mDriveVector.y); //Calculate the angle of this vector
        targetSpeed[i] = mDriveVector.Magnitude() * kMaxSpeed; //Scale the speed of the wheels
        mTurnVector.Rotate(-90.0); //Rotate the vector clockwise 90 degrees
    }
    mWheelFL.setAngle(targetEncoder[0]);
    mWheelFR.setAngle(targetEncoder[1]);
    mWheelBR.setAngle(targetEncoder[2]);
    mWheelBL.setAngle(targetEncoder[3]);
    mWheelFL.setSpeed(targetSpeed[0]);
    mWheelFR.setSpeed(targetSpeed[1]);
    mWheelBR.setSpeed(targetSpeed[2]);
    mWheelBL.setSpeed(targetSpeed[3]);
}


// This method will be called once per scheduler run
void SwerveDrive::Periodic() {}
