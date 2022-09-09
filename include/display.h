#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "config.h"

class display
{
private:
    uint8_t SCK, MOSI, DC, RST, CS;
public:
    display(uint8_t SCK, uint8_t MOSI, uint8_t DC, uint8_t RST, uint8_t CS);
    ~display();
};

void setupDisplay();