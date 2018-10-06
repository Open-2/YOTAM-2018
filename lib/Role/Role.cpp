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
        Defend(mvspeed, fakeangle, balldis, dir, correction);
      } else {
      Defend(mvspeed, camera.bAngle, balldis, dir, correction);
  }
}
}

void Role::Defend(int mvspeed, int angle, int balldis, int dir, int correction) {
  Motor.Setup();
    if (angle > 330 || angle < 30) {
      Motor.Move(0, -correction, 255);
    }
    if (angle >= 90) {
    goalmove = (-0.0104938 * pow(angle, 2) + 3.77778 * angle + (-1.1369 * pow(10, -14)))+20;
    Motor.Move(90, correction, goalmove);
  } else if (angle <= 270) {
    goalmove = (-0.0104938 * pow(angle, 2) + 3.77778 * angle + (-1.1369 * pow(10, -14)))+20;
    Motor.Move(270, correction, goalmove);

  // }
  // if (camera.yGoalDistance > 70) {
  //   Motor.Move(180, correction, 255);
  // } else if (camera.yGoalDistance < 50) {
  //   Motor.Move(0, correction, 255);
  } else {
    Motor.Move(0, -correction, 0);
  }
}

void Role::shit(int ygoalx, int ygoaly, int bgoalx, int bgoaly, int ballx, int bally, int dir, int millistart, int correction, int ballAngle, int bAngle, int bgoalCorrect, int ygoalCorrect) {
  Motor.Setup();
  mvangle = bAngle;
  if (dir == 0) {
    mvcorrect = -ygoalCorrect;
    // if (ygoalx == 0 && ygoaly == 0) {
    //   mvcorrect = bgoalCorrect;
    //   millistart = 0;
    //   Serial.println("Stage 1");
    // if (bgoalx == 0 && bgoaly == 0) {
    //   mvcorrect = -correction;
    //   mvangle = ballAngle;
    //   millistart = 0;
    //   Serial.println("Stage 2");
    if (ballx == 0 && bally == 0) {
      //Some circular movement here
      Serial.println("Stage 3");
      milliangle = millis()/1000;
      if (milliangle%2 == 0) {
        mvangle = 0;
      } else {
        mvangle = 180;
      }
      }
      // Serial.println(milliangle);
      // Motor.Move(milliangle, correction, 255);
    Motor.Move(0, mvcorrect, 0);
    Serial.print(mvangle);
    Serial.print(", ");
    Serial.println(mvcorrect);
    } else {
      //action(shit to put in inputs)
      Motor.Move(mvangle, mvcorrect, 255);
      Serial.print(mvangle);
      Serial.print(", ");
      Serial.println(mvcorrect);
      // Serial.println("Not executed");
    }
  // } else if (dir == 1) {
  //   if (ygoalx == 0 && ygoaly == 0) {
  //     bgoalCorrect = ygoalCorrect;
  //     millistart = 0;
  //     // Serial.println("Stage 1");
  //   if (bgoalx == 0 && bgoaly == 0) {
  //     bgoalCorrect = correction;
  //     bAngle = ballAngle;
  //     millistart = 0;
  //     // Serial.println("Stage 2");
  //   if (ballx == 0 && bally == 0) {
  //     //Some circular movement here
  //     // Serial.println("Stage 3");
  //     if (millistart == 0) {
  //       millistart = millis();
  //     }
  //     milliangle = (millis() - millistart) / 20;
  //     bAngle = milliangle;
  //     if (milliangle == 360) {
  //       millistart = millis();
  //     }
  //     // Serial.println(milliangle);
  //     Motor.Move(milliangle, correction, 255);
  //       }
  //     }
  //   } else {
  //     //action(shit to put in inputs)
  //     Motor.Move(bAngle, bgoalCorrect, 255);
  //     // Serial.println("Not executed");
  //   }
  }
