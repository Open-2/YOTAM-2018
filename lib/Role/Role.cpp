#include <Arduino.h>
#include <Role.h>


void Role::action(int mvspeed, int state) {
  if (debug.motoron == true) {
  if (state == 1) {
    Motor.Move(camera.bAngle, compass.correction, mvspeed);
  }
  //else: {
    //Insert defender code here
//  }
  }
}
