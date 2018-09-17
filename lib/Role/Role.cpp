#include <Arduino.h>
#include <Role.h>


void Role::action(int mvspeed, int state, int dir) {
    if (state == 0) {
      //Attacker Code:
      Motor.Move(0, 0, mvspeed);
      Serial.print("5");
    }
    if (state == 1) {
      //Defender Code
      Defend(mvspeed, dir);
  }
}

void Role::Defend(int mvspeed, int dir) {

}
