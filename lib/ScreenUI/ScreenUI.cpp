#include "ScreenUI.h"

View::View(uint16_t x, uint16_t y, uint16_t w, uint16_t h) : x(x), y(y), w(w), h(h) {}

Button::Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h) : View(x, y, w, h) {}

void View::checkDraw() {
    if (needsDrawing) {
        draw();
        needsDrawing = false;
    }
}

void View::setNeedsDraw() {
    needsDrawing = true;
}

Dial::Dial(uint16_t cx, uint16_t cy, uint16_t r, int maxValue) : View(cx - r, cy - r, r * 2, r * 2), cx(cx), cy(cy), r(r), maxValue(maxValue) {}

void Dial::draw() {
    TFT.drawCircle(cx, cy, r, FOREGROUND_COLOR);

    double oldAngleRadians = ((double)min(oldValue, maxValue) / (double)maxValue) * 2*PI - 0.5*PI;
    double angleRadians = ((double)min(value, maxValue) / (double)maxValue) * 2*PI - 0.5*PI;
    TFT.drawLine(cx, cy, cx + r * 0.8 * cos(oldAngleRadians), cy + r * 0.8 * sin(oldAngleRadians), BACKGROUND_COLOR);
    TFT.fillCircle(cx, cy, 10, FOREGROUND_COLOR);
    TFT.drawLine(cx, cy, cx + r * 0.8 * cos(angleRadians), cy + r * 0.8 * sin(angleRadians), HIGHLIGHT_COLOR);

    oldValue = value;
}

void Dial::setValue(int newValue) {
    if (value != newValue) {
        value = newValue;
        setNeedsDraw();
    }
}

int Dial::getValue() {
    return value;
}


void Button::setEnabled(bool isEnabled) {
    if (enabled != isEnabled) {
        enabled = isEnabled;
        setNeedsDraw(true);
    }
}

GoalView::GoalView(uint16_t x, uint16_t y, uint16_t w, uint16_t h) : View(x, y, w, h) {}

void GoalView::draw() {
    int16_t centreX = x + w / 2;
    int16_t centreY = y + h / 2;

    if (oldYellowAngle != 400) {
        int16_t oldYellowX = centreX + (min(w, h) / 2 - GOAL_VIEW_GOAL_RADIUS) * ((double)oldYellowDistance / (double)GOAL_VIEW_MAX_DISTANCE) * cos(degreesToRadians(oldYellowAngle - 90));
        int16_t oldYellowY = centreY + (min(w, h) / 2 - GOAL_VIEW_GOAL_RADIUS) * ((double)oldYellowDistance / (double)GOAL_VIEW_MAX_DISTANCE) * sin(degreesToRadians(oldYellowAngle - 90));
        TFT.fillCircle(oldYellowX, oldYellowY, GOAL_VIEW_GOAL_RADIUS, BACKGROUND_COLOR);
    }

    if (yellowAngle != 400) {
        int16_t yellowX = centreX + (min(w, h) / 2 - GOAL_VIEW_GOAL_RADIUS) * ((double)yellowDistance / (double)GOAL_VIEW_MAX_DISTANCE) * cos(degreesToRadians(yellowAngle - 90));
        int16_t yellowY = centreY + (min(w, h) / 2 - GOAL_VIEW_GOAL_RADIUS) * ((double)yellowDistance / (double)GOAL_VIEW_MAX_DISTANCE) * sin(degreesToRadians(yellowAngle - 90));  
        TFT.fillCircle(yellowX, yellowY, GOAL_VIEW_GOAL_RADIUS, YELLOW);
    }

    if (oldBlueAngle != 400) {
        int16_t oldBlueX = centreX + (min(w, h) / 2 - GOAL_VIEW_GOAL_RADIUS) * ((double)oldBlueDistance / (double)GOAL_VIEW_MAX_DISTANCE) * cos(degreesToRadians(oldBlueAngle - 90));
        int16_t oldBlueY = centreY + (min(w, h) / 2 - GOAL_VIEW_GOAL_RADIUS) * ((double)oldBlueDistance / (double)GOAL_VIEW_MAX_DISTANCE) * sin(degreesToRadians(oldBlueAngle - 90));
        TFT.fillCircle(oldBlueX, oldBlueY, GOAL_VIEW_GOAL_RADIUS, BACKGROUND_COLOR);
    }

    if (blueAngle != 400) {
        int16_t blueX = centreX + (min(w, h) / 2 - GOAL_VIEW_GOAL_RADIUS) * ((double)blueDistance / (double)GOAL_VIEW_MAX_DISTANCE) * cos(degreesToRadians(blueAngle - 90));
        int16_t blueY = centreY + (min(w, h) / 2 - GOAL_VIEW_GOAL_RADIUS) * ((double)blueDistance / (double)GOAL_VIEW_MAX_DISTANCE) * sin(degreesToRadians(blueAngle - 90));
        TFT.fillCircle(blueX, blueY, GOAL_VIEW_GOAL_RADIUS, BLUE);
    }
     
    TFT.fillCircle(centreX, centreY, GOAL_VIEW_ROBOT_RADIUS, FOREGROUND_COLOR);

    oldYellowAngle = yellowAngle;
    oldYellowDistance = yellowDistance;
    oldBlueAngle = blueAngle;
    oldBlueDistance = blueDistance;
}

