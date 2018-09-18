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
      Defend(mvspeed, dir, camera.bAngle);
  }
}

void Role::Defend(int mvspeed, int dir, int angle) {
  if (angle <= 15 || angle >= 345) {
    Motor.Move(0, 0, 50);
  } else if (angle >= 270) {
    goalmove = (angle - 2 * (angle - 180)*1.5 + 120);
    Motor.Move(270, 0, goalmove);
  } else if (angle <= 90) {
    goalmove = (angle*1.5) + 120;
    Motor.Move(90, 0, goalmove);
  } else if (angle <= 185 && angle >= 165) {
    if (angle > 180) {
      Motor.Move(90, 0, 150);
    } else {
      Motor.Move(270, 0, 150);
    }
  } else {
    Motor.Move(180, 0, 255);
  }

}
