//All the includes go here:

#include <Arduino.h>
#include <Camera.h>
#include <Define.h>


//All the library naming goes here:

Camera camera;
//MotorController Motor;

//All the variable naming goes here:
int bAngle = 0;

void setup() {
  Serial.begin(9600);
  camera.setup();
  //Motor.Setup();
  //Wire.begin();
  //camera.init();
}

void loop() {

  //Constant Data Refreshing and Movement:

  camera.update();
  //Motor.move(0, 0, 75);

  //Movement If Statements:

  // if (camera.ballAngle > 340 || camera.ballAngle < 20) {
  //   bAngle = 0
  // } else {
  //   if (camera.ballAngle > 180) {
  //     bAngle = camera.ballAngle - 90;
  //   } else {
  //       bAngle = camera.ballAngle + 90;
  //       }
  //     }

}
