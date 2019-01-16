#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_ILI9341_8bit.h>
#include <TouchScreen.h>
#include <ScreenUI.h>
#include <Define.h>
#include <DebugSettings.h>

// Enum for the type of screens
enum ScreenType: uint8_t {
    mainScreenType, // Main screen
    debugScreenType, // Debug
    settingScreenType, // Settings
    ballDebugScreenType, // Ball debug
    cameraDebugScreenType, // Camera debug
    terminalDebugScreenType // Terminal
};

// Touchscreen controller. Is a subclass of print to enable printing to the terminal
class Screen : public Print {
public:
    Screen() {}

    void init();

    void clearAll();
    void clear();
    void changeScreen(ScreenType newType);
    void redrawScreen();
    
    void checkTouch();
    void updateBatteryMeter();
    void setBluetoothConnected(bool connected);
    void drawBluetoothIcon(bool connected);
    void update();

    void displayMessage(char *message, bool clearable = false);
    void clearMessage();

    size_t write(uint8_t c);

    DebugSettings settings; // Settings

    // Debug Variables

    int heading = 0;
    int leftRPM = 0;
    int rightRPM = 0;
    int backLeftRPM = 0;
    int backRightRPM = 0;
    int yellowAngle = 0, yellowDistance = 0, blueAngle = 0, blueDistance = 0;
    uint16_t lsFirst = 0, lsSecond = 0, lsThird = 0, lsFourth = 0;
    long lsData = 0;
    
private:
    TouchScreen ts = TouchScreen(SCREEN_XP, SCREEN_YP, SCREEN_XM, SCREEN_YM, TS_RESISTANCE); // Resistive touch controller object
    TSPoint lastTouchPoint; // Touch point
    bool lastIsTouching; // If the screen was previously touched

    bool displayingMessage = false; // Showing a popup message
    bool messageClearable = false; // If the popup message is clearable, for example by pressing the home button

    ScreenType screenType = ScreenType::mainScreenType; // Type of screen being shown
    ScreenType lastScreenType = ScreenType::mainScreenType; // Last shown screen for back button

    // UI Elements //

    HomeButton homeButton;
    BackButton backButton;

    // Main Screen

    EngineStartButton engineStartButton;

    TextButton debugButton;
    TextButton settingsButton;
    TextButton IMUResetButton;
    TextButton lightSensorsResetButton;

    TextButton resetAllButton;

    // Settings Screen

    Label playModeSwitchingLabel;
    CheckBox playModeSwitchingCheckBox;

    Label defaultPlayModeLabel;
    Switch defaultPlayModeSwitch;

    Label goalIsYellowLabel;
    Switch goalIsYellowSwitch;

    Label gameModeLabel;
    CheckBox gameModeCheckBox;

    // Debug Screen

    TextButton imuDebugButton;
    TextButton motorsDebugButton;
    TextButton ballDebugButton;
    TextButton lightSensorsDebugButton;
    TextButton cameraDebugButton;
    TextButton ledsDebugButton;
    TextButton terminalDebugButton;

    TextButton otherIMUDebugButton;
    TextButton otherBallDebugButton;

    IndicatorLabel otherBallIsOutLabel;
    IndicatorLabel otherIsOnFieldLabel;

    // Camera Debug Screen
    GoalView goalView;

    // Terminal Debug Screen
    Terminal terminal;
};

#endif // SCREEN_H
