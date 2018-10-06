#include <Arduino.h>
#include <Goalie.h>
#include <math.h>

void goalieCalc() {
    //Calculate the position of where we want to orbit to using the angle to the goal and the distance on the cam to the goal.
    // goalieDisplacement = 20;
    // BR = camera.ballcamDistance;
    // GR = camera.yGoalcamDistance;
    // diffangle = camera.ballAngle - camera.yGoalAngle
    // if (camera.yellowExists) {
    //     GB = sqrt(BR * BR + GR * GR - 2 * BR * GR * cos(diffangle));
    //     BI = GB - goalieDisplacement;
    //     tempbeta = (BR * BR + GB * GB - GR * GR)/(2 * BR * GB);
    // }
}

void goalieRun() {
    //If to left, move right according to equation speed = (-0.0104938 * pow(angle, 2) + 3.77778 * angle + (-1.1369 * pow(10, -14))) in the direction required.    //Use the same equation for the vertical movement
    //Use the above equation for vertical movement also, and find the average of the 2 directions you are moving.
    //If the ball reaches a certain distance to the robot, begin to orbit the ball as per the normal attacker code.
    //If the defender leaves a certain range of the goal, move towards the goal.
    if (camera.yellowExists) {
        if (camera.ballExists) {
            if (camera.yGoalDistance >= 100) {
                Motor.Move(camera.yGoalAngle, compass.correction, 255);
            } else if (camera.ballcamDistance < 70) {
                Motor.Move(camera.bAngle, compass.correction, 255);
            } else if (camera.yGoalAngle < 120) {
                goaliemv = (-0.0104938 * pow(camera.ballAngle, 2) + 3.77778 * camera.ballAngle + (-1.1369 * pow(10, -14)));
                Motor.Move(90, compass.correction, goaliemv);
            } else if (camera.yGoalAngle > 240) {
                goaliemv = (-0.0104938 * pow(camera.ballAngle, 2) + 3.77778 * camera.ballAngle + (-1.1369 * pow(10, -14)));
                Motor.Move(270, compass.correction, goaliemv);
            } else {
                Motor.Move(camera.bAngle, compass.correction, 255);
            }
        } else {
            if (camera.yGoalDistance >= 100) {
                Motor.Move(camera.yGoalAngle, compass.correction, 255);
            } else if (camera.yGoalAngle < 120) {
                goaliemv = (-0.0104938 * pow(camera.ballAngle, 2) + 3.77778 * camera.ballAngle + (-1.1369 * pow(10, -14)));
                Motor.Move(90, compass.correction, goaliemv);
            } else if (camera.yGoalAngle > 240) {
                goaliemv = (-0.0104938 * pow(camera.ballAngle, 2) + 3.77778 * camera.ballAngle + (-1.1369 * pow(10, -14)));
            }
        }
        
    } else {
        if (camera.ballExists) {
            Motor.Move(camera.bAngle, compass.correction, 255);
        } else {
            //Search pattern
        }
    }
}
