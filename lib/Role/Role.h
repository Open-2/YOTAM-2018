#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>
#include <MotorController.h>
#include <Camera.h>
#include <Compass.h>
#include <Debug.h>


class Role{
  public:
    void action(int mvspeed, int state);
    int mvspeed = 0;

  private:
    int state;
    MotorController Motor;
    Compass compass;
    Camera camera;
    Debug debug;

};

#endif
