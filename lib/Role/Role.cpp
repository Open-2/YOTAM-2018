#include <Arduino.h>
#include <Role.h>


void Role::action(int mvspeed, int state, int dir) {
  if (debug.motoron == true) {
    if (state == 0) {
      //Attacker Code:
      Motor.Move(camera.bAngle, compass.correction, mvspeed);
    }
    if (state == 1) {
      //Defender Code
      Defend(mvspeed, dir);
    }
  }
}
void Role::Defend(int mvspeed, int dir) {

}
