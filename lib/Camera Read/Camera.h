#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <Define.h>
#include <Common.h>

class Camera{
  public:
    void setup();
    void update();
    void angleCalc();
    // void defenceCalc(double heading);
    void Test();

    void corCalc(int val1, int val2);

    bool isAvailable();

    // int forwardmove;
    // int sidemove;

    int realcor;
    int camBuffer[CAM_BUFFER_NUM] = {0};
    int ballx = 0;
    int bally = 0;
    int blueGoalx = 0;
    int blueGoaly = 0;
    int yellowGoalx = 0;
    int yellowGoaly = 0;
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
    int milliangle;
    int ballCorrect;
    // int yGoalDistance = 0;
    // int bGoalDistance = 0;

    int mvspeed = 255;
    int losscounter;

    bool ballExists;
    bool blueExists;
    bool yellowExists;
    
};
#endif
