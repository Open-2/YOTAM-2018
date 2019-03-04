#ifndef POINT_H
#define POINT_H

#include <Arduino.h>
#include "Camera.h"

class Point {
public:
    void ballOrbitCalc(int ballx, int bally, int goalx, int goaly);
    void AttackCalc(int ballx, int bally, int goalx, int goaly);
    void DefendCalc(int ballx, int bally, int goalx, int goaly);
    void moveExec();


    double defPointX;
    double defPointY;
    double nextPointX;
    double nextPointY;
    double nextDist;
    int mvAngle;
    int mvSpeed;
    bool ballLock = false;
    bool goalLock = false;
    int ballChangeX;
    int ballChangeY;
    int goalChangeX;
    int goalChangey;
    bool returnCheck;

};


#endif