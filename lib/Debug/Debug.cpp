#include <Debug.h>
#include <Arduino.h>
#include <MotorController.h>
#include <Motors.h>




void Debug::cameraTest(){
  //Here we test the camera output
  Serial.print("Ball (");
  Serial.print(camera.ballx);
  Serial.print(", ");
  Serial.print(camera.bally);
  Serial.print(", ");
  Serial.print(camera.ballAngle);
  Serial.print(" Blue Goal (");
  Serial.print(camera.blueGoalx);
  Serial.print(", ");
  Serial.print(camera.blueGoaly);
  Serial.print(", ");
  Serial.print(camera.bGoalAngle);
  Serial.print(") Yellow Goal (");
  Serial.print(camera.yellowGoalx);
  Serial.print(", ");
  Serial.print(camera.yellowGoaly);
  Serial.print(", ");
  Serial.print(camera.bGoalAngle);
  Serial.println(")");
}

void Debug::motorTest(){
  //Here we make all the motors spin right to see what is moving in the correct direction.
  Motor.Setup();
  motoron = false;
  timePassed = millis() - timeStart;
  if (timePassed < 2000) {
    Motor.Move(0, 0, 0);
    Motor.motorFrontLeft.Move(-255);
    Serial.println("Front left");
  } else {
    if (timePassed < 4000) {
      Motor.Move(0, 0, 0);
      Motor.motorBackLeft.Move(-255);
      Serial.println("Back left");
    } else {
      if (timePassed < 6000) {
        Motor.Move(0, 0, 0);
        Motor.motorBackRight.Move(-255);
        Serial.println("Back right");
      } else {
        if (timePassed < 8000) {
          Motor.Move(0, 0, 0);
          Motor.motorFrontRight.Move(-255);
          Serial.println("Front right");
        } else {
          timeStart = millis();

        }
      }
    }
  }
}

void Debug::compassTest(){
  //For now there is nothing here but when we get the compass working we will output this.
}
