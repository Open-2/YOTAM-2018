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
  // debug.setCamera(&camera);
  Motor.Setup();
  // compass.compassSetup();
  // compass.calibrate();
}
void loop() {
  Motor.Move(0, 0, 255);
  // Motor.Setup();
  // debug.motorTest();
  // //"""Data Refreshing"""
  // camera.update();
  // camera.Test();
  // Serial.print(Serial3.read());
  // debug.cameraTest();
  // // debug.motorTest();
  // compass.updateGyro();
  // //"""Angle/Correction Calculation"""
  // camera.angleCalc();
  // camera.Test();
  // compass.compassCalc();
  // //"""Motor Movement Code"""
  // Motor.Move(camera.bAngle, 0, 255);
  // Motor.Move(45, 0, 255);
  // Motor.Move(0, compass.correction, 0);
  // debug.motorTest();
  // Motor.Move(45, 0, 255);
  // Motor.Move(0, -115, 255);
  // Motor.Move(0, camera.yGoalAngle, 0);
  // Motor.Move(0, 0, 70);
  // Motor.Move(0, 0,  255);
  // role.action(255, 0, -1, 10, 0, 0);
  //Parameters:
  //First parameter is the speed of the robot.
  //Second parameter is the state of the robot. 0 means it is attacking, 1 means it is defending.
  //Third parameter is the fake angle. If it is set to -1, it is off. Otherwise, it is the fake angle of the ball.
  //Fourth parameter is the distance to the ball.
  //Fifth parameter is the direction of the game. 0 means the direction is yellow, 1 means the direction is blue.
  //Sixth parameter is the compass correction toggle. 0 means off, 1 means on.
  //Note: Correction max is 110 and minimum is variable
} 
