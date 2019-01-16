#ifndef DEBUG_SETTINGS_H
#define DEBUG_SETTINGS_H

#include <Arduino.h>
#include <Define.h>
#include <EEPROM.h>

// Settings controlled on the touchscreen
class DebugSettings {
public:
    DebugSettings();
    DebugSettings(uint16_t numberValue);

    uint16_t numberValue();
    void setNumberValue(uint16_t numberValue);

    void readEEPROM();
    void writeEEPROM();

    bool engineStarted; // Motors on or off
    bool IMUNeedsResetting; // IMU reset and calibration
    bool playModeSwitching; // Robot will switch play mode or not
    bool lightSensorsNeedResetting; // Light sensor reset and calibration
    bool defaultPlayModeIsAttack; // Default play mode
    bool goalIsYellow; // Goal colour
    bool gameMode; // Game mode (no debug)
};

#endif // DEBUG_SETTINGS_H
