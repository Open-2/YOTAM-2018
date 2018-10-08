#include <Camera.h>
#include <math.h>

int currentin = 0;

void Camera::setup(){
  Serial3.begin(9600);
}

void Camera::update(){
  if(Serial3.available() >= 2 * CAM_BUFFER_NUM) {
    if(Serial3.read() == 255){
      for (int i = 1; i <= CAM_BUFFER_NUM; i++){
        currentin = Serial3.read();
        if(currentin != -1 && currentin != 255){
          camBuffer[i] = currentin;             
        }
      }
    }
  }
  
  ballx = camBuffer[1];
  bally = camBuffer[2];
  // ballx = 0;
  // bally = 0;
  if(ballx == 0 && bally == 0){
    ballExists = false;
  }
  else{
    ballExists = true;
  }
  // ballx = 0;
  // bally = 0;

  yellowGoalx = camBuffer[3];
  yellowGoaly = camBuffer[4];
  // if (yellowGoalx == 0 && yellowGoaly == 0)
  // {
    // yellowExists = false;
  // }
  // else
  // {
  //   yellowExists = true;
  // }
  // yellowGoalx = 0;
  // yellowGoaly = 0;

  blueGoalx = camBuffer[5];
  blueGoaly = camBuffer[6];
  // if (blueGoalx == 0 && blueGoaly == 0)
  // {
  //   blueExists = false;
  // }
  // else
  // {
  //   blueExists = true;
  // }
  // blueGoalx = 0;
  // blueGoaly = 0;

  ballAngle = (450 - degrees(atan2(ballx - 120, bally - 120)))- 90;
  ballAngle = (ballAngle%360);
      //Meme
      // ballAngle = 45;
      //Meme
  yGoalAngle = (450 - degrees(atan2(yellowGoalx - 100, yellowGoaly - 100))) - 90;
  yGoalAngle = (yGoalAngle%360);
  yGoalAngle = yGoalAngle - 2 * (yGoalAngle - 180);
  bGoalAngle = (450 - degrees(atan2(blueGoalx - 100, blueGoaly - 100)))- 90;
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
//  if (ballAngle > 280 || ballAngle < 80) {
//    if (ballAngle > 180)
//    {
//      bAngle = ballAngle /*- 2 * (ballAngle - 180)*/ - 10;
//    }
//    else
//    {
//      bAngle = ballAngle /*- 2 * (ballAngle - 180)*/ + 10;
//    }
//  } else {
//    if (ballAngle > 180) {
//      bAngle = ballAngle /*- 2 * (ballAngle - 180)*/ - 40;
//    } else {
//      bAngle = ballAngle /*- 2 * (ballAngle - 180)*/ + 40;
//    }
  if(ballAngle > 180) ballAngle -= 360;
  if (ballAngle > 100 && ballAngle < -100) {
    if (ballAngle > 0) {
      bAngle = 220;
    } else {
      bAngle = 140;
    }
  } else {
  bAngle = ballAngle * 1.4;
  } 
  if (abs(ballAngle) < 50) {
    if (abs(ballAngle) < 15) {
      mvspeed = 255;
      bAngle = 0; 
    } else {
      if (ballAngle < 0) {
      bAngle = ballAngle + 15;
    } else {
      bAngle = ballAngle - 15;
    }
    }
  }
  if (ballAngle > 100 || ballAngle < -100)
  {
    if (ballAngle > 0)
    {
      bAngle = 220;
    }
    else
    {
      bAngle = 140;
    }
  }
  if (ballcamDistance > 90) {
    bAngle = ballAngle;
  }
 
      ballcamDistance = sqrt(pow((ballx - 120), 2) + (pow((bally - 120), 2)));
      // ballDistance = ((-59.1132 * pow(45.5842, (-0.00842102 * camDistance))) + 102.468);
      bGoalcamDistance = sqrt(pow((blueGoalx - 120), 2) + (pow((blueGoaly - 120), 2)));
      yGoalcamDistance = sqrt((pow((yellowGoalx - 120), 2)) + (pow((yellowGoaly - 120), 2)));

      //  bgoalCorrect = (-0.00339513*pow(bGoalAngle, 2) + 1.22225*bGoalAngle - 2.50014) + 50;

      //  ygoalCorrect = (-0.00439513*pow(yGoalAngle, 2) + 1.22225*yGoalAngle - 2.50014);

      //   if (yGoalAngle <= 10 || yGoalAngle >= 350)
      //   {
      //     ygoalCorrect = 0;
      //  }
      //  else if (yGoalAngle <= 180)
      //  {
      //    ygoalCorrect = 2 * ((yGoalAngle - 2 * (yGoalAngle - 180)));
      //  }
      //  else
      //  {
      //    ygoalCorrect = (yGoalAngle * -1) * 2;
      //  }

      //   if (bGoalAngle <= 10 || bGoalAngle >= 350) {
      //     bgoalCorrect = 0;
      //   } else if (bGoalAngle <= 180) {
      //     bgoalCorrect = 0.3 * ((bGoalAngle - 2 * (bGoalAngle - 180)));
      //   } else {
      //     bgoalCorrect = (bGoalAngle * -1) * 0.3;
      //   }

      //   if (ballx == 0 && bally == 0) {
      //     //Some circular movement here
      //     // Serial.println("Stage 3");
      //     losscounter += 1;
      //     if (losscounter >= 30) {
      //       bAngle = 180;
      //       mvspeed = 255;
      //     }
      //     milliangle = millis() / 2000;
      //     mvspeed = 130;
      //     if (milliangle % 2 == 0) {
      //       bAngle = 180;
      //     } else if (milliangle % 2 == 1) {
      //       bAngle = 0;
      //       }
      //   } else {
      //     losscounter = 0;
      //   }
}

// void Camera::defenceCalc(double heading){
//   if(yellowExists) {
//     if (ballExists) {
//       if (ballAngle < 90 || ballAngle > 270) {
//         if (ballcamDistance < 70 && yGoalcamDistance < 100) {
//           //orbit calc
//         } else {
//           if ((ballAngle < 20 || ballAngle < 340) && ballcamDistance < 70 && yGoalcamDistance < 100) {
//            forwardmove = (yGoalcamDistance - 70) * 5;
//            sidemove = (yGoalAngle - 90) * 5;

//            bAngle = doubleMod((degrees(atan2(sidemove, forwardmove))), 360);
//            mvspeed = sqrt(sidemove * sidemove + forwardmove * forwardmove); 
//           }
//         }
//       } else {
//         mvspeed = 255;
//       }
//     } else {
//       mvspeed = 0;
//     }
//   } else {
//     //orbit calc
//   }
// }