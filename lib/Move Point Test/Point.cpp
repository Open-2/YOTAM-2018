#include "Point.h"
#include <Arduino.h>

void Point::pointCalc(int ballx, int bally, int minOrbit, int kickRadius){
    defPointX = ballx;
    defPointY = bally;

    nextPointX = defPointX/50;
    nextPointY = defPointY/50;
    if (abs(sqrt(pow((ballx - nextPointX), 2) + (pow((bally - nextPointY), 2)))) <= minOrbit) {
        nextDist = minOrbit / abs(sqrt(pow((nextPointX - ballx), 2) + (pow((nextPointY - bally), 2))));
        nextPointX = ballx + ((nextPointX - ballx) * nextDist);
        nextPointY = bally + ((nextPointY - bally) * nextDist);
    }
    mvAngle = (450 - degrees(atan2(nextPointX, nextPointY))) - 90;
    mvAngle = (mvAngle % 360);
}