void GoalView::setGoalData(int ya, int yd, int ba, int bd) {
    if (ya != yellowAngle || yd != yellowDistance || ba != blueAngle || bd != blueDistance)  {
        yellowAngle = ya;
        yellowDistance = yd;
        blueAngle = ba;
        blueDistance = bd;

        setNeedsDraw();
    }
}


bool Button::getEnabled() {
    return enabled;
}

void Button::setNeedsDraw(bool highlightOnly) {
    needsDrawing = true;
    needsHighlightOnly = highlightOnly;
}

bool Button::isTouched(uint16_t tx, uint16_t ty, bool touchDown) {
    bool in = inButton(tx, ty);

    if ((in && touchDown) != highlighted) {
        highlighted = in && touchDown;
        setNeedsDraw(true);
    }

    return in && !touchDown;
}

bool Button::inButton(uint16_t tx, uint16_t ty) {
    return (tx > x) && (tx < x + w) && (ty > y) && (ty < y + h);
}

Label::Label(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *str, uint8_t textSize) : View(x, y, w, h), str(str), textSize(textSize) {}

void Label::draw() {
    TFT.fillRect(x, y, w, h, BACKGROUND_COLOR);
    TFT.setTextColor(FOREGROUND_COLOR);
    TFT.setCursor(x, y);
    TFT.setTextSize(textSize);
    TFT.print(str);
}

void Label::setText(char *newStr) {
    str = newStr;
    setNeedsDraw();
}

IndicatorLabel::IndicatorLabel(uint16_t x, uint16_t y, uint16_t w, uint16_t h, char *str, uint8_t textSize) : Label(x, y, w, h, str, textSize) {}

void IndicatorLabel::draw() {
    TFT.fillRect(x, y, w, h, BACKGROUND_COLOR);
    TFT.setTextColor(FOREGROUND_COLOR);
    TFT.setCursor(x + h + 8, y);
    TFT.setTextSize(textSize);
    TFT.print(str);
    TFT.fillCircle(x + h / 2, y + h / 2, h / 2, enabled ? FOREGROUND_COLOR : BACKGROUND_COLOR);
}

void IndicatorLabel::setEnabled(bool isEnabled) {
    if (enabled != isEnabled) {
        enabled = isEnabled;
        setNeedsDraw();
    }
}

CircleButton::CircleButton(uint16_t cx, uint16_t cy, uint16_t r) : Button(cx - r, cy - r, r * 2, r * 2), cx(cx), cy(cy), r(r) {}

bool CircleButton::inButton(uint16_t tx, uint16_t ty) {
    return distanceBetween(cx, tx, cy, ty) < r;
}

EngineStartButton::EngineStartButton(uint16_t cx, uint16_t cy) : CircleButton(cx, cy, ENGINE_START_BUTTON_OUTER_RADIUS) {}

