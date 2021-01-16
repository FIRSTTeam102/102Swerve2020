/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#define GYRO

#include <math.h>

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/Vector2d.h>
#include <frc/XboxController.h>
#include <frc/SerialPort.h>

#include "subsystems/SwerveWheel.h"
#include "Constants.h"

class SwerveDrive : public frc2::SubsystemBase {
 public:
  SwerveDrive();
  void setController(frc::XboxController *pDriverController) {
    mpDriverController = pDriverController;
  }

  void testSwerve();
  void vectorSwerve();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  double pythag(double x, double y);
  double angleCalc(double x, double y);
  
#ifdef GYRO
  int readOffset();
#endif

  int angle;
  double speed;

  frc::XboxController *mpDriverController;
#ifdef GYRO
  frc::SerialPort mSerial{115200, frc::SerialPort::kUSB};
#endif

  SwerveWheel mWheelFL;
  SwerveWheel mWheelFR;
  SwerveWheel mWheelBR;
  SwerveWheel mWheelBL;

  int targetEncoder[4];
  float targetSpeed[4], turnMagnitude[4];
  char rawOffset[10] = {0};
  int offset = 0;
  bool negativeOffset = false;
  frc::Vector2d mDriveVector;
  frc::Vector2d mTurnVector;
  frc::Vector2d mSumVector;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
