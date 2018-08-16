#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#define TO_RADIANS 0.01745329251994329576923690768489

struct Vector3D {
  double x;
  double y;
  double z;
};

int sign(int value);

int sign(double value);

double doubleAbs(double value);

int mod (int x, int m);

double doubleMod(double value, double maxValue);

double convertRawAcceleration(int raw);

double convertRawGyro(int raw);

double degreesToRadians(double degrees);

#endif
