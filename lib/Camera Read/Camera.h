#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Define.h>


class Camera{
  public:

    void setup();
    void update();

    bool isAvailable();


    int camBuffer[CAM_BUFFER_NUM] = {0};
    int ballx = 0;
    int bally = 0;
    int blueGoalx = 0;
    int blueGoaly = 0;
    int yellowGoalx = 0;
    int yellowGoaly = 0;



};

#endif
