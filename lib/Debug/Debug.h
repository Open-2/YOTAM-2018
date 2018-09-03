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


private:
    MotorController Motor;
    Camera camera;
    void Motorrun(int motornum);
    int timeStart = 0;
    int timeCurrent = 0;
    int timePassed = 0;
};



#endif
