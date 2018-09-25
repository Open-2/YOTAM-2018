#include <Camera.h>
#include <math.h>

int currentin = 0;

void Camera::setup(){
  Serial3.begin(9600);
}

void Camera::update(){
  if(Serial3.available() >= CAM_BUFFER_NUM) {
    if(Serial3.read() == 255){
        for (int i = 1; i < CAM_BUFFER_NUM; i++){
          currentin = Serial3.read();
          if(currentin != -1 && currentin != 0 && currentin != 255){
            camBuffer[i] = currentin;

                
              }
           }
        }
    }
  ballx = camBuffer[1];
  bally = camBuffer[2];

  yellowGoalx = camBuffer[3];
  yellowGoaly = camBuffer[4];

  blueGoalx = camBuffer[5];
  blueGoaly = camBuffer[6];

  ballAngle = (450 - degrees(atan2(ballx - 120, bally -120)))- 90;
  //Fix this fucking shit smh
  ballAngle = (ballAngle%360);
  yGoalAngle = (450 - degrees(atan2(yellowGoalx - 120, yellowGoaly -120)))- 90;
  yGoalAngle = (yGoalAngle%360);
  bGoalAngle = (450 - degrees(atan2(blueGoalx - 120, blueGoaly -120)))- 90;
  bGoalAngle = (bGoalAngle%360);
  Serial.print(ballx);
  Serial.print(", ");
  Serial.print(bally);
  Serial.print(", ");
  Serial.println(ballAngle);
  }
  void Camera::angleCalc(){
      if (ballAngle > 340 || ballAngle < 20) {
      bAngle = 0;
    } else {
      if (ballAngle > 180) {
        bAngle = ballAngle /*- 2 * (ballAngle - 180)*/ - 90;
      } else {
          bAngle = ballAngle /*- 2 * (ballAngle - 180)*/ + 90;
        }
    }
    camDistance = sqrt(((ballx-120)^2)+((bally-120)^2));
    ballDistance = ((-59.1132*pow(45.5842, (-0.00842102*camDistance)))+102.468);
    bGoalDistance = sqrt(((ballx - 120) ^ 2) + ((bally - 120) ^ 2));
    yGoalDistance = sqrt(((ballx - 120) ^ 2) + ((bally - 120) ^ 2));
  }

