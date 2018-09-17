#ifndef DEFINES_H
#define DEFINES_H

//Compass Definitions
#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

#define COMPASS_CALIBRATION 1.39
#define COMPASS_CALIBRATION_TIME 1000

//Motor Definitions

#define MOTOR_ANGLE 45

#define MOTOR_FRONT_LEFT_ENA 8
#define MOTOR_FRONT_LEFT_IN1 9
#define MOTOR_FRONT_LEFT_IN2 10
#define MOTOR_FRONT_LEFT_REVERSED false
#define MOTOR_BACK_LEFT_ENA 13
#define MOTOR_BACK_LEFT_IN1 11
#define MOTOR_BACK_LEFT_IN2 12
#define MOTOR_BACK_LEFT_REVERSED true
#define MOTOR_BACK_RIGHT_ENA 2
#define MOTOR_BACK_RIGHT_IN1 3
#define MOTOR_BACK_RIGHT_IN2 4
#define MOTOR_BACK_RIGHT_REVERSED false
#define MOTOR_FRONT_RIGHT_ENA 7
#define MOTOR_FRONT_RIGHT_IN1 5
#define MOTOR_FRONT_RIGHT_IN2 6
#define MOTOR_FRONT_RIGHT_REVERSED false

//Camera Definitions

#define CAM_BUFFER_NUM 7

#endif
