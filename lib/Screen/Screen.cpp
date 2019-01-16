#include "Screen.h"

void Screen::init()
{
    // Load settings from EEPROM
    settings.readEEPROM();

    // Init the display controller
    TFT.begin();

    // Fill the background colour
    TFT.setRotation(SCREEN_ROTATION);
    TFT.fillScreen(BACKGROUND_COLOR);

    TFT.setTextSize(TITLE_FONT_SIZE);
    TFT.setTextColor(FOREGROUND_COLOR);

    TFT.setMaxCursor(TFT.width(), TFT.height());

    uint16_t width, height;
    int16_t tempX, tempY;

    // Draw title text
    TFT.getTextBounds("B-TEC", 0, 0, &tempX, &tempY, &width, &height);

    TFT.setCursor(TFT.width() / 2 - width / 2, TITLE_Y);
    TFT.print("B-TEC");

    // Battery meter setup
    TFT.drawRoundRect(TFT.width() - BATTERY_METER_RIGHT_X, BATTERY_METER_Y, BATTERY_METER_WIDTH, BATTERY_METER_HEIGHT, BATTERY_METER_ROUNDED_RADIUS, FOREGROUND_COLOR);
    TFT.fillRect(TFT.width() - BATTERY_METER_RIGHT_X + BATTERY_METER_WIDTH, BATTERY_METER_Y + (BATTERY_METER_HEIGHT - BATTERY_METER_END_HEIGHT) / 2, BATTERY_METER_END_WIDTH - 1, BATTERY_METER_END_HEIGHT, FOREGROUND_COLOR);
    TFT.fillRoundRect(TFT.width() - BATTERY_METER_RIGHT_X + BATTERY_METER_WIDTH, BATTERY_METER_Y + (BATTERY_METER_HEIGHT - BATTERY_METER_END_HEIGHT) / 2, BATTERY_METER_END_WIDTH, BATTERY_METER_END_HEIGHT, BATTERY_METER_END_ROUNDED_RADIUS, FOREGROUND_COLOR);

    // Horizontal line
    TFT.drawLine(0, LINE_Y, TFT.width(), LINE_Y, FOREGROUND_COLOR);

    // Home and back buttons
    homeButton = HomeButton(HOME_BUTTON_X, HOME_BUTTON_Y);
    backButton = BackButton(BACK_BUTTON_X, BACK_BUTTON_Y);

    // Main Screen

    engineStartButton = EngineStartButton(TFT.width() / 2, LINE_Y + (TFT.height() - LINE_Y) / 2);
    debugButton = TextButton(TFT.width() - MAIN_SCREEN_BUTTON_INSET, LINE_Y + MAIN_SCREEN_BUTTON_INSET, MAIN_SCREEN_BUTTON_RADIUS, "Debug", 1);
    settingsButton = TextButton(TFT.width() - MAIN_SCREEN_BUTTON_INSET, TFT.height() - MAIN_SCREEN_BUTTON_INSET, MAIN_SCREEN_BUTTON_RADIUS, "Settings", 1);
    IMUResetButton = TextButton(MAIN_SCREEN_BUTTON_INSET, TFT.height() - MAIN_SCREEN_BUTTON_INSET, MAIN_SCREEN_BUTTON_RADIUS, "Reset IMU", 1);
    lightSensorsResetButton = TextButton(MAIN_SCREEN_BUTTON_INSET, LINE_Y + MAIN_SCREEN_BUTTON_INSET, MAIN_SCREEN_BUTTON_RADIUS, "Reset LS", 1);

    resetAllButton = TextButton(TFT.width() - MAIN_SCREEN_BUTTON_INSET, LINE_Y + MAIN_SCREEN_BUTTON_INSET, MAIN_SCREEN_BUTTON_RADIUS, "Reset All", 1);

    // Debug Screen

    imuDebugButton = TextButton(80, LINE_Y + 40, 30, "IMU", 1);
    motorsDebugButton = TextButton(160, LINE_Y + 40, 30, "Motors", 1);
    ballDebugButton = TextButton(40, LINE_Y + (TFT.height() - LINE_Y) / 2, 30, "Ball", 1);
    lightSensorsDebugButton = TextButton(120, LINE_Y + (TFT.height() - LINE_Y) / 2, 30, "Light", 1);
    cameraDebugButton = TextButton(200, LINE_Y + (TFT.height() - LINE_Y) / 2, 30, "Camera", 1);
    ledsDebugButton = TextButton(80, TFT.height() - 40, 30, "LEDs", 1);
    terminalDebugButton = TextButton(160, TFT.height() - 40, 30, "Terminal", 1);


    otherIMUDebugButton = TextButton(60, LINE_Y + 60, 35, "IMU", 1);
    otherBallDebugButton = TextButton(60, TFT.height() - 60, 35, "Ball", 1);

    otherIsOnFieldLabel = IndicatorLabel(150, LINE_Y + 30 + SWITCH_HEIGHT, 200, 14, "Is on field", 2);
    otherBallIsOutLabel = IndicatorLabel(150, LINE_Y + 30 + SWITCH_HEIGHT + 30, 200, 14, "Ball is out", 2);

    // Settings Screen

    playModeSwitchingLabel = Label(SETTINGS_SCREEN_INSET, LINE_Y + SETTINGS_SCREEN_INSET + SETTINGS_SCREEN_LABEL_Y_OFFSET, 200, 20, "Play mode switching", 2);
    playModeSwitchingCheckBox = CheckBox(TFT.width() - CHECK_BOX_OUTER_SIZE - SETTINGS_SCREEN_INSET, LINE_Y + SETTINGS_SCREEN_INSET);

    defaultPlayModeLabel = Label(SETTINGS_SCREEN_INSET, LINE_Y + SETTINGS_SCREEN_INSET * 2 + CHECK_BOX_OUTER_SIZE + SETTINGS_SCREEN_LABEL_Y_OFFSET, 200, 20, "Default play mode", 2);
    defaultPlayModeSwitch = Switch(TFT.width() - SWITCH_WIDTH - SETTINGS_SCREEN_INSET, LINE_Y + SETTINGS_SCREEN_INSET * 2 + CHECK_BOX_OUTER_SIZE, FOREGROUND_COLOR, "A", FOREGROUND_COLOR, "D");

    goalIsYellowLabel = Label(SETTINGS_SCREEN_INSET, LINE_Y + SETTINGS_SCREEN_INSET * 3 + CHECK_BOX_OUTER_SIZE * 2 + SETTINGS_SCREEN_LABEL_Y_OFFSET, 200, 20, "Goal color", 2);
    goalIsYellowSwitch = Switch(TFT.width() - SWITCH_WIDTH - SETTINGS_SCREEN_INSET, LINE_Y + SETTINGS_SCREEN_INSET * 3 + CHECK_BOX_OUTER_SIZE * 2, YELLOW, "", BLUE, "");

    gameModeLabel = Label(SETTINGS_SCREEN_INSET, LINE_Y + SETTINGS_SCREEN_INSET * 4 + CHECK_BOX_OUTER_SIZE * 3 + SETTINGS_SCREEN_LABEL_Y_OFFSET, 200, 20, "Game mode", 2);
    gameModeCheckBox = CheckBox(TFT.width() - CHECK_BOX_OUTER_SIZE - SETTINGS_SCREEN_INSET, LINE_Y + SETTINGS_SCREEN_INSET * 4 + CHECK_BOX_OUTER_SIZE * 3);


    // Ball Debug Screen

    ballView = BallView(5, LINE_Y + 5, TFT.width() - 10, TFT.height() - LINE_Y - 10);

    // Camera Debug Screen

    goalView = GoalView(5, LINE_Y + 5, (TFT.width() - 10) / 2, TFT.height() - LINE_Y - 10);
    robotPositionView = RobotPositionView(TFT.width() / 2, LINE_Y + 5, (TFT.width() - 10) / 2, TFT.height() - LINE_Y - 10);

    // Terminal Debug Screen

    terminal = Terminal(5, LINE_Y + 5, TFT.width() - 10, TFT.height() - LINE_Y - 10, 1, FOREGROUND_COLOR);
}

