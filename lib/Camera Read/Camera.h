#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Define.h>


class Camera{
  public:
    void setup();
    void update();
    void angleCalc();
    void Test();

    bool isAvailable();


    int camBuffer[CAM_BUFFER_NUM] = {0};
    int ballx = 0;
    int bally = 0;
    bool ballExists;

    int blueGoalx = 0;
    int blueGoaly = 0;
    bool blueExists;

    int yellowGoalx = 0;
    int yellowGoaly = 0;
    bool yellowExists;

    int ballAngle = 0;
    int yGoalAngle = 0;
    int bGoalAngle = 0;
    int bAngle = 0;
    int camDistance = 0;
    int ballcamDistance = 0;
    int ballDistance;
    int bGoalDistance;
    int yGoalDistance;
    int bGoalcamDistance;
    int yGoalcamDistance;
    int bgoalCorrect;
    int ygoalCorrect;
    int mvspeed;
    int losscounter;
    int milliangle;
    // int yGoalDistance = 0;
    // int bGoalDistance = 0;
  





};

#endif
