#ifndef POINT_H
#define POINT_H

#include <Arduino.h>
#include "Camera.h"

class Point {
public:
    void pointCalc(int ballx, int bally, int minOrbit, int kickRadius);
    void nexPointCalc();

    double defPointX;
    double defPointY;
    double nextPointX;
    double nextPointY;
    double nextDist;
    int mvAngle;
    int mvSpeed;

};


#endif