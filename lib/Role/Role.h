#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>
#include <MotorController.h>
#include <Camera.h>
#include <Compass.h>
#include <Debug.h>


class Role{
  public:
    void action(int mvspeed, int state, int fakeangle, int balldis, int dir, int comp);
    int mvspeed = 0;

  private:
    void Defend(int mvspeed, int angle, int balldis, int dir);
    int state;
    int dir;
    int goalmove = 0;
    int goalCorrect;
    int balldis = 0;
    MotorController Motor;
    Compass compass;
    Camera camera;
    Debug debug;

};

#endif
