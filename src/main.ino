//All the includes go here:

#include <Arduino.h>
#include <Camera.h>
#include <Compass.h>
#include <Define.h>
#include <MotorController.h>
#include <Motors.h>
#include <Debug.h>
#include <Role.h>


// """All the library naming goes here:"""

Role role;
Camera camera;
MotorController Motor;
Debug debug;
Compass compass;

// """All the variable naming goes here:"""
int bAngle = 0;
const int GoalAcc = 7;

void setup() {
  Serial.begin(9600);
  camera.setup();
  Motor.Setup();
  // compass.compassSetup();
  // compass.calibrate();
  // Wire.begin();
}
void loop() {
  //"""Constant Data Refreshing and Movement"""
  // debug.cameraTest();
  camera.update();
  //compass.updateGyro();

  //"""Compass Correction Code"""
  //compass.compassCalc();

  // """Goal Correction Code"""

  //"""Motor Movement Code"""
  camera.angleCalc();

  role.action(255, 0, 1);
  //Parameters:
  //First parameter is the speed of the robot.
  //Second parameter is the state of the robot. 0 means it is attacking, 1 means it is defending.
  //Third parameter is the direction of the game. 0 means the direction is yellow, 1 means the direction is blue.
}
