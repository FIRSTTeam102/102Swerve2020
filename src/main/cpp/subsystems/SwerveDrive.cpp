/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SwerveDrive.h"

SwerveDrive::SwerveDrive() {}

double SwerveDrive::angleCalc(double x, double y) {
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

void SwerveDrive::testSwerve() {
    int angle = angleCalc(mpDriverController->GetRawAxis(0), mpDriverController->GetRawAxis(1));
    mWheelFL.setAngle(angle);
    mWheelFR.setAngle(angle);
    mWheelBR.setAngle(angle);
    mWheelBL.setAngle(angle);
}

void SwerveDrive::vectorSwerve() {
    // Yet to be added
}


// This method will be called once per scheduler run
void SwerveDrive::Periodic() {}