void EngineStartButton::draw() {
    if (needsHighlightOnly) {
        TFT.fillRoundRect(cx - ENGINE_START_BUTTON_INDICATOR_WIDTH / 2, cy + ENGINE_START_BUTTON_INDICATOR_Y, ENGINE_START_BUTTON_INDICATOR_WIDTH, ENGINE_START_BUTTON_INDICATOR_HEIGHT, ENGINE_START_BUTTON_INDICATOR_ROUNDED_RADIUS, enabled ? GREEN : RED);

        TFT.drawCircle(cx, cy, ENGINE_START_BUTTON_INNER_RADIUS - 3, highlighted ? TFT.color565(150, 150, 150) : TFT.color565(30, 30, 30));
    } else {
        uint16_t widthEngine, heightEngine, widthStart, heightStart;
        int16_t tempX, tempY;

        TFT.fillCircle(cx, cy, ENGINE_START_BUTTON_OUTER_RADIUS, TFT.color565(200, 200, 200));
        TFT.fillCircle(cx, cy, ENGINE_START_BUTTON_MIDDLE_RADIUS, TFT.color565(150, 150, 150));
        TFT.fillCircle(cx, cy, ENGINE_START_BUTTON_INNER_RADIUS, TFT.color565(30, 30, 30));

        TFT.setTextColor(WHITE);

        TFT.setTextSize(ENGINE_START_BUTTON_ENGINE_TEXT_SIZE);
        TFT.getTextBounds("ENGINE", 0, 0, &tempX, &tempY, &widthEngine, &heightEngine);
        TFT.setCursor(cx - widthEngine / 2, cy + ENGINE_START_BUTTON_ENGINE_TEXT_Y);
        TFT.print("ENGINE");
        TFT.setTextSize(ENGINE_START_BUTTON_START_TEXT_SIZE);
        TFT.getTextBounds("START", 0, 0, &tempX, &tempY, &widthStart, &heightStart);
        TFT.setCursor(cx - widthStart / 2, cy + ENGINE_START_BUTTON_START_TEXT_Y);
        TFT.print("START");

        TFT.setTextColor(FOREGROUND_COLOR);
        TFT.setFont();

        TFT.fillRoundRect(cx - ENGINE_START_BUTTON_INDICATOR_WIDTH / 2, cy + ENGINE_START_BUTTON_INDICATOR_Y, ENGINE_START_BUTTON_INDICATOR_WIDTH, ENGINE_START_BUTTON_INDICATOR_HEIGHT, ENGINE_START_BUTTON_INDICATOR_ROUNDED_RADIUS, enabled ? GREEN : RED);

        TFT.drawCircle(cx, cy, ENGINE_START_BUTTON_INNER_RADIUS - 3, highlighted ? TFT.color565(150, 150, 150) : TFT.color565(30, 30, 30));
    }
}

TextButton::TextButton(uint16_t cx, uint16_t cy, uint16_t r, char *str, uint8_t textSize) : CircleButton(cx, cy, r), str(str), textSize(textSize) {
    int16_t tempX, tempY;

    TFT.setTextSize(textSize);
    TFT.getTextBounds(str, 0, 0, &tempX, &tempY, &textWidth, &textHeight);
}

void TextButton::draw() {
    TFT.drawCircle(cx, cy, r, highlighted ? HIGHLIGHT_COLOR : FOREGROUND_COLOR);
    TFT.setCursor(cx - textWidth / 2, cy - textHeight / 2);
    TFT.setTextSize(textSize);
    TFT.setTextColor(FOREGROUND_COLOR);
    TFT.print(str);
}

HomeButton::HomeButton(uint16_t cx, uint16_t cy) : CircleButton(cx, cy, HOME_BUTTON_OUTER_RADIUS * 1.5) {}

void HomeButton::draw() {
    TFT.drawCircle(cx, cy, HOME_BUTTON_OUTER_RADIUS, FOREGROUND_COLOR);
    TFT.fillCircle(cx, cy, HOME_BUTTON_INNER_RADIUS, highlighted ? BACKGROUND_COLOR : FOREGROUND_COLOR);
}

BackButton::BackButton(uint16_t x, uint16_t y) : Button(x, y, BACK_BUTTON_WIDTH, BACK_BUTTON_HEIGHT) {}

void BackButton::draw() {
    TFT.drawLine(x, y + h / 2, x + w, y + h / 2, highlighted ? HIGHLIGHT_COLOR : FOREGROUND_COLOR);
    TFT.drawLine(x, y + h / 2, x + w / 2, y, highlighted ? HIGHLIGHT_COLOR : FOREGROUND_COLOR);
    TFT.drawLine(x, y + h / 2, x + w / 2, y + h, highlighted ? HIGHLIGHT_COLOR : FOREGROUND_COLOR);
}

