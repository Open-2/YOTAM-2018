// UI elements for the touchscreen

#ifndef SCREEN_UI_H
#define SCREEN_UI_H

#include <Arduino.h>
#include <Adafruit_ILI9341_8bit.h>
#include <TouchScreen.h>
#include <Define.h>
#include <Common.h>


// Base view
class View {
public:
    View() {}
    View(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

    virtual void draw() {}
    void checkDraw();
    virtual void setNeedsDraw();

    uint16_t x, y, w, h;

protected:
    bool needsDrawing = true; // Only redraw to the screen if this is true
};

// Dial, shows a number with a needle
class Dial : public View {
public:
    Dial() {}
    Dial(uint16_t cx, uint16_t cy, uint16_t r, int maxValue);

    void draw();
    void setValue(int newValue);
    int getValue();

protected:
    int maxValue;
    int value;
    int oldValue;

    uint16_t cx, cy, r;
};


// Position of the two goals on the camera
class GoalView : public View {
public:
    GoalView() {}
    GoalView(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

    void draw();
    void setGoalData(int ya, int yd, int ba, int bd);

protected:
    int yellowAngle, oldYellowAngle;
    int yellowDistance, oldYellowDistance;
    int blueAngle, oldBlueAngle;
    int blueDistance, oldBlueDistance;
};


// Generic button
class Button : public View {
public:
    Button() {}
    Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

    void setNeedsDraw(bool highlightOnly = false);

    bool isTouched(uint16_t tx, uint16_t ty, bool touchDown);
    virtual bool inButton(uint16_t tx, uint16_t ty);

    void setEnabled(bool isEnabled);
    bool getEnabled();

protected:
    bool highlighted = false;
    bool enabled = false;
    bool needsHighlightOnly = false;
};

// Text label
class Label : public View {
public:
    Label() {}
    Label(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *str, uint8_t textSize);

    void draw();
    void setText(char *newStr);

protected:
    char *str;
    uint8_t textSize;
};

// Label with an on/off dot
class IndicatorLabel : public Label {
public:
    IndicatorLabel() {}
    IndicatorLabel(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *str, uint8_t textSize);

    void draw();
    void setEnabled(bool isEnabled);
protected:
    bool enabled = false;
};

// Generic button with a circle bounds
class CircleButton : public Button {
public:
    CircleButton() {}
    CircleButton(uint16_t cx, uint16_t cy, uint16_t r);

    bool inButton(uint16_t tx, uint16_t ty);

protected:
    uint16_t cx, cy, r;
};

// ENGINE START
class EngineStartButton : public CircleButton {
public:
    EngineStartButton() {}
    EngineStartButton(uint16_t cx, uint16_t cy);

    void draw();
};

// Home button
class HomeButton : public CircleButton {
public:
    HomeButton() {}
    HomeButton(uint16_t cx, uint16_t cy);

    void draw();
};

// Back button
class BackButton : public Button {
public:
    BackButton() {}
    BackButton(uint16_t x, uint16_t y);

    void draw();
};

// Circle button with text
class TextButton : public CircleButton {
public:
    TextButton() {}
    TextButton(uint16_t cx, uint16_t cy, uint16_t r, char *str, uint8_t textSize);

    void draw();

protected:
    char *str;
    uint8_t textSize;

    uint16_t textWidth, textHeight;
};

// On/off checkbox
class CheckBox : public Button {
public:
    CheckBox() {}
    CheckBox(uint16_t x, uint16_t y);

    void draw();
};

// On/off slide switch
class Switch : public Button {
public:
    Switch() {}
    Switch(uint16_t x, uint16_t y, uint16_t onColor, char *onChar, uint16_t offColor, char *offChar);

    void draw();

protected:
    uint16_t onColor;
    char *onChar;
    uint16_t offColor;
    char *offChar;
};

// Serial terminal
class Terminal : public View, public Print {
public:
    Terminal() {}
    Terminal(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t textSize, uint16_t textColor);

    void draw();
    void drawChar(uint8_t c);
    void drawFromBuffer();
    void clear();

    size_t write(uint8_t c);

protected:
    uint8_t charBuffer[100];

    uint8_t head, tail, bufferSize = 0;

    void clearIfOverflow();

    uint16_t textColor;
    uint8_t textSize;
};

#endif // BUTTON_H
