#ifndef GOALIE_H
#define GOALIE_H

#include <Arduino.h>
#include <Camera.h>
#include <Compass.h>
#include <MotorController.h>

class Goalie{
public:
    void goalieCalc();
    void goalieRun(); 
private:
    Camera camera;
    Compass compass;
    MotorController Motor;
    int goaliex;
    int goaliey;
    double goalieDisplacement;
    double goalieAngle;
    double GB; //Goal to ball
    double GR; //Goal to robot
    double BR; //Ball to robot
    double diffangle;
    double BI;
    double tempbeta;
    double beta;
    int goaliemv;
};

#endif