CheckBox::CheckBox(uint16_t x, uint16_t y) : Button(x, y, CHECK_BOX_OUTER_SIZE, CHECK_BOX_OUTER_SIZE) {}

void CheckBox::draw() {
    TFT.drawRect(x, y, CHECK_BOX_OUTER_SIZE, CHECK_BOX_OUTER_SIZE, highlighted ? HIGHLIGHT_COLOR : FOREGROUND_COLOR);
    TFT.fillRect(x + (CHECK_BOX_OUTER_SIZE - CHECK_BOX_INNER_SIZE) / 2, y + (CHECK_BOX_OUTER_SIZE - CHECK_BOX_INNER_SIZE) / 2, CHECK_BOX_INNER_SIZE, CHECK_BOX_INNER_SIZE, enabled ? FOREGROUND_COLOR : BACKGROUND_COLOR);
}

Switch::Switch(uint16_t x, uint16_t y, uint16_t onColor, char *onChar, uint16_t offColor, char *offChar) : Button(x, y, SWITCH_WIDTH, SWITCH_HEIGHT), onColor(onColor), onChar(onChar), offColor(offColor), offChar(offChar) {}

void Switch::draw() {
    TFT.drawRect(x, y, SWITCH_WIDTH, SWITCH_HEIGHT, highlighted ? HIGHLIGHT_COLOR : FOREGROUND_COLOR);
    TFT.fillRect(enabled ? x + SWITCH_TOGGLE_INSET : x + SWITCH_WIDTH / 2, y + SWITCH_TOGGLE_INSET, SWITCH_WIDTH / 2 - SWITCH_TOGGLE_INSET, SWITCH_HEIGHT - SWITCH_TOGGLE_INSET * 2, enabled ? onColor : offColor);
    TFT.fillRect(!enabled ? x + SWITCH_TOGGLE_INSET : x + SWITCH_WIDTH / 2, y + SWITCH_TOGGLE_INSET, SWITCH_WIDTH / 2 - SWITCH_TOGGLE_INSET, SWITCH_HEIGHT - SWITCH_TOGGLE_INSET * 2, BACKGROUND_COLOR);
    
    uint16_t textWidth, textHeight;
    int16_t textX, textY;

    TFT.setTextSize(2);
    TFT.getTextBounds(enabled ? onChar : offChar, 0, 0, &textX, &textY, &textWidth, &textHeight);

    TFT.setCursor(enabled ? x + SWITCH_TOGGLE_INSET + ((SWITCH_WIDTH / 2 - SWITCH_TOGGLE_INSET) - textWidth) / 2 : x + SWITCH_WIDTH / 2 + ((SWITCH_WIDTH / 2 - SWITCH_TOGGLE_INSET) - textWidth) / 2, y + (SWITCH_HEIGHT - textHeight) / 2);
    TFT.setTextColor(BACKGROUND_COLOR);
    TFT.print(enabled ? onChar : offChar);
}

Terminal::Terminal(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t textSize, uint16_t textColor) : View(x, y, w, h), textSize(textSize), textColor(textColor) {
    needsDrawing = false;
}

void Terminal::clear() {
    TFT.fillRect(x, y, w, h, BACKGROUND_COLOR);
    TFT.setCursor(x, y);
}

size_t Terminal::write(uint8_t c) {
    if (bufferSize == 100) {
        return 0;
    } else {
        bufferSize++;
        charBuffer[tail] = c;
        tail = mod(tail + 1, 100);
    }

    return 1;
}

void Terminal::clearIfOverflow() {
    if (TFT.getCursorY() > y + h - textSize * 8) {
        clear();
    }
}

void Terminal::draw() {
    clear();
}

void Terminal::drawChar(uint8_t c) {
    TFT.setMaxCursor(x + w, y + h);
    TFT.setBaseCursor(x);
    TFT.write(c);
   
    clearIfOverflow();
}

void Terminal::drawFromBuffer() {
    TFT.setTextColor(textColor);
    TFT.setTextSize(textSize);

    while (bufferSize > 0) {
        drawChar(charBuffer[head]);
        bufferSize--;
        head = mod(head + 1, 100);
    }

    TFT.setBaseCursor(0);
    TFT.setMaxCursor(TFT.width(), TFT.height());
}