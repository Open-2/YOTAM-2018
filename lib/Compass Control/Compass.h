#ifndef COMPASS_H
#define COMPASS_H

#include <I2C.h>
#include <Define.h>
#include <Common.h>

class Compass {
public:
  double calibration = COMPASS_CALIBRATION;

  Compass() {};
  void compassSetup();
  void compassCalc();

  Vector3D readAccelerometer();
  Vector3D readGyroscope();
  Vector3D readMagnetometer();

  void updateGyro();
  double calibrate();
  int correction = 0;
  double heading;
  int relativeHeading = 0;

private:
  long previousTime;

  double convertRawAcceleration(int raw){
      // Since we are using 2G range
      // -2g maps to a raw value of -32768
      // +2g maps to a raw value of 32767

      double a = (raw * 2.0) / 32768.0;
      return a;
  }

  double convertRawGyro(int raw) {
      // Since we are using 500 degrees/seconds range
      // -500 maps to a raw value of -32768
      // +500 maps to a raw value of 32767

      double g = (raw * 500.0) / 32768.0;
      return g;
  }
  const double kp = 0.45;
  const double kd = 0.9;
  unsigned long previousMillis = 0;
  unsigned long compMillis = 0;
  unsigned long currentMillis = 0;
  int previousHeading = 0;



};

//extern Compass compass;

#endif
