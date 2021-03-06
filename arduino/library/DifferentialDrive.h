//-*- mode: c -*-
/* 
 * NAME
 *     DifferentialDrive
 * PURPOSE
 *     Controls drivers for motors on differential drive rover (wheelchair, hoverboard, balancebot etc)
 * PROTOCOL FROM HOST
 *     Normally none if this is controlled by the Helm. Check sub-classes.
 * PROTOCOL TO HOST
 *     Normally none if this is controlled by the Helm. Check sub-classes.
 * AUTHOR
 *     Scott BARNES 2019. IP freely on non-commercial applications.
 * PHILOSOPHY
 *     Power not speed. Speed is a Helm concept.
 */

#ifndef DifferentialDrive_h
#define DifferentialDrive_h

#include <Arduino.h>
#include "King.h"
#include "DifferentialDrive.h"

class DifferentialDrive : public King {
private:
    int64_t leftMotorCount  = 0; // Iff we have encoders. Note that on BLDC motors, this is probably 120 degrees of the wheel - ie very course.
    int64_t rightMotorCount = 0; // Iff we have encoders. Note that on BLDC motors, this is probably 120 degrees of the wheel - ie very course.
 protected:
    int reportIntervalMs = 0;    // Report for debugging. 0 => no reporting
public:
    int currentLeftMotorPower  = 0;
    int currentRightMotorPower = 0;
    int currentLeftMotorDirection = 0;
    int currentRightMotorDirection = 0;
    byte reverseLeftMotor = false;     // Whether the motor is reversed (ie must be run backwards).
    byte reverseRightMotor = false;    // Whether the motor is reversed (ie must be run backwards).

    DifferentialDrive(byte reverseLeftMotor, byte reverseRightMotor) {
        this->reverseLeftMotor = reverseLeftMotor;
        this->reverseRightMotor = reverseRightMotor;
    };
    
    virtual void setMotorPowers(int leftMotorSpeed, int rightMotorSpeed);
    void setReportInterval(int reportIntervalMs) { this->reportIntervalMs = reportIntervalMs; };
};

#endif /* DifferentialDrive_h */
