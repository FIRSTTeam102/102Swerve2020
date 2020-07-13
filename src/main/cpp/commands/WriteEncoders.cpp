/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/WriteEncoders.h"

WriteEncoders::WriteEncoders() {
  // Use addRequirements() here to declare subsystem dependencies.
  mpEncFile = fopen("deploy/values.txt", "w");
}

// Called when the command is initially scheduled.
void WriteEncoders::Initialize() {
  fprintf(mpEncFile, "%d %d\n%d %d\n%d %d\n%d %d", FLAng, FLInv, FRAng, FRInv, BRAng, BRInv, BLAng, BLInv);
}

// Called repeatedly when this Command is scheduled to run
void WriteEncoders::Execute() {}

// Called once the command ends or is interrupted.
void WriteEncoders::End(bool interrupted) {
  fclose(mpEncFile);
}

// Returns true when the command should end.
bool WriteEncoders::IsFinished() { return true; }
