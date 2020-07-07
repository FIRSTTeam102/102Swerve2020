/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

// Motor Ports

const int kFLDrive = 0;
const int kFLTurn = 1;
const int kFRDrive = 2;
const int kFRTurn = 3;
const int kBRDrive = 4;
const int kBRTurn = 5;
const int kBLDrive = 6;
const int kBLTurn = 7;


// Encoder Ports

const int kFLEncA = 0;
const int kFLEncB = 1;
const int kFREncA = 2;
const int kFREncB = 3;
const int kBREncA = 4;
const int kBREncB = 5;
const int kBLEncA = 6;
const int kBLEncB = 7;


// Calibration Values

const int kFLAngleScale = 360;
const int kFRAngleScale = 360;
const int kBRAngleScale = 360;
const int kBLAngleScale = 360;

const int kSwerveThresh = 15;


// Swerve Mode

const int kSwerveMode = 0;