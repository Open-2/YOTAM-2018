#ifndef DEFINES_H
#define DEFINES_H

/*|||Compass Definitions*/
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

/*|||Motor Definitions|||*/
#define MOTOR_ANGLE 45

// //Mind Pins
// #define MOTOR_FRONT_LEFT_ENA 7
// #define MOTOR_FRONT_LEFT_IN1 6
// #define MOTOR_FRONT_LEFT_IN2 5
// #define MOTOR_FRONT_LEFT_REVERSED true
// #define MOTOR_BACK_LEFT_ENA 2
// #define MOTOR_BACK_LEFT_IN1 4
// #define MOTOR_BACK_LEFT_IN2 3
// #define MOTOR_BACK_LEFT_REVERSED true
// #define MOTOR_BACK_RIGHT_ENA 8
// #define MOTOR_BACK_RIGHT_IN1 9
// #define MOTOR_BACK_RIGHT_IN2 10
// #define MOTOR_BACK_RIGHT_REVERSED true
// #define MOTOR_FRONT_RIGHT_ENA 13
// #define MOTOR_FRONT_RIGHT_IN1 11
// #define MOTOR_FRONT_RIGHT_IN2 12
// #define MOTOR_FRONT_RIGHT_REVERSED true

//Yeast Pins
#define MOTOR_FRONT_LEFT_ENA 2
#define MOTOR_FRONT_LEFT_IN1 3
#define MOTOR_FRONT_LEFT_IN2 4
#define MOTOR_FRONT_LEFT_REVERSED false
#define MOTOR_BACK_LEFT_ENA 7
#define MOTOR_BACK_LEFT_IN1 5
#define MOTOR_BACK_LEFT_IN2 6
#define MOTOR_BACK_LEFT_REVERSED true
#define MOTOR_BACK_RIGHT_ENA 10
#define MOTOR_BACK_RIGHT_IN1 9
#define MOTOR_BACK_RIGHT_IN2 8
#define MOTOR_BACK_RIGHT_REVERSED false
#define MOTOR_FRONT_RIGHT_ENA 13
#define MOTOR_FRONT_RIGHT_IN1 11
#define MOTOR_FRONT_RIGHT_IN2 12
#define MOTOR_FRONT_RIGHT_REVERSED false


/*|||Camera Definitions|||*/
#define CAM_BUFFER_NUM 7

/*|||LIDAR/LRF Definitions|||*/

/*|||Light Gate Definitions|||*/

/*|||Light Sensor Definitions*/

// EEPROM address of the debug settings
#define DEBUG_SETTINGS_EEPROM_ADDRESS 0

/*|||Screen Definitions|||*/

// Pins

#define SCREEN_YP A7
#define SCREEN_XM A6
#define SCREEN_YM 48
#define SCREEN_XP 46

// Min and max X and Y values to map touch screen values to X and Y values
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// Resistance of the screen with no pressure
#define TS_RESISTANCE 255

// Min and max pressure values to be considered a touch
#define MIN_PRESSURE 100
#define MAX_PRESSURE 1000

// Common colours as hex values
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define BACKGROUND_COLOR BLACK
#define FOREGROUND_COLOR WHITE
#define HIGHLIGHT_COLOR RED

#define SCREEN_ROTATION 3

// Y value and font size of title text
#define TITLE_Y 2
#define TITLE_FONT_SIZE 3

// Horizontal line
#define LINE_Y 30

// Engine start button
#define ENGINE_START_BUTTON_INNER_RADIUS 60
#define ENGINE_START_BUTTON_MIDDLE_RADIUS 65

#define ENGINE_START_BUTTON_INDICATOR_Y -40
#define ENGINE_START_Btton

#define ENGINE_START_BUTTON_OUTER_RADIUS 68
#define ENGINE_START_BUTTON_INDICATOR_WIDTH 40
#define ENGINE_START_BUTTON_INDICATOR_HEIGHT 10
#define ENGINE_START_BUTTON_INDICATOR_ROUNDED_RADIUS 3
#define ENGINE_START_BUTTON_ENGINE_TEXT_SIZE 2
#define ENGINE_START_BUTTON_START_TEXT_SIZE 3
#define ENGINE_START_BUTTON_ENGINE_TEXT_Y -6
#define ENGINE_START_BUTTON_START_TEXT_Y 15

// Home button
#define HOME_BUTTON_OUTER_RADIUS 10
#define HOME_BUTTON_INNER_RADIUS 7
#define HOME_BUTTON_X 15
#define HOME_BUTTON_Y 15

// Back button
#define BACK_BUTTON_WIDTH 20
#define BACK_BUTTON_HEIGHT 20
#define BACK_BUTTON_X 40
#define BACK_BUTTON_Y 5

// Message popups
#define MESSAGE_BOX_PADDING 50
#define MESSAGE_BOX_FONT_SIZE 2

// Check box
#define CHECK_BOX_OUTER_SIZE 36
#define CHECK_BOX_INNER_SIZE 28

// Switch
#define SWITCH_WIDTH 72
#define SWITCH_HEIGHT 36
#define SWITCH_TOGGLE_INSET 4

// Round text buttons on main screen
#define MAIN_SCREEN_BUTTON_INSET 50
#define MAIN_SCREEN_BUTTON_RADIUS 35

// Paddings for settings screen
#define SETTINGS_SCREEN_INSET 10
#define SETTINGS_SCREEN_LABEL_Y_OFFSET 10

// Ball view

#define BALL_VIEW_MAX_STRENGTH 300
#define BALL_VIEW_ROBOT_RADIUS 20
#define BALL_VIEW_BALL_RADIUS 10


// Camera view
#define GOAL_VIEW_ROBOT_RADIUS 10
#define GOAL_VIEW_GOAL_RADIUS 10
#define GOAL_VIEW_MAX_DISTANCE 80

#define ROBOT_POSITION_VIEW_ROBOT_RADIUS 10

#endif
