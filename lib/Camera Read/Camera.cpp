#include <Camera.h>
#include <math.h>

int currentin = 0;

void Camera::setup(){
  Serial3.begin(9600);
}

void Camera::update(){
  if(Serial3.available() >= CAM_BUFFER_NUM) {
    if(Serial3.read() == 255){
      for (int i = 1; i <= CAM_BUFFER_NUM; i++){
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

  ballAngle = (450 - degrees(atan2(ballx - 92, bally - 92)))- 90;
  ballAngle = (ballAngle%360);
  //Meme
  // ballAngle = 45;
  //Meme
  yGoalAngle = (450 - degrees(atan2(yellowGoalx - 92, yellowGoaly - 92)))- 90;
  yGoalAngle = (yGoalAngle%360);
  bGoalAngle = (450 - degrees(atan2(blueGoalx - 92, blueGoaly - 92)))- 90;
  bGoalAngle = (bGoalAngle%360);
}

void Camera::Test(){
   Serial.print("Ball x: ");
   Serial.print(ballx);
   Serial.print(", ball y: ");
   Serial.print(bally);
   Serial.print(", yellow goal x: ");
   Serial.print(yellowGoalx);
   Serial.print(", yellow goal y: ");
   Serial.print(yellowGoaly);
   Serial.print(", blue goal x: ");
   Serial.print(blueGoalx);
   Serial.print(", blue goal y: ");
   Serial.print(blueGoaly);
   Serial.print(", ball angle: ");
   Serial.print(ballAngle);
   Serial.print(", ball distance: ");
   Serial.println(ballDistance);
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
 ballcamDistance = sqrt(((ballx-120)^2)+((bally-120)^2));
 ballDistance = ((-59.1132*pow(45.5842, (-0.00842102*camDistance)))+102.468);
 bGoalcamDistance = sqrt(((blueGoalx - 120) ^ 2) + ((blueGoaly - 120) ^ 2));
 yGoalcamDistance = sqrt((pow((yellowGoalx - 120),  2)) + (pow((yellowGoaly - 120), 2)));

 bgoalCorrect = (-0.00339513*pow(bGoalAngle, 2) + 1.22225*bGoalAngle - 2.50014) + 50;
 
 ygoalCorrect = (-0.00439513*pow(yGoalAngle, 2) + 1.22225*yGoalAngle - 2.50014) + 50;

//  if (yGoalAngle <= 7.5 || yGoalAngle >= 352.5)
//  {
//    ygoalCorrect = 0;
//  }
//  else if (yGoalAngle <= 180)
//  {
//    ygoalCorrect = 0.5 * ((yGoalAngle - 2 * (yGoalAngle - 180)));
//  }
//  else
//  {
//    ygoalCorrect = (yGoalAngle * -1) * 0.5;
//  }
}

