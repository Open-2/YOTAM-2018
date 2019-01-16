#include "Adafruit_ILI9341_8bit.h"

void RD_STROBE() {
    RD_ACTIVE;
    RD_IDLE;
}

void WR_STROBE() {
    WR_ACTIVE;
    WR_IDLE;
}

void swap(int16_t a, int16_t b) {
    int16_t t = a;
    a = b;
    b = t;
}

void write8special(uint8_t c) {
    digitalWriteFast(TFT_WR, LOW);
    digitalWriteFast(D0, c & 0x1);
    digitalWriteFast(D1, c & (0x1 << 1));
    digitalWriteFast(D2, c & (0x1 << 2));
    digitalWriteFast(D3, c & (0x1 << 3));
    digitalWriteFast(D4, c & (0x1 << 4));
    digitalWriteFast(D5, c & (0x1 << 5));
    digitalWriteFast(D6, c & (0x1 << 6));
    digitalWriteFast(D7, c & (0x1 << 7));
    digitalWriteFast(TFT_WR, HIGH);

    // Wait 10ns
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
}

// Constructor when using 8080 mode of control.
Adafruit_ILI9341_8bit::Adafruit_ILI9341_8bit(void): Adafruit_GFX(ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT) {
    pinMode(TFT_RD, OUTPUT);
    pinMode(TFT_WR, OUTPUT);
    pinMode(TFT_RS, OUTPUT);
    pinMode(TFT_CS, OUTPUT);

    CS_IDLE;

    // Set all control bits to HIGH (idle)
    CD_DATA;

    // Signals are ACTIVE LOW
    WR_IDLE;
    RD_IDLE;

    // Set up 8 bit parallel port to write mode.
    setWriteDataBus();
}

void Adafruit_ILI9341_8bit::setWriteDataBus(void) {
    // Set the pins to output mode
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
}

void Adafruit_ILI9341_8bit::setReadDataBus(void) {
    // Set the pins to input mode
    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);
    pinMode(D4, INPUT);
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D7, INPUT);
}

void Adafruit_ILI9341_8bit::write8(uint8_t c) {
    CS_ACTIVE;
    digitalWriteFast(TFT_WR, LOW);
    digitalWriteFast(D0, c & 0x1);
    digitalWriteFast(D1, c & (0x1 << 1));
    digitalWriteFast(D2, c & (0x1 << 2));
    digitalWriteFast(D3, c & (0x1 << 3));
    digitalWriteFast(D4, c & (0x1 << 4));
    digitalWriteFast(D5, c & (0x1 << 5));
    digitalWriteFast(D6, c & (0x1 << 6));
    digitalWriteFast(D7, c & (0x1 << 7));
    digitalWriteFast(TFT_WR, HIGH);
    digitalWriteFast(TFT_WR, HIGH);

    // Wait 10ns
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");

    CS_IDLE;
}

void Adafruit_ILI9341_8bit::writecommand(uint8_t c) {
    CD_COMMAND;
    write8(c);
}

void Adafruit_ILI9341_8bit::writedata(uint8_t c) {
    CD_DATA;
    write8(c);
}

