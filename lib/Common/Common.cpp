#include "Common.h"
#include <Math.h>

int sign(int value) {
  return value >= 0 ? 1 : -1;
}

int sign(double value) {
  return value >= 0 ? 1 : -1;
}

double doubleAbs(double value) {
  return value * sign(value);
}

int mod(int x, int m) {
  int r = x % m;
  return r <0 ? r + m : r;
}

double doubleMod(double value, double maxValue) {
  return fmod((value +maxValue), maxValue);
}

// double ConvertRawAcceleration(int raw){
//
//   double a = (raw * 2.0) / 32768.0;
//   return a;
// }
//
// double convertRawGyro(int raw) {
//
//   double g = (raw * 500.0) / 32768.0;
//   return g;

//}

double degreesToRadians(double degrees) {
  return degrees * TO_RADIANS;
}



// double toDegrees(double rad){
//   return rad*TO_DEGREES;
// }
//
// double toRadians(double deg){
//   return deg*TO_RADIANS;
// }
//
// int mod(int n, int modulo){
//   int r = n % modulo;
//   return r < 0 ? r + modulo : r;
// }
//
// double doubleMod(double value, double maxValue) {
//     return fmod((value + maxValue), maxValue);
// }
//
// bool isAngleBetween(int angle, int leftAngle, int rightAngle){
//   if(rightAngle < leftAngle){
//     return angle < rightAngle || angle > leftAngle;
//   }
//   else{
//     return angle < rightAngle && angle > leftAngle;
//   }
// }

double distanceBetween(double x1, double x2, double y1, double y2)
{
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}