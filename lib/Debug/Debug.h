#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include <MotorController.h>
#include <Camera.h>
#include <Motors.h>
#include <Compass.h>

class Debug{
  public:
    void motorTest();
    void cameraTest();
    void compassTest();
    void motorTestState(int state);
    void Debug::setCamera(Camera *cam);
    bool motoron = true;


private:
    MotorController Motor;
    Compass compass;
    int timeStart = 0;
    int timeCurrent = 0;
    int timePassed = 0;
    int bAngleFake = 0;
    int timeState = 0;
    Camera *camera;
};



#endif
