//All the includes go here

#include <Arduino.h>

//All the library namin goes here

//Camera camera;
//MotorController Motor;

//All the variable naming goes

void setup() {
  Serial.begin(9600);
  //Motor.Setup();
  //Wire.begin();
  //camera.init();
}

void loop() {
  //camera.update();
  Serial.print(Serial3.read());
  //Motor.move(0, 0, 150);

}