void Adafruit_ILI9341_8bit::begin(void) {
    writecommand(0xEF);
    writedata(0x03);
    writedata(0x80);
    writedata(0x02);
    writecommand(0xCF);
    writedata(0x00);
    writedata(0XC1);
    writedata(0X30);
    writecommand(0xED);
    writedata(0x64);
    writedata(0x03);
    writedata(0X12);
    writedata(0X81);
    writecommand(0xE8);
    writedata(0x85);
    writedata(0x00);
    writedata(0x78);
    writecommand(0xCB);
    writedata(0x39);
    writedata(0x2C);
    writedata(0x00);
    writedata(0x34);
    writedata(0x02);
    writecommand(0xF7);
    writedata(0x20);
    writecommand(0xEA);
    writedata(0x00);
    writedata(0x00);
    writecommand(ILI9341_PWCTR1);
    writedata(0x23);
    writecommand(ILI9341_PWCTR2);
    writedata(0x10);
    writecommand(ILI9341_VMCTR1);
    writedata(0x3e);
    writedata(0x28);
    writecommand(ILI9341_VMCTR2);
    writedata(0x86);
    writecommand(ILI9341_MADCTL);
    writedata(0x48);
    writecommand(ILI9341_PIXFMT);
    writedata(0x55);
    writecommand(ILI9341_FRMCTR1);
    writedata(0x00);
    writedata(0x18);
    writecommand(ILI9341_DFUNCTR);
    writedata(0x08);
    writedata(0x82);
    writedata(0x27);
    writecommand(0xF2);
    writedata(0x00);
    writecommand(ILI9341_GAMMASET);
    writedata(0x01);
    writecommand(ILI9341_GMCTRP1);
    writedata(0x0F);
    writedata(0x31);
    writedata(0x2B);
    writedata(0x0C);
    writedata(0x0E);
    writedata(0x08);
    writedata(0x4E);
    writedata(0xF1);
    writedata(0x37);
    writedata(0x07);
    writedata(0x10);
    writedata(0x03);
    writedata(0x0E);
    writedata(0x09);
    writedata(0x00);
    writecommand(ILI9341_GMCTRN1);
    writedata(0x00);
    writedata(0x0E);
    writedata(0x14);
    writedata(0x03);
    writedata(0x11);
    writedata(0x07);
    writedata(0x31);
    writedata(0xC1);
    writedata(0x48);
    writedata(0x08);
    writedata(0x0F);
    writedata(0x0C);
    writedata(0x31);
    writedata(0x36);
    writedata(0x0F);
    writecommand(ILI9341_INVOFF);
    delay(120);
    writecommand(ILI9341_SLPOUT);
    delay(120);
    writecommand(ILI9341_DISPON);
}

void Adafruit_ILI9341_8bit::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    CS_ACTIVE;
    CD_COMMAND;
    write8special(ILI9341_CASET);
    CD_DATA;
    write8special(x0 >> 8);
    write8special(x0 & 0xFF);
    write8special(x1 >> 8);
    write8special(x1 & 0xFF);
    CD_COMMAND;
    write8special(ILI9341_PASET);
    CD_DATA;
    write8special(y0 >> 8);
    write8special(y0);
    write8special(y1 >> 8);
    write8special(y1);
    CD_COMMAND;
    write8special(ILI9341_RAMWR);
}

void Adafruit_ILI9341_8bit::pushColor(uint16_t color) {
    writedata(color >> 8);
    writedata(color);
}

void Adafruit_ILI9341_8bit::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;
    setAddrWindow(x, y, x + 1, y + 1);
    CD_DATA;
    write8special(color >> 8);
    write8special(color);
    CS_IDLE;
}

void Adafruit_ILI9341_8bit::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    // Rudimentary clipping
    if ((x >= _width) || (y >= _height || h < 1)) return;
    if ((y + h - 1) >= _height)    h = _height - y;
    if (h < 2 ) {
        drawPixel(x, y, color);
        return;
    }

    setAddrWindow(x, y, x, y + h - 1);
    CD_DATA;
    uint8_t hi = color >> 8, lo = color;
    while (h--) {
        write8special(hi);
        write8special(lo);
    }

    CS_IDLE;
}

void Adafruit_ILI9341_8bit::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    // Rudimentary clipping
    if ((x >= _width) || (y >= _height || w < 1)) return;
    if ((x + w - 1) >= _width)  w = _width - x;
    if (w < 2 ) {
        drawPixel(x, y, color);
        return;
    }

    setAddrWindow(x, y, x + w - 1, y);
    CD_DATA;
    uint8_t hi = color >> 8, lo = color;
    while (w--) {
        write8special(hi);
        write8special(lo);
    }

    CS_IDLE;
}

