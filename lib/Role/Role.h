#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>
#include <MotorController.h>
#include <Camera.h>

class Role {
public:
    void attack();
    void defend();
private:
    void defenderCalc();
    void attackerCalc();
    Camera camera;
    MotorController Motor;
    int mvspeed;
};

#endif