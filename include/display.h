#pragma once
#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>
#include "config.h"
#include <stdlib.h>

#define BLACK 1 ///< Black pixel
#define WHITE 0 ///< White pixel

#define LCDWIDTH 84  ///< LCD is 84 pixels wide
#define LCDHEIGHT 48 ///< 48 pixels high

#define PCD8544_POWERDOWN 0x04 ///< Function set, Power down mode
#define PCD8544_ENTRYMODE 0x02 ///< Function set, Entry mode
#define PCD8544_EXTENDEDINSTRUCTION                                            \
  0x01 ///< Function set, Extended instruction set control

#define PCD8544_DISPLAYBLANK 0x0    ///< Display control, blank
#define PCD8544_DISPLAYNORMAL 0x4   ///< Display control, normal mode
#define PCD8544_DISPLAYALLON 0x1    ///< Display control, all segments on
#define PCD8544_DISPLAYINVERTED 0x5 ///< Display control, inverse mode

#define PCD8544_FUNCTIONSET 0x20 ///< Basic instruction set
#define PCD8544_DISPLAYCONTROL                                                 \
  0x08 ///< Basic instruction set - Set display configuration
#define PCD8544_SETYADDR                                                       \
  0x40 ///< Basic instruction set - Set Y address of RAM, 0 <= Y <= 5
#define PCD8544_SETXADDR                                                       \
  0x80 ///< Basic instruction set - Set X address of RAM, 0 <= X <= 83

#define PCD8544_SETTEMP                                                        \
  0x04 ///< Extended instruction set - Set temperature coefficient
#define PCD8544_SETBIAS 0x10 ///< Extended instruction set - Set bias system
#define PCD8544_SETVOP                                                         \
  0x80 ///< Extended instruction set - Write Vop to register

/**************************************************************************/
/*!
    @brief The PCD8544 LCD class
 */
class Display : public Adafruit_GFX{
public:
    Display(int8_t sclk_pin, int8_t din_pin, int8_t dc_pin,
                     int8_t cs_pin, int8_t rst_pin);
  
    bool begin(uint8_t contrast = 40, uint8_t bias = 0x04);
  
    void command(uint8_t c);
    void data(uint8_t c);
  
    void setContrast(uint8_t val);
    uint8_t getContrast(void);
  
    uint8_t getBias(void);
    void setBias(uint8_t val);
  
    void clearDisplay(void);
    void clearRectangle(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax);
    void clearString(uint8_t snum);
    void display();
    void updateBoundingBox(uint8_t xmin, uint8_t ymin, uint8_t xmax,
                           uint8_t ymax);
  
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void setPixel(int16_t x, int16_t y, bool color, uint8_t *buffer);
    /*void setCursor(int16_t x, int16_t y) {
        cursor_x = x;
        cursor_y = y;
    }*/
    void setTextColor(uint16_t c) { textcolor = textbgcolor = c; }
    void setTextSize(uint8_t s);
    void setTextSize(uint8_t sx, uint8_t sy);

    void initDisplay();

    void setupDisplay();
    void setShaftData(String newData);
    void setSlicerData(String newData);
    void setWeldingData(String newData);
    void setShaftData(uint16_t newData);
    void setSlicerData(uint16_t newData);
    void setWeldingData(uint16_t newData);
    void setShaftData(double newData);
    void setSlicerData(double newData);
    void setWeldingData(double newData);
    void setWeldingState(bool newState);
    void setSomeData(String newData, int16_t x, int16_t y);
private:
  Adafruit_SPIDevice *spi_dev = NULL;
  int8_t _rstpin = -1, _dcpin = -1;

  uint8_t _contrast;        ///< Contrast level, Vop
  uint8_t _bias;            ///< Bias value
  uint8_t _reinit_interval; ///< Reinitialize the display after this many calls
                            ///< to display()
  uint8_t _display_count;   ///< Count for reinit interval
  int16_t _width = LCDWIDTH;       ///< Display width as modified by current rotation
  int16_t _height = LCDHEIGHT; 
  uint8_t xUpdateMin, xUpdateMax, yUpdateMin, yUpdateMax;
  uint8_t rotation = 0;     ///< Display rotation (0 thru 3)
  int16_t WIDTH = LCDWIDTH;        ///< This is the 'raw' display width - never changes
  int16_t HEIGHT = LCDHEIGHT;       ///< This is the 'raw' display height - never changes
  int16_t cursor_x = 0;     ///< x location to start print()ing text
  int16_t cursor_y = 0;     ///< y location to start print()ing text
  uint16_t textcolor = 0xFFFF;   ///< 16-bit background color for print()
  uint16_t textbgcolor = 0xFFFF; ///< 16-bit text color for print()
  uint8_t textsize_x = 1;   ///< Desired magnification in X-axis of text to print()
  uint8_t textsize_y = 1;   ///< Desired magnification in Y-axis of text to print()
  bool wrap = true;            ///< If set, 'wrap' text at right edge of display
  bool _cp437 = false;          ///< If set, use correct CP437 charset (default is off)

};
