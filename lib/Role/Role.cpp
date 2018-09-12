#include <Arduino.h>
#include <Role.h>
#include <Motors.h>
#include <Camera.h>
#include <Compass.h>

Motors Motor;
Compass compass;
Camera camera;


void Role::action(int mvspeed, int state) {
  if (state == 1) {
    Motor.Move(camera.bAngle, compass.correction, mvspeed);
  }
  //else: {
    //Insert defender code here
//}

}
