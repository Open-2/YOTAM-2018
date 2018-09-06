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
const double kp = 0.45;
const double kd = 0.9;
unsigned long previousMillis = 0;
unsigned long compMillis = 0;
unsigned long currentMillis = 0;
int previousHeading = 0;

void setup() {
  Serial.begin(9600);
  camera.setup();
  Motor.Setup();
  // compass.compassSetup();
  // compass.calibrate();
  //Wire.begin();
}

void loop() {
  //Constant Data Refreshing and Movement
  debug.cameraTest();

  debug.motorTest();

  // compass.updateGyro();

  // Serial.println("Whomst is it that has performed this action");

  // """Compass Correction Code"""
  // unsigned long currentMillis = millis();
  //
  // int relativeHeading = compass.heading > 180 ? (360 - compass.heading) : compass.heading;
  //
  // double diffTime = ((double)(currentMillis - compMillis))/100.0;
  // double difference = ((double)(relativeHeading - previousHeading)) / diffTime;
  // compMillis = currentMillis;
  // //Serial.print((previousHeading-relativeHeading));
  // //Serial.print("\t");
  // //Serial.println(difference);
  // previousHeading = relativeHeading;
  //
  // int correction = round(kp*((double)relativeHeading) + kd*difference);

  // """Goal Correction Code"""

  // Motor Movement Code
  camera.angleCalc();
  if (debug.motoron == true){
    Motor.Move(camera.bAngle, 0, 255);

      }
}
