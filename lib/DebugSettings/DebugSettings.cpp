#include "DebugSettings.h"

DebugSettings::DebugSettings() {
    engineStarted = false;
    IMUNeedsResetting = false;
    playModeSwitching = true;
    lightSensorsNeedResetting = false;
    defaultPlayModeIsAttack = true;
    goalIsYellow = true;
    gameMode = false;
}

DebugSettings::DebugSettings(uint16_t numberValue) {
    setNumberValue(numberValue);
}

void DebugSettings::setNumberValue(uint16_t numberValue) {
    // Unpack bools from a uint16_t

    engineStarted = numberValue & 0x1;
    IMUNeedsResetting = (numberValue >> 1) & 0x1;
    playModeSwitching = (numberValue >> 2) & 0x1;
    lightSensorsNeedResetting = (numberValue >> 3) & 0x1;
    defaultPlayModeIsAttack = (numberValue >> 4) & 0x1;
    goalIsYellow = (numberValue >> 5) & 0x1;
    gameMode = (numberValue >> 6) & 0x1;
}

uint16_t DebugSettings::numberValue() {
    // Convert bools to a uint16_t
    return engineStarted | (IMUNeedsResetting << 1) | (playModeSwitching << 2) | (lightSensorsNeedResetting << 3) | (defaultPlayModeIsAttack << 4) | (goalIsYellow << 5) | (gameMode << 6);
}

void DebugSettings::writeEEPROM() {
    // Save to EEPROM
    uint8_t number = playModeSwitching | (defaultPlayModeIsAttack << 1) | (goalIsYellow << 2) | (gameMode << 3);
    EEPROM.write(DEBUG_SETTINGS_EEPROM_ADDRESS, number);
}

void DebugSettings::readEEPROM() {
    // Read from EEPROM
    uint8_t number = EEPROM.read(DEBUG_SETTINGS_EEPROM_ADDRESS);
    playModeSwitching = number & 0x1;
    defaultPlayModeIsAttack = (number >> 1) & 0x1;
    goalIsYellow = (number >> 2) & 0x1;
    gameMode = (number >> 3) & 0x1;
}

