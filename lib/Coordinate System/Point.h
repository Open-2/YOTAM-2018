#ifndef POINT_H
#define POINT_H

#include <Arduino.h>
#include "Camera.h"

class Point {
public:
    void pointCalc(int ballx, int bally);
    void AttackCalc(int ballx, int bally, int minOrbit, int kickRadiusX, int kickRadiusY);
    void DefendCalc(int ballx, int bally, int minRadius, int maxRadius, int goalx, int goaly, int kickRadiusX, int kickRadiusY);


    double defPointX;
    double defPointY;
    double nextPointX;
    double nextPointY;
    double nextDist;
    int mvAngle;
    int mvSpeed;

};


#endif