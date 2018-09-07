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
  //Here we make all the motors spin right to see what is moving in the correct direction.
  Motor.Setup();
  motoron = false;
  timePassed = millis() - timeStart;
  if (timePassed < 1000) {
    Motor.Move(0, 0, 0);
    Motor.motorFrontLeft.Move(-255);
    // Serial.println("Front Left Motor Turning Right");
  } else {
    if (timePassed < 2000) {
      Motor.Move(0, 0, 0);
      Motor.motorBackLeft.Move(-255);
      // Serial.println("Back Left Motor Turning Right");
    } else {
      if (timePassed < 3000) {
        Motor.Move(0, 0, 0);
        Motor.motorBackRight.Move(-255);
        // Serial.println("Back Right Motor Turning Right");
      } else {
        if (timePassed < 4000) {
          Motor.Move(0, 0, 0);
          Motor.motorFrontRight.Move(-255);
          // Serial.println("Front Right Motor Turning Right");
        } else {
          if (timePassed < 5000) {
            Motor.Move(0, 0, 0);
            Motor.motorFrontLeft.Move(255);
            // Serial.println("Front Left Motor Turning Left");
          } else {
            if (timePassed < 6000) {
              Motor.Move(0, 0, 0);
              Motor.motorBackLeft.Move(255);
              // Serial.println("Back Left Motor Turning Left");
            } else {
              if (timePassed < 7000) {
                Motor.Move(0, 0, 0);
                Motor.motorBackRight.Move(255);
                // Serial.println("Back Right Motor Turning Left");
              } else {
                if (timePassed < 8000) {
                  Motor.Move(0, 0, 0);
                  Motor.motorFrontRight.Move(255);
                  // Serial.println("Front Right Motor Turning Left");
        } else {
          timeStart = millis();

                }
              }
            }
          }
        }
      }
    }
  }
}

void Debug::compassTest(){
  //For now there is nothing here but when we get the compass working we will output this.
}
