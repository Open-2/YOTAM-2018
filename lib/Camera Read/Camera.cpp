#include <Camera.h>
#include <math.h>

int currentin = 0;

void Camera::setup(){

  //Open the serial 3 port for baud rate 9600.
  Serial3.begin(9600);
}

void Camera::update(){

  //Check if the amount of bytes available in serial is more than 2 times the maximum data length +1.
  if(Serial3.available() >= 4 * CAM_BUFFER_NUM) {

    //If the value "255" is received from serial, proceed.
    if(Serial3.read() == 255){

      //While the only the values of the first camera output buffer exists, assign recieved values to a buffer.
      for (int i = 1; i <= CAM_BUFFER_NUM; i++){
        currentin = Serial3.read();

        //Only assign the incoming value to its assigned variable if it is not -1. If the recieved value is -1, leave the old value of the data and continue.
        if(currentin != -1) camBuffer[i] = currentin;                
      }
    }
  }

  //Assign the ball values and check if the ball exists.
  ballx = camBuffer[1];
  // ballx = 115;
  bally = camBuffer[2];
  // bally = 115;
  if(ballx == 0 && bally == 0){
    ballExists = false;
  }
  else{
    ballExists = true;
  }

  //Assign the blue goal values and check if the yellow goal exists.
  yellowGoalx = camBuffer[3];
  yellowGoaly = camBuffer[4];
  if (yellowGoalx == 0 && yellowGoaly == 0)
  {
    yellowExists = false;
  }
  else
  {
    yellowExists = true;
  }
  yellowGoalx = 0;
  yellowGoaly = 0;


  //Assign the blue goal values and check if the blue goal exists.
  blueGoalx = camBuffer[5];
  blueGoaly = camBuffer[6];
  if (blueGoalx == 0 && blueGoaly == 0)
  {
    blueExists = false;
  }
  else
  {
    blueExists = true;
  }

  //Calculate the 2 significant angles of the ball.
  ballAngle = (450 - degrees(atan2(ballx - 120, bally - 120)))- 90;
  ballAngle = (ballAngle%360);

  //Calculate the 2 significant angles of the yellow goal.
  yGoalAngle = (450 - degrees(atan2(yellowGoalx - 100, yellowGoaly - 100))) - 90;
  yGoalAngle = (yGoalAngle%360);

  //Calculate the 2 significant angles of the blue goal.
  // yGoalAngle = yGoalAngle - 2 * (yGoalAngle - 180);
  bGoalAngle = (450 - degrees(atan2(blueGoalx - 100, blueGoaly - 100)))- 90;
  bGoalAngle = (bGoalAngle%360);
}

void Camera::Test(){

  //Honestly fuck this debug function and fuck the old debug library, I hated working on this shit so much. (It outputs all the values displayed by the camera.)
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

      //Calculate the distances of the ball, blue goal and yellow goal from the center of the camera.
      ballcamDistance = sqrt(pow((ballx - 120), 2) + (pow((bally - 120), 2)));
      bGoalcamDistance = sqrt(pow((blueGoalx - 120), 2) + (pow((blueGoaly - 120), 2)));
      yGoalcamDistance = sqrt((pow((yellowGoalx - 120), 2)) + (pow((yellowGoaly - 120), 2)));

      //Calculate the goal correction in terms of the yellow goal.
      if (yGoalAngle <= 10 || yGoalAngle >= 350)
      {
        ygoalCorrect = 0;
      }
      else if (yGoalAngle <= 180)
      {
        ygoalCorrect = 2 * (yGoalAngle - 2 * (yGoalAngle - 180));
      }
      else
      {
        ygoalCorrect = (yGoalAngle * -1) * 2;
      }

      //Calculate the goal correction in terms of the blue goal.
      if (bGoalAngle <= 10 || bGoalAngle >= 350)
      {
        bgoalCorrect = 0;
      }
      else if (bGoalAngle <= 180)
      {
        bgoalCorrect = 0.3 * ((bGoalAngle - 2 * (bGoalAngle - 180)));
      }
      else
      {
        bgoalCorrect = (bGoalAngle * -1) * 0.3;
      }

      //Calculate the correction in terms of the ball.
      if (ballAngle <= 10 || ballAngle >= 350)
      {
        ballCorrect = 0;
      }
      else if (ballAngle >= 180)
      {
        ballCorrect = 1.5 * ((ballAngle - 2 * (ballAngle - 180)));
      }
      else
      {
        ballCorrect = (ballAngle * -1) * 1.5;
      }
}

void Camera::corCalc(int val1, int val2) {
  int realCor = (val1 + val2)/2;
}
