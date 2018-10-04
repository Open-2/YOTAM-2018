#include <Arduino.h>
#include <Role.h>


void Role::action(int mvspeed, int state, int fakeangle, int balldis, int dir, int comp, int bangle, int correction) {
    Motor.Setup();

    if (state != -1) {
      //Attacker Code:
    if (comp == 0) {
      if (dir == 0) {
      if (balldis <= 15) {
        Motor.Move(state, camera.yGoalAngle, mvspeed);
      } else {
        Motor.Move(state, camera.yGoalAngle, mvspeed);
      }
    } else if (dir == 1) {
    if (balldis <= 15) {
      Motor.Move(state, camera.bgoalCorrect, mvspeed);
    } else {
      Motor.Move(state, camera.bgoalCorrect, mvspeed);
        }
      }
    } else if (comp == 1) {
      if (balldis <= 15) {
        Motor.Move(state, correction, mvspeed);
      } else {
        Motor.Move(state, correction, mvspeed);
        }
      }
    }
    if (state == -1) {
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
    if (angle >= 270) {
    goalmove = (-0.0104938 * pow(angle, 2) + 3.77778 * angle + (-1.1369 * pow(10, -14)));
    Motor.Move(90, camera.ygoalCorrect, goalmove);
  } else if (angle <= 90) {
    goalmove = (-0.0104938 * pow(angle, 2) + 3.77778 * angle + (-1.1369 * pow(10, -14)));
    Motor.Move(270, camera.ygoalCorrect, goalmove);
  }
  if (camera.yGoalDistance > 20) {
    Motor.Move(180, camera.ygoalCorrect, 255);
  } else if (camera.yGoalDistance < 10) {
    Motor.Move(0, camera.ygoalCorrect, 255);
  }
}

void Role::shit(int ygoalx, int ygoaly, int bgoalx, int bgoaly, int ballx, int bally, int dir, int millistart, int correction) {
  Motor.Setup();
  if (dir == 0) {
    if (ygoalx == 0 && ygoaly == 0) {
      camera.ygoalCorrect = camera.bgoalCorrect;
      millistart = 0;
      // Serial.println("Stage 1");
    if (bgoalx == 0 && bgoaly == 0) {
      camera.ygoalCorrect = correction;
      camera.bAngle = camera.ballAngle;
      millistart = 0;
      // Serial.println("Stage 2");
    if (ballx == 0 && bally == 0) {
      //Some circular movement here
      // Serial.println("Stage 3");
      if (millistart == 0) {
        millistart = millis();
      }
      milliangle = (millis())/5;
      camera.bAngle = milliangle;
      if (milliangle == 360) {
        millistart = 0;
      }
      Serial.println(milliangle);
      Motor.Move(milliangle, correction, 255);
        }
          }
    } else {
      //action(shit to put in inputs)
      Motor.Move(camera.bAngle, camera.ygoalCorrect, 255);
      // Serial.println("Not executed");
    }
  } else if (dir == 1) {
    if (ygoalx == 0 && ygoaly == 0) {
      camera.ygoalCorrect = camera.bgoalCorrect;
      millistart = 0;
      // Serial.println("Stage 1");
    if (bgoalx == 0 && bgoaly == 0) {
      camera.ygoalCorrect = correction;
      camera.bAngle = camera.ballAngle;
      millistart = 0;
      // Serial.println("Stage 2");
    if (ballx == 0 && bally == 0) {
      //Some circular movement here
      // Serial.println("Stage 3");
      if (millistart == 0) {
        millistart = millis();
      }
      milliangle = (millis() - millistart) / 10;
      camera.bAngle = milliangle;
      if (milliangle == 360) {
        millistart = millis();
      }
      Serial.println(milliangle);
      Motor.Move(milliangle, correction, 255);
        }
      }
    } else {
      //action(shit to put in inputs)
      Motor.Move(camera.bAngle, camera.ygoalCorrect, 255);
      // Serial.println("Not executed");
    }
  }
}
