#include "Role.h"
#include <math.h>

void Role::attack(int cor, int bangle, int bdist) {
    Serial.println("Attacking");

    //Run the attacker calculation function.
    attackerCalc(bangle, bdist);

    //If the ball does not exist, run this code.
    if (camera.ballExists == false) {

        //If it is still the first 5 seconds after being turned on, move directly forwards.
        if (millis() < 5000) {
            Motor.Move(0, cor, 255); 

        //Otherwise, run the search code.
        } else {
            Motor.Move(180, cor, 125);
        }
    
    //Otherwise, orbit the ball.
    } else {
    Motor.Move(moveangle, cor, mvspeed);
    }
}

void Role::defend(int cor, int bangle, int bdist, int bcor, int goaldist, int goalangle) {
    Serial.println("Defending");

    //Run the defender calculation function.
    defenderCalc(bangle, bdist, goaldist, goalangle); 

    //If the ball is behind the robot, run the attacker orbit to get it back in front.
    if (bangle > 70 && bangle < 290) {  
        attack(cor, bangle, bdist);

    //Otherwise, run the normal defender code.
    } else {  
        Motor.Move(moveangle, bcor, mvspeed);
    }

    //If the combined distance of the ball and the goal is high enough, run the next if else statement. 
    if ((bdist + goaldist) > 200) { 

        //If the ball is behind and the above is still true, move towards the goal.
        if (bangle > 70 && bangle < 290) {
            Motor.Move(goalangle, cor, 255);

        //Otherwise, orbit the ball and function as an attacker.
        } else {
            attack(cor, bangle, bdist);
        }
    }
}

void Role::defenderCalc(int bangle, int bdist, int goaldist, int goalangle) {
    Serial.println("Defender Calculating");
    mvspeed = 150;

    //When the goal is too far away, move back towards it.
    if (goaldist > 80) moveangle = goalangle;

    //When the goal is too close, move away from the goal.
    if (goaldist < 70) moveangle > 180 ? moveangle = moveangle += -180 : moveangle += 180;

    //When the ball is to the left but not behind, move left.
    if (bangle < 70 && bangle > 25) {
        mvspeed = bangle * 2;
        moveangle = 90;
    }

    //When the ball is to the right but not behind, move right.
    if (bangle > 290 && bangle < 335) {
        mvspeed = (bangle + 2 * (180 - bangle)) * 2;
        moveangle = 270;
    }

    //When the ball is in front, surge.
    if (bangle > 335 || bangle < 25) moveangle = 0;

    //If the goal is much too far away, move towards the goal. This is given priority over all other values.
    if (goaldist > 110) moveangle = goalangle;
}

void Role::attackerCalc(int bangle, int bdist) {
    Serial.println("Attacker Calculating");
    
    mvspeed = 150;

    //If the ball angle is more than 180, take away 360.
    if (bangle > 180) bangle -= 360;

    //If the absolute value of the ball angle is more than 100, move to the side opposite to the ball with a slight tendency towards backwards.
    if (abs(bangle) > 100) {
        bangle > 0 ? moveangle = 220 : moveangle = 140; 

    //Otherwise, move at an angle relative to the ball defined by the equation movement angle = ball angle multiplied by a tested value.
    } else {
        moveangle = bangle * 1.4;
    }

    //If the absolute value of the ball angle is less than 50, proceed.
    if (abs(bangle) < 50) {

        //If the absolute value of the ball angle is less than 15, surge into the ball.
        if (abs(bangle) < 15) {
            moveangle = 0;

        //Otherwise, move angle is offest in the opposite direction of the ball.
        } else moveangle = (bangle < 0 ? bangle + 15 : bangle - 15);
    }
    
    //If the distance to the ball is above 90 pixels, move directly towards the ball.
    if (bdist > 90) moveangle = bangle;
}


