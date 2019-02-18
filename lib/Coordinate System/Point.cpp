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
    Serial.println("Calculating Coordinates");
}

void Point::moveExec(){
    mvAngle = (450 - degrees(atan2(nextPointX, nextPointY))) - 90;
    mvAngle = (mvAngle % 360);
}

void Point::AttackCalc(int ballx, int bally, int minOrbit, int kickRadiusX, int kickRadiusY, int goalx, int goaly){
    ballOrbitCalc(ballx, bally, goalx, goaly);
    ballChangeX = 0;
    ballChangeY = -minOrbit;
    ballLock = true;
    goalLock = false;
    if (abs(sqrt(pow((ballx - nextPointX), 2) + (pow((bally - nextPointY), 2)))) <= minOrbit){
        nextDist = minOrbit / abs(sqrt(pow((nextPointX - ballx), 2) + (pow((nextPointY - bally), 2))));
        nextPointX = ballx + ((nextPointX - ballx) * nextDist);
        nextPointY = bally + ((nextPointY - bally) * nextDist);
    }
    mvSpeed = 25 * abs(sqrt(pow((ballx - nextPointX), 2) + (pow((bally - nextPointY), 2))));
    if (abs(nextPointX) <= kickRadiusX && abs(nextPointY) <= kickRadiusY) {
        ballChangeX = 0;
        ballChangeY = 0;
        ballLock = true;
        mvSpeed = 255;
        ballOrbitCalc(ballx, bally, goalx, goaly);
    }
}


void Point::DefendCalc(int ballx, int bally, int minRadius, int maxRadius, int goalx, int goaly, int kickRadiusX, int kickRadiusY){
    ballChangeX = 0;
    ballChangeY = 0;
    ballLock = true;
    goalLock = false;
    Serial.println("Restarting Loop");
    ballOrbitCalc(ballx, bally, goalx, goaly);
    // if (abs(sqrt(pow((goalx - nextPointX), 2) + (pow((goaly - nextPointY), 2)))) >= 60) {
    //     nextDist = 60 / abs(sqrt(pow((goalx), 2) + (pow((goaly), 2))));
    //     nextPointX = (goalx + ((nextPointX - goalx) * nextDist));
    //     nextPointY = (goaly + ((nextPointY - goaly) * nextDist));
    //     Serial.println("Too close to the ball, moving around.");
    // } else {
        //     returnCheck = false;
        // }
        if (abs(ballx - nextPointX) <= kickRadiusX && abs(bally - nextPointY) <= kickRadiusY && bally >= 0){
            Serial.println("Checking for kick distance.");
            if (abs(sqrt(pow((goalx - nextPointX), 2) + (pow((goaly - nextPointX), 2)))) <= maxRadius + 20){
                ballChangeX = 0;
                ballChangeY = 0;
                ballLock = true;
                goalLock = false;
                mvSpeed = 255;
                ballOrbitCalc(ballx, bally, goalx, goaly);
                Serial.println("Close enough to goal, kicking.");
            } else {
                returnCheck = true;
                Serial.println("Much too far from the goal, force returning.");
            }
        } else {
            Serial.println("Not within kick distance, continuing to move.");

        }
        if (returnCheck == true){
            goalChangeX = 0;
            goalChangey = 0;
            goalLock = true;
            ballLock = false;
            Serial.println("Returning to Goal. (Returncheck == True)");
        }
        Serial.print("Ball Coordinates: ");
        Serial.print(ballx);
        Serial.print(", ");
        Serial.println(bally);
        Serial.print("Objective Coordinates: ");
        Serial.print(defPointX);
        Serial.print(", ");
        Serial.print(defPointY);
        Serial.print(" + ");
        Serial.print(nextPointX);
        Serial.print(", ");
        Serial.println(nextPointY);
        Serial.print("Movement Angle: ");
        Serial.println(mvAngle);
}
