#include <Role.h>
#include <math.h>

void Role::attack() {
    Serial.println("Attacking");
}

void Role::defend() {
    Serial.println("Defending");
}

void Role::defenderCalc() {
    Serial.println("Defender Calculating");
}

void Role::attackerCalc() {
    Serial.println("Attacker Calculating");
    if (camera.ballx != 0 && camera.bally != 0) {
        if (camera.ballAngle > 180) camera.ballAngle -= 360;
        if (abs(camera.ballAngle) > 100) {
            camera.ballAngle > 0 ? camera.bAngle = 220 : camera.bAngle = 140; 
        } else {
            camera.bAngle = camera.ballAngle * 1.4;
        }
        if (abs(camera.ballAngle) < 50) {
            if (abs(camera.ballAngle) < 15) {
                mvspeed = 255;
                camera.bAngle = 0;
            } else if (camera.ballAngle < 0) camera.bAngle = (camera.ballAngle < 0 ? camera.ballAngle + 15 : camera.ballAngle - 15);
        if (abs(camera.ballAngle) > 100) camera.bAngle = (camera.bAngle > 0 ? 220 : 140);
        if (camera.ballcamDistance > 90) camera.bAngle = camera.ballAngle;
        }
    }
}


