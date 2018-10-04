#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>
#include <MotorController.h>
#include <Camera.h>
#include <Compass.h>
#include <Debug.h>


class Role{
  public:
    void action(int mvspeed, int state, int fakeangle, int balldis, int dir, int comp, int bangle, int correction);
    int mvspeed = 0;
    void shit(int ygoalx, int ygoaly, int bgoalx, int bgoaly, int ballx, int bally, int dir, int millistart, int correction, int ballAngle, int bAngle, int bgoalCorrect, int ygoalCorrect);

  private:
    void Defend(int mvspeed, int angle, int balldis, int dir);
    int state;
    int dir;
    int goalmove = 0;
    int goalCorrect;
    int balldis = 0;
    int milliangle;
    int mvangle;
    int mvcorrect;
    MotorController Motor;
    // Compass compass;
    Camera camera;
    Debug debug;

};

#endif
