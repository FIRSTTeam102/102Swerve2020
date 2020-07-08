/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/PWMTalonSRX.h>
#include <frc/Encoder.h>

#include "Constants.h"

class SwerveWheel : public frc2::SubsystemBase {
 public:
  SwerveWheel(int drivePort, int turnPort, int encAPort, int encBPort, int angleScale, int id);

  void setAngle(double angle);
  void setSpeed(double speed);
  void resetEnc();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  frc::PWMTalonSRX mDriveMotor;
  frc::PWMTalonSRX mTurnMotor;
  frc::Encoder mEnc;
  int mAngleScale;
  int target = 0;
  int min, max;
  int scaledPos, posCurrent;
  int mId;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
