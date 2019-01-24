#include "Point.h"
#include <Arduino.h>

void Point::ballOrbitCalc(int ballx, int bally, int goalx, int goaly){
    if (goalLock == true){
        defPointX = goalx + goalChangeX;
        defPointY = goaly + goalChangey;
    }
    if (ballLock == true){
        defPointX = ballx + ballChangeX;
        defPointY = bally + ballChangeY;
    }
    nextPointX = defPointX/50;
    nextPointY = defPointY/50;
}

void Point::moveExec(){
    mvAngle = (450 - degrees(atan2(nextPointX, nextPointY))) - 90;
    mvAngle = (mvAngle % 360);
}

void Point::AttackCalc(int ballx, int bally, int minOrbit, int kickRadiusX, int kickRadiusY, int goalx, int goaly){
    ballChangeX = 0;
    ballChangeY = 40;
    ballLock = true;
    ballOrbitCalc(ballx, bally, goalx, goaly);
    if (abs(sqrt(pow((ballx - nextPointX), 2) + (pow((bally - nextPointY), 2)))) <= minOrbit){
        nextDist = minOrbit / abs(sqrt(pow((nextPointX - ballx), 2) + (pow((nextPointY - bally), 2))));
        nextPointX = ballx + ((nextPointX - ballx) * nextDist);
        nextPointY = bally + ((nextPointY - bally) * nextDist);
    }
    // mvSpeed = 25 * abs(sqrt(pow((ballx - nextPointX), 2) + (pow((bally - nextPointY), 2))));
    // if (abs(nextPointX) <= kickRadiusX && abs(nextPointY) <= kickRadiusY) {
    //     ballChangeX = 0;
    //     ballChangeY = 0;
    //     ballLock = true;
    //     mvSpeed = 255;
    // }
}


void Point::DefendCalc(int ballx, int bally, int minRadius, int maxRadius, int goalx, int goaly, int kickRadiusX, int kickRadiusY){
    ballChangeX = 0;
    ballChangeY = 40;
    ballLock = true;
    goalLock = false;
    if (abs(sqrt(pow((goalx), 2) + (pow((goaly), 2)))) <= minRadius) {
        nextDist = minRadius / abs(sqrt(pow((goalx), 2) + (pow((goaly), 2))));
        nextPointX = ((goalx) * nextDist);
        nextPointY = ((goaly) * nextDist);
    } else {
        returnCheck = false;
    }
    if (abs(nextPointX) <= kickRadiusX && abs(nextPointY) <= kickRadiusY){
        if (abs(sqrt(pow((goalx), 2) + (pow((goaly), 2)))) <= maxRadius){
            ballChangeX = 0; 
            ballChangeY = 0;
            ballLock = true;
            goalLock = false;
            mvSpeed = 255;
        } else {
            returnCheck = true;
        }
    }
    if (returnCheck == true){
        goalChangeX = 0;
        goalChangey = 0;
        goalLock = true;
        ballLock = false;
    }
    ballOrbitCalc(ballx, bally, goalx, goaly);
}
