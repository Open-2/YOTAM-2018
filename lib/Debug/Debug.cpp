#include <Debug.h>
#include <Arduino.h>
#include <MotorController.h>
#include <Motors.h>

void Debug::cameraTest(){
  //Here we test the camera output
  Serial.print("Ball (");
  Serial.print(camera.ballx);
  Serial.print(" x, ");
  Serial.print(camera.bally);
  Serial.print(" y, ");
  Serial.print(camera.ballAngle);
  Serial.print(" degree ball angle, ");
  Serial.print(camera.bAngle);
  Serial.print(" degree movement angle");
  Serial.print(") Blue Goal (");
  Serial.print(camera.blueGoalx);
  Serial.print(" x, ");
  Serial.print(camera.blueGoaly);
  Serial.print(" y, ");
  Serial.print(camera.bGoalAngle);
  Serial.print(" degrees");
  Serial.print(") Yellow Goal (");
  Serial.print(camera.yellowGoalx);
  Serial.print(" x, ");
  Serial.print(camera.yellowGoaly);
  Serial.print(" y, ");
  Serial.print(camera.bGoalAngle);
  Serial.println(" degrees)");
}

void Debug::motorTest(){
  //Here we make all the motors spin right to see what is moving in the correct direction
  motoron = false;
  timePassed = millis() - timeStart;
  timeState = (millis()%8000);
  timeState = timeState/1000;
  motorTestState(timeState);
}


void Debug::motorTestState(int state) {
  switch (state) {
    case 1:
      Motor.motorFrontLeft.Move(-255);
    case 2:
      Motor.motorBackLeft.Move(-255);
    case 3:
      Motor.motorBackRight.Move(-255);
    case 4:
      Motor.motorFrontRight.Move(-255);
    case 5:
      Motor.motorFrontLeft.Move(255);
    case 6:
      Motor.motorBackLeft.Move(255);
    case 7:
      Motor.motorBackRight.Move(255);
    case 8:
      Motor.motorFrontRight.Move(255);
  }
}

void Debug::compassTest(){
  Serial.print("(");
  Serial.print(compass.heading);
  Serial.print(" degree heading, ");
  Serial.print(compass.relativeHeading);
  Serial.print(" degree relative heading, ");
  Serial.print(compass.correction);
  Serial.print(" correction)");
}
