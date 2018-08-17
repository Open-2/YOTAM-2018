#include "Common.h"

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

}

double degreesToRadians(double degrees) {
  return degrees * TO_RADIANS;
}
