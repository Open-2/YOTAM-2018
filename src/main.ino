//All the includes go here:

#include <Arduino.h>
#include <Camera.h>
#include <Compass.h>
#include <Define.h>
#include <MotorController.h>
#include <Motors.h>
#include <Debug.h>


// """All the library naming goes here:"""

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
  compass.compassSetup();
  compass.calibrate();
  Wire.begin();
}
void loop() {
  //Constant Data Refreshing and Movement
  debug.cameraTest();
  debug.motorTest();

  // compass.updateGyro();

  // """Compass Correction Code"""
  //compass.compassCalc();

  // """Goal Correction Code"""

  // Motor Movement Code
  camera.angleCalc();
  if (debug.motoron == true){
    Motor.Move(camera.bAngle, compass.correction, 255);

      }
}
