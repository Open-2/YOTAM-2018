#include "Role.h"
#include <math.h>

void Role::attack(int cor, int bangle, int bdist) {
    Serial.println("Attacking");
    attackerCalc(bangle, bdist);
    if (bangle == 135) {
    if (millis() < 5000) {
        Motor.Move(0, cor, 255); 
    } else {
        Motor.Move(180, cor, 125);
        }
    }
    Motor.Move(moveangle, cor, mvspeed);
}

void Role::defend(int cor, int bangle, int bdist, int bcor, int goaldist, int goalangle) {
    Serial.println("Defending");
    defenderCalc(bangle, bdist, goaldist, goalangle);
    if (bangle > 90 && bangle < 270) {
        attack(cor, bangle, bdist);
    } else {
        Motor.Move(moveangle, bcor, mvspeed);
    }
}

void Role::defenderCalc(int bangle, int bdist, int goaldist, int goalangle) {
    Serial.println("Defender Calculating");
    if (bangle < 90 && bangle > 25) {
        mvspeed = bangle * 2.75;
        moveangle = 90;
    }
    if (bangle > 270 && bangle < 335) {
        mvspeed = (bangle + 2 * (180 - bangle)) * 2.75;
        moveangle = 270;
    }
    if (bangle > 335 || bangle < 25) {
        moveangle = 0;
        mvspeed = 255;
        } 
    if (goaldist > 90) {
        moveangle = goalangle;
        mvspeed = 255;
        }
}

void Role::attackerCalc(int bangle, int bdist) {
    Serial.println("Attacker Calculating");
    if (bangle > 180) bangle -= 360;
    if (abs(bangle) > 100) {
        bangle > 0 ? moveangle = 220 : moveangle = 140; 
    } else {
        moveangle = bangle * 1.4;
    }
    if (abs(bangle) < 50) {
        if (abs(bangle) < 15) {
            mvspeed = 255;
            moveangle = 0;
        } else if (bangle < 0) moveangle = (bangle < 0 ? bangle + 15 : bangle - 15);
    if (abs(bangle) > 100) moveangle = (moveangle > 0 ? 220 : 140);
    if (bdist > 90) moveangle = bangle;
    }
}


