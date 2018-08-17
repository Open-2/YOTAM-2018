#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Arduino.h"
#include <Motor.h>
#include "Common.h"

class MotorController{
public:
  double vector1, vector2, off;
  Motor motorFrontLeft;
  Motor motorFrontRight;
  Motor motorBackLeft;
  Motor motorBackRight;
  void Setup();
  void Move(int angle, int rotation, int speed);
  void Turn(int speed);
  void Brake();
  int weights [4] = {0, 0, 0, 0};
};


#endif
