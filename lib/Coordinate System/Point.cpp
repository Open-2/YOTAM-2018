#include "Point.h"
#include <Arduino.h>

void Point::pointCalc(int defx, int defy){
    defPointX = defx;
    defPointY = defy;

    nextPointX = defPointX/50;
    nextPointY = defPointY/50;
}

void Point::AttackCalc(int ballx, int bally, int minOrbit, int kickRadiusX, int kickRadiusY){
    pointCalc(ballx, (bally - minOrbit));
    if (abs(sqrt(pow((ballx - nextPointX), 2) + (pow((bally - nextPointY), 2)))) <= minOrbit){
        nextDist = minOrbit / abs(sqrt(pow((nextPointX - ballx), 2) + (pow((nextPointY - bally), 2))));
        nextPointX = ballx + ((nextPointX - ballx) * nextDist);
        nextPointY = bally + ((nextPointY - bally) * nextDist);
    }
    mvSpeed = 25 * abs(sqrt(pow((ballx - nextPointX), 2) + (pow((bally - nextPointY), 2))));
    mvAngle = (450 - degrees(atan2(nextPointX, nextPointY))) - 90;
    mvAngle = (mvAngle % 360);
    if (abs(nextPointX) <= kickRadiusX && abs(nextPointY) <= kickRadiusY) {
        nextPointX = ballx;
        nextPointY = bally;
        mvSpeed = 255;
    }
}


void Point::DefendCalc(int ballx, int bally, int minRadius, int maxRadius, int goalx, int goaly, int kickRadiusX, int kickRadiusY){
    pointCalc(ballx, bally - 40);
    if (abs(sqrt(pow((goalx), 2) + (pow((goaly), 2)))) >= minRadius){
        nextDist = minRadius / abs(sqrt(pow((goalx), 2) + (pow((goaly), 2))));
        nextPointX = ((goalx) * nextDist);
        nextPointY = ((goaly) * nextDist);
    }
    if (abs(nextPointX) <= kickRadiusX && abs(nextPointY) <= kickRadiusY){
        if (abs(sqrt(pow((goalx), 2) + (pow((goaly), 2)))) <= maxRadius){
            nextPointX = ballx;
            nextPointY = bally;
            mvSpeed = 255;
        } else {
            defPointX = goalx;
            defPointY = goaly;
        }
    }
}
