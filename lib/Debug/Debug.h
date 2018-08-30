#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include <MotorController.h>
#include <Camera.h>
#include <Motors.h>

class Debug{
  public:
    void motorTest();
    void cameraTest();
    void compassTest();

    bool motoron = true;
    int timePassed = 0;
    int timeStart = 0;

private:
    MotorController Motor;
    Camera camera;
};



#endif
