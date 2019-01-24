#ifndef ADAFRUIT_ILI9341_8BIT_H
#define ADAFRUIT_ILI9341_8BIT_H

#include <Adafruit_GFX.h>
#include <Arduino.h>

#define ILI9341_TFTWIDTH 240
#define ILI9341_TFTHEIGHT 320
#define ILI9341_NOP 0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID 0xD3
#define ILI9341_RDDST 0x09
#define ILI9341_SLPIN 0x10
#define ILI9341_SLPOUT 0x11
#define ILI9341_PTLON 0x12
#define ILI9341_NORON 0x13
#define ILI9341_RDMODE 0x0A
#define ILI9341_RDMADCTL 0x0B
#define ILI9341_RDPIXFMT 0x0C
#define ILI9341_RDIMGFMT 0x0D
#define ILI9341_RDSELFDIAG 0x0F
#define ILI9341_INVOFF 0x20
#define ILI9341_INVON 0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPOFF 0x28
#define ILI9341_DISPON 0x29
#define ILI9341_CASET 0x2A
#define ILI9341_PASET 0x2B
#define ILI9341_RAMWR 0x2C
#define ILI9341_RAMRD 0x2E
#define ILI9341_PTLAR 0x30
#define ILI9341_MADCTL 0x36
#define ILI9341_PIXFMT 0x3A
#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR 0xB4
#define ILI9341_DFUNCTR 0xB6
#define ILI9341_PWCTR1 0xC0
#define ILI9341_PWCTR2 0xC1
#define ILI9341_PWCTR3 0xC2
#define ILI9341_PWCTR4 0xC3
#define ILI9341_PWCTR5 0xC4
#define ILI9341_VMCTR1 0xC5
#define ILI9341_VMCTR2 0xC7
#define ILI9341_RDID1 0xDA
#define ILI9341_RDID2 0xDB
#define ILI9341_RDID3 0xDC
#define ILI9341_RDID4 0xDD
#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1

// Colour definitions

#define ILI9341_BLACK 0x0000 /*   0,   0,   0 */
#define ILI9341_NAVY 0x000F /*   0,   0, 128 */
#define ILI9341_DARKGREEN 0x03E0 /*   0, 128,   0 */
#define ILI9341_DARKCYAN 0x03EF /*   0, 128, 128 */
#define ILI9341_MAROON 0x7800 /* 128,   0,   0 */
#define ILI9341_PURPLE 0x780F /* 128,   0, 128 */
#define ILI9341_OLIVE 0x7BE0 /* 128, 128,   0 */
#define ILI9341_LIGHTGREY 0xC618 /* 192, 192, 192 */
#define ILI9341_DARKGREY 0x7BEF /* 128, 128, 128 */
#define ILI9341_BLUE 0x001F /*   0,   0, 255 */
#define ILI9341_GREEN 0x07E0 /*   0, 255,   0 */
#define ILI9341_CYAN 0x07FF /*   0, 255, 255 */
#define ILI9341_RED 0xF800 /* 255,   0,   0 */
#define ILI9341_MAGENTA 0xF81F /* 255,   0, 255 */
#define ILI9341_YELLOW 0xFFE0 /* 255, 255,   0 */
#define ILI9341_WHITE 0xFFFF /* 255, 255, 255 */
#define ILI9341_ORANGE 0xFD20 /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5 /* 173, 255,  47 */
#define ILI9341_PINK 0xF81F

/*Define pins and Output Data Registers*/

#define TFT_RD 19
#define TFT_WR 20
#define TFT_RS 21
#define TFT_CS 22

#define RD_IDLE  	  digitalWrite(TFT_RD, HIGH)
#define RD_ACTIVE     digitalWrite(TFT_RD, LOW)
#define WR_IDLE       digitalWrite(TFT_WR, HIGH)
#define WR_ACTIVE     digitalWrite(TFT_WR, LOW)
#define CD_COMMAND    digitalWrite(TFT_RS, LOW)
#define CD_DATA       digitalWrite(TFT_RS, HIGH)
#define CS_IDLE       digitalWrite(TFT_CS, HIGH)
#define CS_ACTIVE     digitalWrite(TFT_CS, LOW)

#define D0 22
#define D1 23
#define D2 24
#define D3 27
#define D4 26
#define D5 27
#define D6 28
#define D7 29

class Adafruit_ILI9341_8bit: public Adafruit_GFX {
public:
    Adafruit_ILI9341_8bit(void);
    void begin(void);
    void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void pushColor(uint16_t color);
    void fillScreen(uint16_t color);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void setRotation(uint8_t r);
    void invertDisplay(boolean i);
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
    uint8_t readcommand8(uint8_t reg);
    uint32_t readID(void);
    uint8_t tabcolor;
    uint8_t read8(void);
    void setReadDataBus(void);
    void setWriteDataBus(void);
    void write8(uint8_t);
    void writecommand(uint8_t c);
    void writedata(uint8_t d);
};

extern Adafruit_ILI9341_8bit TFT;

#endif
