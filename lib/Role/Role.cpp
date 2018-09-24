#include <Arduino.h>
#include <Role.h>


void Role::action(int mvspeed, int state, int dir, int fakeangle, int balldis) {
    if (state == 0) {
      //Attacker Code:
      if (balldis <= 15) {
        Motor.Move(camera.bAngle, 0, mvspeed);
      } else {
        Motor.Move(camera.ballAngle, 0, mvspeed);
      }
    }
    if (state == 1) {
      //Defender Code
      if (fakeangle != -1) {
        Defend(mvspeed, dir, fakeangle, balldis);
      } else {
      Defend(mvspeed, dir, camera.bAngle, balldis);
  }
}
}

void Role::Defend(int mvspeed, int dir, int angle, int balldis) {
  if (angle <= 15 || angle >= 345) {
    Motor.Move(0, 0, 50);
  } else if (angle >= 270) {
    goalmove = (angle - 2 * (angle - 180)*1.5 + 120);
    //Remember to fix this shit lmao
    Motor.Move(270, 0, goalmove);
  } else if (angle <= 90) {
    goalmove = (angle*1.5) + 120;
    Motor.Move(90, 0, goalmove);
  } else {
    action(255, 0, dir, -1, camera.ballDistance);
  }

}
