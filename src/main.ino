/*|||SETUP|||*/

#include <Arduino.h>
#include <Camera.h>
#include <Compass.h>
#include <Wire.h>
#include <Define.h>
#include <MotorController.h>
#include <Motors.h>
#include <PID.h>
#include <Role.h>
#include <Point.h>
// #include <Screen.h>

Camera camera;
MotorController Motor;
Compass compass;
Role role;
Point point;
// Screen screen;

int debugState;
int debugTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  camera.setup();
  Motor.Setup();
  // screen.init();

  // compass.compassSetup();
  // compass.calibrate();
}

/*|||SETUP|||*/

void loop() {

/*|||DEBUG TOGGLES|||*/

debugState = 0;

//State 0 is all motor debug.
//State 1 is individual motor debug.
//State 2 is camera debug.
//State 3 is IMU debug.
//State 4 is light sensor debug.
//State 5 is light gate debug.
//State 6 is LIDAR debug.

/*|||DEBUG TOGGLES|||*/

/*|||DEBUG CODE|||*/

// debugTime = millis();

// switch(debugState) {
//      case 0:

//         //Move in all four 90 degree motor angles, alternating between directions every 2 seconds.
//         debugTime = (debugTime - debugTime%2000)/2000;
//         if (debugTime == 1) {
//         Motor.Move(0, 0, 255);
//         }
//         if (debugTime == 2) {
//         Motor.Move(90, 0, 255);
//         }
//         if (debugTime == 3) {
//         Motor.Move(180, 0, 255);
//         }
//         if (debugTime == 4) {
//         Motor.Move(270, 0, 255);
//         }
//         break;
//     case 1:

//         //Move each motor individually, switching motors every 2 seconds.
//         debugTime = (debugTime - debugTime % 2000) / 2000;
//         if (debugTime == 1) {
//         Motor.motorFrontLeft.Move(255);
//         }
//         if (debugTime == 2) {
//         Motor.motorBackLeft.Move(255);
//         }
//         if (debugTime == 3) {
//         Motor.motorBackRight.Move(255);
//         }
//         if (debugTime == 4) {
//         Motor.motorFrontRight.Move(255);
//         }
//         break;
//     case 2:

//         //Output all significant camera values to the terminal.
//         Serial.print("Ball: ");
//         Serial.print(camera.ballAngle);
//         Serial.print(", ");
//         Serial.print("Yellow Goal: ");
//         Serial.print(camera.yGoalAngle);
//         Serial.print(", ");
//         Serial.print("Blue Goal: ");
//         Serial.println(camera.bGoalAngle);
//         break;  
//     case 3:

//         //Output all significant compass values to the terminal.
//         Serial.print(compass.heading);
//         Serial.print(", ");
//         Serial.println(compass.correction);
//         break;
//     case 4:

//         //Output all significant light sensor values to the terminal.
//         break;
//     case 5:

//         //Output all significant light gate values to the terminal.
//         break;
//     case 6:
    
//         //Output all significant LRF/LIDAR values to the terminal.
//         break;
// }

/*|||DEBUG CODE|||*/

/*|||MAIN CODE|||*/

    camera.update();
    compass.updateGyro();
    camera.angleCalc();

    // Motor.Move(0, 0, 255);
    // Motor.Move(90, 0, 255);

    point.AttackCalc(camera.ballx - 120, camera.bally - 120, 50, 20, 80, camera.blueGoalx - 120, camera.blueGoaly - 120);
    point.moveExec();

    // Motor.Move(270, 0, 255);
    Motor.Move(point.mvAngle, compass.correction, 255);   
    // Motor.Move()
    // Serial.print(point.nextPointX);
    // Serial.print(", ");
    // Serial.print(point.nextPointY);
    // Serial.print(" + ");
    // Serial.print(point.defPointX);
    // Serial.print(", ");
    // Serial.print(point.defPointY);
    // Serial.print(" + ");
    // Serial.println(point.mvAngle);
    // Serial.print(camera.ballx);
    // Serial.print(", ");
    // Serial.print(camera.bally);
    // Serial.print(camera.ballx - 120);
    // Serial.print(", ");
    // Serial.print(camera.bally - 120);
    // Serial.print(", ");
    // Serial.println(camera.ballAngle);
    // Motor.Move(0, 0, 255);
    // Motor.Move(point.mvAngle, 0, 255);
    
    // camera.corCalc(camera.ygoalCorrect, compass.correction);
    // Motor.Move(0, camera.realcor, 0);

    //role.attack(-compass.correction, camera.ballAngle, camera.ballcamDistance);
    // role.defend(-compass.correction, camera.ballAngle, camera.ballcamDistance, -camera.ballCorrect, camera.yGoalcamDistance, camera.yGoalAngle)

    /*|||MAIN CODE|||*/

}