void Adafruit_ILI9341_8bit::fillScreen(uint16_t color) {
    fillRect(0, 0,  _width, _height, color);
}

void Adafruit_ILI9341_8bit::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    // Rudimentary clipping (drawChar w/big text requires this)
    if ((x >= _width) || (y >= _height || h < 1 || w < 1)) return;
    if ((x + w - 1) >= _width)  w = _width  - x;
    if ((y + h - 1) >= _height) h = _height - y;
    if (w == 1 && h == 1) {
        drawPixel(x, y, color);
        return;
    }

    setAddrWindow(x, y, x + w - 1, y + h - 1);
    CD_DATA;
    uint8_t hi = color >> 8, lo = color;

    for(y=h; y>0; y--) {
        for(x=w; x>0; x--) {
            write8special(hi);
            write8special(lo);
        }

    }

    CS_IDLE;
}

// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t Adafruit_ILI9341_8bit::color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

void Adafruit_ILI9341_8bit::setRotation(uint8_t m) {
    writecommand(ILI9341_MADCTL);
    rotation = m % 4;

    switch (rotation) {
        case 0:
        writedata(MADCTL_MX | MADCTL_BGR);
        _width  = ILI9341_TFTWIDTH;
        _height = ILI9341_TFTHEIGHT;
        break;

        case 1:
        writedata(MADCTL_MV | MADCTL_BGR);
        _width  = ILI9341_TFTHEIGHT;
        _height = ILI9341_TFTWIDTH;
        break;

        case 2:
        writedata(MADCTL_MY | MADCTL_BGR);
        _width  = ILI9341_TFTWIDTH;
        _height = ILI9341_TFTHEIGHT;
        break;

        case 3:
        writedata(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
        _width  = ILI9341_TFTHEIGHT;
        _height = ILI9341_TFTWIDTH;
        break;
    }

}

void Adafruit_ILI9341_8bit::invertDisplay(boolean i) {
    writecommand(i ? ILI9341_INVON : ILI9341_INVOFF);
}

// Stuff not actively being used, but kept for posterity
uint8_t Adafruit_ILI9341_8bit::read8(void) {
    RD_ACTIVE;
    delay(5);
    uint8_t temp = 0;
    if(digitalWrite(D0)) {
        temp |= (1 << 0);
    }

    // Slow reading but works

    if (digitalWrite(D1)) {
        temp |= (1 << 1);
    }

    if (digitalWrite(D2)) {
        temp |= (1 << 2);
    }

    if (digitalWrite(D3)) {
        temp |= (1 << 3);
    }

    if (digitalWrite(D4)) {
        temp |= (1 << 4);
    }

    if (digitalWrite(D5)) {
        temp |= (1 << 5);
    }

    if (digitalWrite(D6)) {
        temp |= (1 << 6);
    }

    if (digitalWrite(D7)) {
        temp |= (1 << 7);
    }

    RD_IDLE;
    delay(5);
    return temp;
}

uint8_t Adafruit_ILI9341_8bit::readcommand8(uint8_t c) {
    writecommand(c);
    CS_ACTIVE;
    CD_DATA;
    setReadDataBus();
    delay(5);
    //single dummy data
    uint8_t data = read8();
    //real data
    data = read8();
    setWriteDataBus();
    CS_IDLE;
    return data;
}

uint32_t Adafruit_ILI9341_8bit::readID(void) {
    writecommand(ILI9341_RDDID);
    CS_ACTIVE;
    CD_DATA;
    setReadDataBus();
    uint32_t r = read8();
    r <<= 8;
    r |= read8();
    r <<= 8;
    r |= read8();
    r <<= 8;
    r |= read8();
    setWriteDataBus();
    CS_IDLE;
    return r;
}

Adafruit_ILI9341_8bit TFT = Adafruit_ILI9341_8bit();
