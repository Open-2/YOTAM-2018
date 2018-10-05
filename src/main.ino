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
// PID pid = PID(0.5, 1, 0.2, 255);

// //"""Variable Naming"""
// const int MoveSpd = 255;
// const int GoalAcc = 7;

// unsigned long previousMillis = 0;
// const long interval = 200;
// bool voiding = false;
// int oldLight = 0;

// unsigned long compMillis = 0;
// int previousHeading = 0;
// const double kp = 4.5;
// const double kd = 9; //-8;

// double corr;
int ballAngles;
int x;
int y;

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
  camera.mvspeed = 255;
  camera.update();
  compass.updateGyro();
  // corr = pid.update(compass.heading, 0);
  // //"""Angle/Correction Calculation"""
  // corr = pid.update(compass.heading, 0);
  camera.angleCalc();
  // Serial.print(camera.ballAngle);
  // camera.Test();
  // Serial.println(camera.ballAngle);
  // Motor.Move(camera.ballAngle, 0, 255);
  // Motor.Move(0, -camera.bgoalCorrect, 0);
  // compass.compassCalc();
  // Serial.println(compass.heading);
  // Serial.println(compass.heading);
    Motor.Move(camera.bAngle, -compass.correction, camera.mvspeed);
  // Serial.print("Ball = ");
  // Serial.print(camera.ballAngle);
  // Serial.print(", Yellow Goal = ");
  // Serial.println(camera.yGoalAngle);
  // Serial.print(camera.ballExists);
  // Serial.print(", ");
  // Serial.println(Serial3.read());
  // Motor.Move(camera.bAngle, 0, 255);

  // Motor.Move(0, 0, 255);
  // //"""Motor Movement Code"""
  // Motor.Move(90, camera.yGoalAngle, 150);
  // Motor.Move(90, 0 , 255);
  // Motor.Move(90, 0, 255);
  // Motor.Move(0, 0, 255);
  // Motor.Move(0, -corr, 0);
  // Motor.Move(180, 0, 255);
  // role.action(255, camera.bAngle, -1, 10, 0 , 1, camera.ballAngle, compass.correction);
  // Motor.Move(90, 0, 255);
  // Motor.Move(camera.bAngle, -compass.correction, 255);
  //Parameters:
  //First parameter is the speed of the robot.
  //Second parameter is the state of the robot. -1 means it is defending, any other number is the movement direction when attacking.
  //Third parameter is the fake angle. If it is set to -1, it is off. Otherwise, it is the fake angle of the ball.
  //Fourth parameter is the distance to the ball.
  //Fifth parameter is the direction of the game. 0 means the direction is yellow, 1 means the direction is blue.
  //Sixth parameter is the compass correction toggle. 0 means off, 1 means on.
  //Seventh parameter is the direction of the ball.
  //Eighth parameter is the correction value.
} 
