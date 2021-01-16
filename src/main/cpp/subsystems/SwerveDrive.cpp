/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <math.h>

#include "subsystems/SwerveDrive.h"

SwerveDrive::SwerveDrive():
mWheelFL{kFLDrive, kFLTurn, kFLEnc, kFLOffset, 1},
mWheelFR{kFRDrive, kFRTurn, kFREnc, kFROffset, 2}, 
mWheelBR{kBRDrive, kBRTurn, kBREnc, kBROffset, 4},
mWheelBL{kBLDrive, kBLTurn, kBLEnc, kBLOffset, 3} {
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

void SwerveDrive::testSwerve() { // Each wheel should 
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

#ifdef GYRO
int SwerveDrive::readOffset() {
    offset = 0;
    negativeOffset = false;
    mSerial.Write("\n");
    mSerial.Read(rawOffset, 10); //Get initial value
    while (rawOffset[0] != '~') { //Repeat until you get a valid gyro value
        //mSerial.Write("\n");
        while (mSerial.GetBytesReceived() == 0) {
            //mSerial.Write("\n");
        } //Wait for there to be a gyro value from the arduino
        while (mSerial.GetBytesReceived() != 0) { //Get the latest value
            mSerial.Read(rawOffset, 10);
            printf("%s\n", rawOffset);
        }
    }
    while (mSerial.GetBytesReceived() != 0) { //Get the latest value
        mSerial.Read(rawOffset, 10);
    }
    printf("Gyro says: %s\n", rawOffset);
    for (int i = 1; i < 10; i++) {
        if (rawOffset[i] == '.') {
            break;
        }
        else if (rawOffset[i] == '-') {
            negativeOffset = true;
        }
        else {
            offset *= 10;
            offset += rawOffset[i] - '0';
        }
    }
    if (!negativeOffset) { // The gyro is the opposite direction so we usually have to flip it
        offset = -offset;
    }
    return offset;
}
#endif

void SwerveDrive::vectorSwerve() {
#ifdef GYRO
    offset = readOffset();
    printf("Gyro reading: %d\n", offset);
#endif
    mDriveVector.x = mpDriverController->GetRawAxis(4);
    mDriveVector.y = -mpDriverController->GetRawAxis(5);
    mDriveVector.Rotate(360-offset); //Factor in gyroscope value (subtract from 360 to go from counterclockwise to clockwise)
    //mTurnVector.x = cos((mpDriverController->GetRawAxis(0) * 45) + 45) * 57.2958; //I don't think this is gonna work but it's worth a shot
    //mTurnVector.y = sin((mpDriverController->GetRawAxis(0) * 45) + 45) * 57.2958; //No it isnt
    mTurnVector.x = mpDriverController->GetRawAxis(0);
    mTurnVector.y = mpDriverController->GetRawAxis(0);
    printf("Turn speed: %f\n",mTurnVector.x);
    for (int i = 0; i < 4; i++) { //For each wheel:
        mSumVector.x = (mDriveVector.x + mTurnVector.x) / 2; //Add the two vectors to get one final vector
        mSumVector.y = (mDriveVector.y + mTurnVector.y) / 2;
        targetEncoder[i] = angleCalc(mSumVector.x, mSumVector.y); //Calculate the angle of this vector
        targetSpeed[i] = mSumVector.Magnitude() * kMaxSpeed; //Scale the speed of the wheels
        //targetSpeed[i] = kMaxSpeed * mpDriverController->GetRawAxis(3) - kMaxSpeed * mpDriverController->GetRawAxis(2);
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
