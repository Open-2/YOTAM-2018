#include <Camera.h>

int currentin = 0;

void Camera::setup(){
  Serial3.begin(9600);
}

void Camera::update(){
  if(Serial3.available() >= 7) {
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

  yellowGoalx = camBuffer[3] - 120;
  yellowGoaly = camBuffer[4] - 120;

  blueGoalx = camBuffer[5] - 120;
  blueGoaly = camBuffer[6] -120;

  Serial.print("Ball (");
  Serial.print(ballx);
  Serial.print(", ");
  Serial.print(bally);
  Serial.print(", ");/*" Blue Goal (")*/
  // Serial.print(blueGoalx);
  // Serial.print(", ");
  // Serial.print(blueGoaly);
  // Serial.print(") Yellow Goal (");
  // Serial.print(yellowGoalx);
  // Serial.print(", ");
  // Serial.print(yellowGoaly);
  // Serial.println(")");

  ballAngle = (450 - degrees(atan2(ballx - 120, bally -120)))- 90;
  ballAngle = (ballAngle%360);
  Serial.print(ballAngle);
  Serial.println(")");

}
