//All the includes go here:

#include <Arduino.h>
#include <Camera.h>
#include <Define.h>
#include <MotorController.h>
#include <Motors.h>
#include <Debug.h>


//All the library naming goes here:

Camera camera;
MotorController Motor;
Debug debug;

//All the variable naming goes here:
int bAngle = 0;

void setup() {
  Serial.begin(9600);
  camera.setup();
  Motor.Setup();
  //Wire.begin();
}

void loop() {
  //Constant Data Refreshing and Movement
  // debug.motorTest();
  camera.update();
  //Movement If Statements:
if (debug.motoron == true){
  speed = 100;
  if (camera.ballAngle > 340 || camera.ballAngle < 20) {
    bAngle = 0;
  } else {
    if (camera.ballAngle > 180) {
      bAngle = camera.ballAngle - 2 * (camera.ballAngle - 180) - 90;
    } else {
        bAngle = camera.ballAngle - 2 * (camera.ballAngle - 180) + 90;
        }
      }

    }

}
