#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>
#include <MotorController.h>
#include <Camera.h>
#include <Compass.h>
#include <Debug.h>


class Role{
  public:
    void action(int mvspeed, int state, int dir);
    int mvspeed = 0;

  private:
    void Defend(int mvspeed, int dir);
    int state;
    int dir;
    MotorController Motor;
    Compass compass;
    Camera camera;
    Debug debug;

};

#endif