void Screen::clearAll()
{
    // Clear the whole screen
    TFT.fillScreen(BACKGROUND_COLOR);
}

void Screen::clear()
{
    // Only clear the screen from the horizontal line down (leave title bar)
    TFT.fillRect(0, LINE_Y + 1, TFT.width(), TFT.height() - LINE_Y, BACKGROUND_COLOR);
}

void Screen::checkTouch()
{
    // Compute touches

    TSPoint p = ts.getPoint();

    // Check if the pressure is valid for a touch
    bool isTouching = p.z > MIN_PRESSURE && p.z < MAX_PRESSURE && p.x > TS_MINX && p.y < TS_MAXX && p.y > TS_MINY && p.y < TS_MAXY;

    // If the screen is or was being pressed
    if (isTouching || lastIsTouching)
    {
        // Convert point to x and y
        TSPoint touchPoint = p;
        touchPoint.x = map(p.y, TS_MAXY, TS_MINY, 0, TFT.width());
        touchPoint.y = map(p.x, TS_MINX, TS_MAXX, 0, TFT.height());

        // Use current touch point, or last if the touch just ended
        TSPoint currentTouchPoint = isTouching ? touchPoint : lastTouchPoint;
        lastTouchPoint = touchPoint;

        // If there is no popup message, check each button on the current screen
        if (!displayingMessage)
        {
            switch (screenType)
            {
            case ScreenType::mainScreenType:
                if (engineStartButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                {
                    settings.engineStarted = !settings.engineStarted;
                }

                if (debugButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching) && !settings.gameMode)
                {
                    changeScreen(ScreenType::debugScreenType);
                }

                if (settingsButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                {
                    changeScreen(ScreenType::settingScreenType);
                }

                if (IMUResetButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                {
                    settings.IMUNeedsResetting = true;
                    settings.engineStarted = false;
                    displayMessage("Resetting IMU...");
                }

                if (lightSensorsResetButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                {
                    settings.lightSensorsNeedResetting = true;
                    settings.engineStarted = false;
                    displayMessage("Resetting LS...");
                }

                if (resetAllButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching) && settings.gameMode)
                {
                    settings.IMUNeedsResetting = true;
                    settings.lightSensorsNeedResetting = true;
                    settings.engineStarted = false;
                    displayMessage("Resetting All...");
                }

                break;

            case ScreenType::debugScreenType:
                

                    if (ballDebugButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                    {
                        changeScreen(ScreenType::ballDebugScreenType);
                    }

                    if (cameraDebugButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                    {
                        changeScreen(ScreenType::cameraDebugScreenType);
                    }



                    if (terminalDebugButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                    {
                        changeScreen(ScreenType::terminalDebugScreenType);
                    }
                

                break;

            case ScreenType::settingScreenType:
                if (playModeSwitchingCheckBox.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                {
                    settings.playModeSwitching = !settings.playModeSwitching;
                    settings.writeEEPROM();
                }

                if (defaultPlayModeSwitch.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                {
                    settings.defaultPlayModeIsAttack = !settings.defaultPlayModeIsAttack;
                    settings.writeEEPROM();
                }

                if (goalIsYellowSwitch.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                {
                    settings.goalIsYellow = !settings.goalIsYellow;
                    settings.writeEEPROM();
                }

                if (gameModeCheckBox.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
                {
                    settings.gameMode = !settings.gameMode;
                    settings.writeEEPROM();
                }

                break;
            }
        }

        // If there is a popup, this method will only be called if the message is clearable, in which case check the home and back buttons

        if (homeButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
        {
            changeScreen(ScreenType::mainScreenType);
        }

        if (backButton.isTouched(currentTouchPoint.x, currentTouchPoint.y, isTouching))
        {
            changeScreen(lastScreenType);
        }

    }

    lastIsTouching = isTouching;
}

void Screen::update()
{
    // Update the screen

    if (!displayingMessage)
    {
        // Update the UI elements on the current screen if there is no popup message

        switch (screenType)
        {
        case ScreenType::mainScreenType:
            if (settings.gameMode)
            {
                resetAllButton.checkDraw();
            }
            else
            {
                debugButton.checkDraw();
            }

            engineStartButton.setEnabled(settings.engineStarted);
            engineStartButton.checkDraw();
            settingsButton.checkDraw();
            IMUResetButton.checkDraw();
            lightSensorsResetButton.checkDraw();

            break;

        case ScreenType::debugScreenType:
            {
                imuDebugButton.checkDraw();
                motorsDebugButton.checkDraw();
                ballDebugButton.checkDraw();
                lightSensorsDebugButton.checkDraw();
                cameraDebugButton.checkDraw();
                ledsDebugButton.checkDraw();
                terminalDebugButton.checkDraw();
            }

            break;

        case ScreenType::settingScreenType:
            playModeSwitchingCheckBox.setEnabled(settings.playModeSwitching);
            defaultPlayModeSwitch.setEnabled(settings.defaultPlayModeIsAttack);
            goalIsYellowSwitch.setEnabled(settings.goalIsYellow);
            gameModeCheckBox.setEnabled(settings.gameMode);

            playModeSwitchingLabel.checkDraw();
            playModeSwitchingCheckBox.checkDraw();

            defaultPlayModeLabel.checkDraw();
            defaultPlayModeSwitch.checkDraw();

            goalIsYellowLabel.checkDraw();
            goalIsYellowSwitch.checkDraw();

            gameModeLabel.checkDraw();
            gameModeCheckBox.checkDraw();

            break;

        case ScreenType::ballDebugScreenType:
            ballView.checkDraw();

            break;

        case ScreenType::cameraDebugScreenType:
            goalView.setGoalData(yellowAngle, yellowDistance, blueAngle, blueDistance);
            goalView.checkDraw();

            robotPositionView.setRobotPositionData(robotPosition);

            break;

        case ScreenType::terminalDebugScreenType:
            terminal.drawFromBuffer();

            break;

        default:
            break;
        }
    }

    if (!displayingMessage || messageClearable)
    {
        // If the message is clearble, update the home and back buttons

        homeButton.checkDraw();
        backButton.checkDraw();

        

        checkTouch();
    }

}

void Screen::redrawScreen()
{
    // Redraw the screen when changed. Redraw the relevant UI elements

    clear();
    displayingMessage = false;

    switch (screenType)
    {
    case ScreenType::mainScreenType:
        if (settings.gameMode)
        {
            resetAllButton.setNeedsDraw();
        }
        else
        {
            debugButton.setNeedsDraw();
        }

        engineStartButton.setNeedsDraw();
        settingsButton.setNeedsDraw();

        break;

    case ScreenType::debugScreenType:
        if (settings.gameMode)
        {
            displayMessage("Game mode - no debug", true);
        }
        else
        {
        
            
            imuDebugButton.setNeedsDraw();
            motorsDebugButton.setNeedsDraw();
            ballDebugButton.setNeedsDraw();
            lightSensorsDebugButton.setNeedsDraw();
            cameraDebugButton.setNeedsDraw();
            ledsDebugButton.setNeedsDraw();
            terminalDebugButton.setNeedsDraw();
            

        }

        break;

    case ScreenType::settingScreenType:
        playModeSwitchingLabel.setNeedsDraw();
        playModeSwitchingCheckBox.setNeedsDraw();

        defaultPlayModeLabel.setNeedsDraw();
        defaultPlayModeSwitch.setNeedsDraw();

        goalIsYellowLabel.setNeedsDraw();
        goalIsYellowSwitch.setNeedsDraw();

        gameModeLabel.setNeedsDraw();
        gameModeCheckBox.setNeedsDraw();

        break;


    case ScreenType::ballDebugScreenType:
        ballView.setNeedsDraw();

        break;

    case ScreenType::cameraDebugScreenType:
        goalView.setNeedsDraw();

        break;

    case ScreenType::terminalDebugScreenType:
        terminal.setNeedsDraw();

        break;

    default:
        break;
    }
}

void Screen::changeScreen(ScreenType newType)
{
    // Change the screen if the type is different

    if (screenType != newType)
    {
        lastScreenType = screenType;
        screenType = newType;

        redrawScreen();
    }
}


void Screen::displayMessage(char *message, bool clearable)
{
    // Display a popup message

    messageClearable = clearable;
    displayingMessage = true;

    TFT.setTextSize(MESSAGE_BOX_FONT_SIZE);

    uint16_t width, height;
    int16_t tempX, tempY;

    TFT.getTextBounds(message, 0, 0, &tempX, &tempY, &width, &height);

    TFT.setCursor(TFT.width() / 2 - width / 2, TFT.height() / 2 - height / 2);

    TFT.fillRect(TFT.width() / 2 - (width + MESSAGE_BOX_PADDING) / 2, TFT.height() / 2 - (height + MESSAGE_BOX_PADDING) / 2, width + MESSAGE_BOX_PADDING, height + MESSAGE_BOX_PADDING, BACKGROUND_COLOR);
    TFT.drawRect(TFT.width() / 2 - (width + MESSAGE_BOX_PADDING) / 2, TFT.height() / 2 - (height + MESSAGE_BOX_PADDING) / 2, width + MESSAGE_BOX_PADDING, height + MESSAGE_BOX_PADDING, FOREGROUND_COLOR);

    TFT.setTextColor(FOREGROUND_COLOR);
    TFT.print(message);
}

void Screen::clearMessage()
{
    // Clear the screen if there is a popup message
    if (displayingMessage)
    {
        redrawScreen();
    }
}

size_t Screen::write(uint8_t c)
{
    // Write function for print class. Pass onto terminal object if this is the terminal screen
    if (screenType == ScreenType::terminalDebugScreenType)
    {
        terminal.write(c);
    }

    return 1;
}



