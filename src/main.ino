/*###SETUP*/

#include "Arduino.h"
#include <Camera.h>
#include <Compass.h>
#include <Wire.h>
#include <Define.h>
#include <MotorController.h>
#include <Motors.h>
#include <PID.h>
#include <Role.h>

Camera camera;
MotorController Motor;
Compass compass;
Role role;

int debugState;
int debugTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  camera.setup();
  Motor.Setup();
  compass.compassSetup();
  compass.calibrate();
}

/*SETUP*/

void loop() {

/*DEBUG TOGGLES*/

debugState = 0;

//State 0 is all motor debug.
//State 1 is individual motor debug.
//State 2 is camera debug.
//State 3 is IMU debug.
//State 4 is light sensor debug.
//State 5 is light gate debug.
//State 6 is LIDAR debug.

/*DEBUG TOGGLES*/

/*DEBUG CODE*/

debugTime = millis();

switch(debugState) {
  case 0:
    debugTime = (debugTime - debugTime%2000)/2000;
    if (debugTime == 1) {
      Motor.Move(0, 0, 255);
    }
    if (debugTime == 2) {
      Motor.Move(90, 0, 255);
    }
    if (debugTime == 3) {
      Motor.Move(180, 0, 255);
    }
    if (debugTime == 4) {
      Motor.Move(270, 0, 255);
    }
    break;
  case 1:
    debugTime = (debugTime - debugTime % 2000) / 2000;
    if (debugTime == 1) {
      Motor.motorFrontLeft.Move(255);
    }
    if (debugTime == 2) {
      Motor.motorBackLeft.Move(255);
    }
    if (debugTime == 3) {
      Motor.motorBackRight.Move(255);
    }
    if (debugTime == 4) {
      Motor.motorFrontRight.Move(255);
    }
    break;
  case 2:
    Serial.print("Ball: ");
    Serial.print(camera.ballAngle);
    Serial.print(", ");
    Serial.print("Yellow Goal: ");
    Serial.print(camera.yGoalAngle);
    Serial.print(", ");
    Serial.print("Blue Goal: ");
    Serial.println(camera.bGoalAngle);
    break;  
  case 3:
    Serial.print(compass.heading);
    Serial.print(", ");
    Serial.println(compass.correction);
    break;
  case 4:
    //light sensor debug.
    break;
  case 5:
    //light gate debug.
    break;
  case 6:
    //LIDAR debug.
    break;
}

/*DEBUG CODE*/

/*MAIN CODE*/

 camera.update();
 compass.updateGyro();
 camera.angleCalc();
 role.attack(compass.correction, camera.ballAngle, camera.ballcamDistance);

/*MAIN CODE*/