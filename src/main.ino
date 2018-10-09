//"""Includes"""

#include <Arduino.h>
#include <Camera.h>
#include <Compass.h>
#include <Wire.h>
#include <Define.h>
#include <MotorController.h>
#include <Motors.h>
#include <PID.h>
// #include <Defender.h>

// """Library Name Allocation"""

Camera camera;
MotorController Motor;
Compass compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  camera.setup();
  Motor.Setup();
  compass.compassSetup();
  compass.calibrate();
  // pinMode(13, OUTPUT);
}
void loop() {
  // //"""Data Refreshing"""
  camera.update();
  compass.updateGyro();
  camera.angleCalc();
  Serial.println(camera.ballAngle);
  if (camera.ballExists == false) {
    if (millis() < 5000) {
      Motor.Move(0, -compass.correction, 255);
      } else {
        Motor.Move(180, -compass.correction, 125);
      }
    } else {
    Motor.Move(camera.bAngle, -compass.correction, camera.mvspeed);
  }
}
  // Serial.println(camera.bAngle);
  // if (camera.yellowExists == true) {
  // if (camera.yGoalcamDistance > 80) {
  //   Motor.Move(camera.yGoalAngle, -compass.correction, 255);
  //   }
  // }
  // Serial.print(camera.yGoalcamDistance);
  // Serial.print(", ");
  // Serial.println(camera.ballcamDistance);
  // if (camera.yellowExists == true)
  // {
  //   if (camera.ballExists == true)
  //   {
  //     if (camera.yGoalDistance >= 90)
  //     {
  //       Motor.Move(camera.yGoalAngle, -compass.correction, 255);
  //     }
  //     else if (camera.ballcamDistance < 70)
  //     {
  //       Motor.Move(camera.bAngle, -compass.correction, 255);
  //     }
  //     else if (camera.yGoalAngle < 160)
  //     {
  //       goaliemv = (-0.0104938 * pow(camera.ballAngle, 2) + 3.77778 * camera.ballAngle + (-1.1369 * pow(10, -14)));
  //       Motor.Move(90, -compass.correction, goaliemv);
  //     }
  //     else if (camera.yGoalAngle > 200)
  //     {
  //       goaliemv = (-0.0104938 * pow(camera.ballAngle, 2) + 3.77778 * camera.ballAngle + (-1.1369 * pow(10, -14)));
  //       Motor.Move(270, -compass.correction, goaliemv);
  //     }
  //     else
  //     {
  //       Motor.Move(camera.bAngle, -compass.correction, 255);
  //     }
  //   }
  //   else
  //   {
  //     if (camera.yGoalDistance >= 100)
  //     {
  //       Motor.Move(camera.yGoalAngle, -compass.correction, 255);
  //     }
  //     else if (camera.yGoalAngle < 120)
  //     {
  //       goaliemv = (-0.0104938 * pow(camera.yGoalAngle, 2) + 3.77778 * camera.yGoalAngle + (-1.1369 * pow(10, -14)));
  //       Motor.Move(90, -compass.correction, goaliemv);
  //     }
  //     else if (camera.yGoalAngle > 240)
  //     {
  //       goaliemv = (-0.0104938 * pow(camera.yGoalAngle, 2) + 3.77778 * camera.yGoalAngle + (-1.1369 * pow(10, -14)));
  //       Motor.Move(270, -compass.correction, goaliemv);
  //     }
  //   }
  // }
  // else
  // {
  //   if (camera.ballExists == true)
  //   {
  //     Motor.Move(camera.bAngle, -compass.correction, 255);
  //   }
  //   else
  //   {
  //     Motor.Move(0, 0, 255);
  //   }
  // }
// Motor.Move(0, 0, 255);
// camera.defenceCalc(compass.heading);
// Motor.Move(0, -camera.ygoalCorrect, 0);
// Serial.print(camera.yGoalAngle);
// Serial.print(", ");
// Serial.println(camera.yGoalcamDistance);
// Motor.Move(0, 0, 90);
// Motor.motorFrontLeft.Move(90);
// Motor.Move(0, -camera.ygoalCorrect, 0);

// vertmove = 0;
// hormove = 0;
// counter = 0;
// if (camera.yellowExists) {
//   camera.mvspeed = 255;
//   if (camera.yGoalAngle > 200) {
//     hormove = 90;
//     counter += 1;
//   } else if (camera.yGoalAngle < 160) {
//     hormove = 270;
//     counter += 1;
//   }
//   // Serial.println(camera.yGoalcamDistance);
//   if (camera.yGoalcamDistance > 100) {
//     vertmove = 180;
//     counter += 1;
//   } else if (camera.yGoalcamDistance < 60) {
//     vertmove = 0;
//     counter += 1;
//   }
// } else {
//   camera.mvspeed = 0;
//   vertmove = 0;
//   hormove = 0;
//   counter = 0;
// }
// Motor.Move((hormove + vertmove)/counter, compass.correction, camera.mvspeed);
// Motor.Move(camera.ballAngle, -compass.correction, 255);
// Serial.print(camera.ballAngle);
// camera.Test();
// Serial.println(camera.ballAngle);
// Motor.Move(camera.ballAngle, 0, 255);
// Motor.Move(0, -camera.bgoalCorrect, 0);
// compass.compassCalc();
// Serial.println(compass.heading);
// Serial.println(compass.heading);
// if (camera.yellowGoalx == 0 && camera.yellowGoaly == 0) {
// Motor.Move(camera.bAngle, camera.ygoalCorrect, camera.mvspeed);
// Motor.Move(0, 0, 255);
// role.Defend(255, camera.ballAngle, 60, 1, -compass.correction);
// Motor.Move(270, camera.ygoalCorrect, 150);
// Serial.print(camera.ballAngle);
// Serial.print(", ");
// Serial.println(camera.ballcamDistance);
// Serial.print(", ");
// Serial.print(camera.yGoalAngle);
// Serial.print(", ");
// Serial.println(camera.yGoalcamDistance);
// Serial.println(camera.ballAngle);
// } else {
// Motor.Move(camera.bAngle, -camera.ygoalCorrect, camera.mvspeed);
// }
// Serial.print("Ball = ");
// Serial.print(camera.ballAngle);
// Serial.print(", Yellow Goal = ");
// Serial.println(camera.yGoalAngle);
// Serial.print(camera.ballExists);
// Serial.print(", ");
// Serial.println(Serial3.read());
// Motor.Move(camera.bAngle, 0, 255);

// Motor.Move(0, 0, 255);
// //"""Motor Movement Code"""
// Motor.Move(90, camera.yGoalAngle, 150);
// Motor.Move(90, 0 , 255);
// Motor.Move(90, 0, 255);
// Motor.Move(0, 0, 255);
// Motor.Move(0, -corr, 0);
// Motor.Move(180, 0, 255);
// role.action(255, camera.bAngle, -1, 10, 0 , 1, camera.ballAngle, compass.correction);
// Motor.Move(90, 0, 255);
// Motor.Move(camera.bAngle, -compass.correction, 255);
//Parameters:
//First parameter is the speed of the robot.
//Second parameter is the state of the robot. -1 means it is defending, any other number is the movement direction when attacking.
//Third parameter is the fake angle. If it is set to -1, it is off. Otherwise, it is the fake angle of the ball.
//Fourth parameter is the distance to the ball.
//Fifth parameter is the direction of the game. 0 means the direction is yellow, 1 means the direction is blue.
//Sixth parameter is the compass correction toggle. 0 means off, 1 means on.
//Seventh parameter is the direction of the ball.
//Eighth parameter is the correction value.
