// //"""Includes"""

#include <Arduino.h>
#include <Camera.h>
#include <Compass.h>
#include <Wire.h>
#include <Define.h>
#include <MotorController.h>
#include <Motors.h>
#include <Debug.h>
#include <Role.h>
#include <PID.h>

// // """Library Name Allocation"""

Role role;
Camera camera;
MotorController Motor;
Debug debug;
Compass compass;
PID pid = PID(0.5,0,0.1,255);

// //"""Variable Naming"""
const int GoalAcc = 7;
const int MoveSpd = 255;

unsigned long previousMillis = 0;
const long interval = 200;
bool voiding = false;
int oldLight = 0;

unsigned long compMillis = 0;
int previousHeading = 0;
const double kp = 4.5;
const double kd = 9; //-8;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  camera.setup();
  Motor.Setup();
  compass.compassSetup();
  compass.calibrate();
}
void loop() {
  // //"""Data Refreshing"""
  camera.update();
  compass.updateGyro();
  // //"""Angle/Correction Calculation"""
  pid.update(compass.heading, 0);
  camera.angleCalc();
  // camera.Test();
  // Serial.println(camera.ballAngle);
  // compass.compassCalc();
  // Serial.println(compass.heading);
  // Serial.println(compass.heading);
  // int relativeHeading = compass.heading > 180 ? (360 - compass.heading) : -compass.heading;
  // Motor.Move(0, -compass.correction, 0);
  // double diffTime = ((double)(currentMillis - compMillis)) / 100.0;
  // double difference = ((double)(relativeHeading - previousHeading)) / diffTime;
  // compMillis = currentMillis;
  // previousHeading = relativeHeading;

  // int correction = round(kp * ((double)relativeHeading) + kd * difference);

  // Serial.println(compass.heading);
  Motor.Move(0, pid.correction, 0);
  // Motor.Move(0, 0, 255);
  // //"""Motor Movement Code"""
  // Motor.Move(90, camera.yGoalAngle, 150);
  // Motor.Move(90, 0 , 255);
  // role.action(255, 0, -1, 10, 0, 0);
  //Parameters:
  //First parameter is the speed of the robot.
  //Second parameter is the state of the robot. 0 means it is attacking, 1 means it is defending.
  //Third parameter is the fake angle. If it is set to -1, it is off. Otherwise, it is the fake angle of the ball.
  //Fourth parameter is the distance to the ball.
  //Fifth parameter is the direction of the game. 0 means the direction is yellow, 1 means the direction is blue.
  //Sixth parameter is the compass correction toggle. 0 means off, 1 means on.
} 
