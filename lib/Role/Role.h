#ifndef ROLE_H
#define ROLE_H

#include "Arduino.h"
#include <MotorController.h>
#include <Camera.h>
#include <Compass.h>

class Role {
public:
    void attack(int cor, int bangle, int bdist);
    void defend(int cor, int bangle, int bdist, int bcor);
private:
    void defenderCalc(int bangle, int bdist);
    void attackerCalc(int bangle, int bdist);
    Camera camera;
    MotorController Motor;
    Compass compass;
    int mvspeed = 255;
    int moveangle;
};

#endif