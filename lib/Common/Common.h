#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>

#define PI 3.1415926535897932384626433832795

#define TO_RADIANS 0.01745329251994329576923690768489
#define TO_DEGREES 57.29577951308232087679815481410517

double toDegrees(double rad);
double toRadians(double deg);

int mod(int n, int modulo);
double doubleMod(double value, double maxValue);

bool isAngleBetween(int angle, int leftAngle, int rightAngle);

double distanceBetween(double x1, double y1, double x2, double y2);

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
