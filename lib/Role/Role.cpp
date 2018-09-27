#include <Arduino.h>
#include <Role.h>


void Role::action(int mvspeed, int state, int fakeangle, int balldis, int dir, int comp) {
  Motor.Setup();
   

    
    if (state == 0) {
      //Attacker Code:
    if (comp == 0) {
      if (dir == 0) {
      if (balldis <= 15) {
        Motor.Move(camera.bAngle, camera.ygoalCorrect, mvspeed);
      } else {
        Motor.Move(camera.ballAngle, camera.ygoalCorrect, mvspeed);
      }
    } else if (dir == 1) {
    if (balldis <= 15) {
      Motor.Move(camera.bAngle, camera.bgoalCorrect, mvspeed);
    } else {
      Motor.Move(camera.ballAngle, camera.bgoalCorrect, mvspeed);
    }
    }
    } else if (comp == 1) {
      if (balldis <= 15) {
        Motor.Move(camera.bAngle, 0, mvspeed);
      } else {
        Motor.Move(camera.ballAngle, 0, mvspeed);
    }
    }
    }
    if (state == 1) {
      //Defender Code
      if (fakeangle != -1) {
        Defend(mvspeed, fakeangle, balldis, dir);
      } else {
      Defend(mvspeed, camera.bAngle, balldis, dir);
  }
}
}

void Role::Defend(int mvspeed, int angle, int balldis, int dir) {
  Motor.Setup();
  if (angle <= 20 || angle >= 340) {
    Motor.Move(0, 0, 100);
  } else if (angle >= 270) {
    goalmove = (-0.0104938 * pow(angle, 2) + 3.77778 * angle + (-1.1369 * pow(10, -14)));
    Motor.Move(90, 0, goalmove);
  } else if (angle <= 90) {
    goalmove = (-0.0104938 * pow(angle, 2) + 3.77778 * angle + (-1.1369 * pow(10, -14)));
    Motor.Move(270, 0, goalmove);
  } else {
    action(255, 0, -1, camera.ballDistance, dir, 0);
  }

}
