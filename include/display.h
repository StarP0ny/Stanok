#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "config.h"

class Display
{
private:
    uint8_t SCK, MOSI, DC, RST, CS;
public:
    Display(uint8_t SCK, uint8_t MOSI, uint8_t DC, uint8_t RST, uint8_t CS);
    //~Display();

    void setShaftData(String newData);
    void setSlicerData(String newData);
    void setShaftData(uint16_t newData);
    void setSlicerData(uint16_t newData);
};

void setupDisplay();
