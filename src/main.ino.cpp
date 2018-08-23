# 1 "c:\\users\\22451\\appdata\\local\\temp\\tmpnoapr7"
#include <Arduino.h>
# 1 "C:/Users/22451/Documents/GitHub/YOTAM-2018/src/main.ino"




#include <Arduino.h>

#include <Camera.h>

#include <Define.h>

#include <MotorController.h>

#include <Motors.h>
# 23 "C:/Users/22451/Documents/GitHub/YOTAM-2018/src/main.ino"
Camera camera;

MotorController Motor;





int bAngle = 0;
void setup();
void loop();
#line 35 "C:/Users/22451/Documents/GitHub/YOTAM-2018/src/main.ino"
void setup() {

  Serial.begin(9600);

  camera.setup();







}



void loop() {







  Motor.Move(bAngle, 0, 100);

  camera.update();







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
