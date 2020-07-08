/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>

#include "subsystems/SwerveWheel.h"
#include "Constants.h"

class SwerveDrive : public frc2::SubsystemBase {
 public:
  SwerveDrive();
  void setController(frc::XboxController *pDriverController) {
    mpDriverController = pDriverController;
  }
  void resetEncs() {
    mWheelFL.resetEnc();
    mWheelFR.resetEnc();
    mWheelBR.resetEnc();
    mWheelBL.resetEnc();
  }

  void testSwerve();
  void vectorSwerve();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  double angleCalc(double x, double y);
  int angle;
  double speed;

  frc::XboxController *mpDriverController;

  SwerveWheel mWheelFL{kFLDrive, kFLTurn, kFLEncA, kFLEncB, kFLAngleScale};
  SwerveWheel mWheelFR{kFRDrive, kFRTurn, kFREncA, kFREncB, kFRAngleScale};
  SwerveWheel mWheelBR{kBRDrive, kBRTurn, kBREncA, kBREncB, kBRAngleScale};
  SwerveWheel mWheelBL{kBLDrive, kBLTurn, kBLEncA, kBLEncB, kBLAngleScale};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
