//"""Includes"""

#include <Arduino.h>
#include <Camera.h>
#include <Compass.h>
#include <Define.h>
#include <MotorController.h>
#include <Motors.h>
#include <Debug.h>
#include <Role.h>

// """Library Name Allocation"""

Role role;
Camera camera;
MotorController Motor;
Debug debug;
Compass compass;

//"""Variable Naming"""
const int GoalAcc = 7;

void setup() {
  Serial.begin(9600);
  // Wire.begin();
  camera.setup();
  Motor.Setup();
  //compass.compassSetup();
  //compass.calibrate();
}
void loop() {
  //"""Data Refreshing"""
  // debug.motorTest();
  camera.update();
  //compass.updateGyro();
  //"""Angle/Correction Calculation"""
  camera.angleCalc();
  //compass.compassCalc();
  //"""Motor Movement Code"""
  Motor.Move(camera.bAngle, 0, 255);
  // role.action(255, 0, 1, 0);
  //Parameters:
  //First parameter is the speed of the robot.
  //Second parameter is the state of the robot. 0 means it is attacking, 1 means it is defending.
  //Third parameter is the direction of the game. 0 means the direction is yellow, 1 means the direction is blue.
  //Fourth parameter is the fake angle. If it is set to -1, it is off. Otherwise, it is the fake angle of the ball.
} 
