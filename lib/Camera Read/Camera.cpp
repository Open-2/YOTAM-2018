#include <Camera.h>

int currentin = 0;

void Camera::setup(){
  Serial3.begin(9600);
}

void Camera::update(){
  if(Serial3.available() >= CAM_BUFFER_NUM) {
    if(Serial3.read() == 255){
      while(Serial3.read() != 255) {
        for (int i = 0; i < CAM_BUFFER_NUM; i++){
          currentin = Serial3.read();
          if(currentin != -1 && currentin != 0 && currentin != 255){
            camBuffer[i] = currentin;

                }
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
  ballAngle = (yGoalAngle%360);
  yGoalAngle = (450 - degrees(atan2(ballx - 120, bally -120)))- 90;
  yGoalAngle = (yGoalAngle%360);
  bGoalAngle = (450 - degrees(atan2(ballx - 120, bally -120)))- 90;
  yGoalAngle = (yGoalAngle%360);
  // Serial.print(ballAngle);
  // Serial.println(")");

}
