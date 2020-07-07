/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunSwerve.h"

RunSwerve::RunSwerve() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mpSwerveDrive);
}

// Called when the command is initially scheduled.
void RunSwerve::Initialize() {
  mpSwerveDrive.resetEncs();
}

// Called repeatedly when this Command is scheduled to run
void RunSwerve::Execute() {
  switch (kSwerveMode) {
   case 0:
    mpSwerveDrive.testSwerve();
    return;
   case 1:
    mpSwerveDrive.vectorSwerve();
    return;
  }
}

// Called once the command ends or is interrupted.
void RunSwerve::End(bool interrupted) {}

// Returns true when the command should end.
bool RunSwerve::IsFinished() { return false; }
