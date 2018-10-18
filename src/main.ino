/*###SETUP! DO NOT TOUCH!*/

#include <Arduino.h>
#include <Camera.h>
#include <Compass.h>
#include <Wire.h>
#include <Define.h>
#include <MotorController.h>
#include <Motors.h>
#include <PID.h>

Camera camera;
MotorController Motor;
Compass compass;

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

/*SETUP! DO NOT TOUCH!*/

void loop() {

/*DEBUG TOGGLES*/

debugState = 0;

//State 0 is motor debug.
//State 1 is camera debug.
//State 2 is IMU debug.


/*DEBUG TOGGLES*/

/*DEBUG CODE! DO NOT TOUCH!*/

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
    Serial.println(camera.ballAngle);
    break;  
  case 2:
    Serial.print(compass.heading);
    Serial.print(", ");
    Serial.println(compass.correction);
    break;
}

/*DEBUG CODE! DO NOT TOUCH!*/

/*MAIN CODE! DO NOT TOUCH!*/

 camera.update();
 compass.updateGyro();
 camera.angleCalc();
  if (camera.ballExists == false) {
    if (millis() < 5000) {
      Motor.Move(0, -compass.correction, 255);
      } else {
        Motor.Move(180, -compass.correction, 125);
      }
    } else {
    Motor.Move(camera.bAngle, -compass.correction, camera.mvspeed);
  }
}

/*MAIN CODE! DO NOT TOUCH!*/