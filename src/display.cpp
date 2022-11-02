#include "display.h"

Display::Display(int8_t sclk_pin, int8_t din_pin,
                                   int8_t dc_pin, int8_t cs_pin, int8_t rst_pin)
                : Adafruit_GFX(LCDWIDTH, LCDHEIGHT){
  spi_dev = new Adafruit_SPIDevice(cs_pin, sclk_pin, -1, din_pin,
                                   4000000); // 4mhz max speed

  _dcpin = dc_pin;
  _rstpin = rst_pin;
  
}

uint8_t pcd8544_buffer[LCDWIDTH * LCDHEIGHT / 8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFF, 0xFC, 0xE0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
    0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0xC0,
    0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC7, 0xC7, 0x87, 0x8F, 0x9F,
    0x9F, 0xFF, 0xFF, 0xFF, 0xC1, 0xC0, 0xE0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFC, 0xFC, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xF8,
    0xF0, 0xE0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0,
    0xF1, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0x0F, 0x87,
    0xE7, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F, 0x3F, 0xF9, 0xF8, 0xF8, 0xF8, 0xF8,
    0xF8, 0xF8, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x7F, 0x3F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFE, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x7E, 0x3F, 0x3F, 0x0F,
    0x1F, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xE0, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFC, 0xF0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
    0x7F, 0x7F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/*!
  @brief Update the bounding box for partial updates
  @param xmin left
  @param ymin bottom
  @param xmax right
  @param ymax top
 */
void Display::updateBoundingBox(uint8_t xmin, uint8_t ymin,
                                         uint8_t xmax, uint8_t ymax) {
  xUpdateMin = min(xUpdateMin, xmin);
  xUpdateMax = max(xUpdateMax, xmax);
  yUpdateMin = min(yUpdateMin, ymin);
  yUpdateMax = max(yUpdateMax, ymax);
}

/*!
  @brief The most basic function, set a single pixel, in the main buffer
  @param x     x coord
  @param y     y coord
  @param color pixel color (BLACK or WHITE)
 */
void Display::drawPixel(int16_t x, int16_t y, uint16_t color) {
  setPixel(x, y, color, pcd8544_buffer);
}

/*!
  @brief The most basic function, set a single pixel
  @param x     x coord
  @param y     y coord
  @param color pixel color (BLACK or WHITE)
  @param buffer The framebuffer to set the pixel in
 */
void Display::setPixel(int16_t x, int16_t y, bool color,
                                uint8_t *buffer) {
  if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
    return;

  int16_t t;
  switch (rotation) {
  case 1:
    t = x;
    x = y;
    y = LCDHEIGHT - 1 - t;
    break;
  case 2:
    x = LCDWIDTH - 1 - x;
    y = LCDHEIGHT - 1 - y;
    break;
  case 3:
    t = x;
    x = LCDWIDTH - 1 - y;
    y = t;
    break;
  }
  updateBoundingBox(x, y, x, y);

  // x is which column
  if (color)
    buffer[x + (y / 8) * LCDWIDTH] |= 1 << (y % 8);
  else
    buffer[x + (y / 8) * LCDWIDTH] &= ~(1 << (y % 8));
}

/*!
  @brief  Set the bias level
  @param val Bias value
 */
void Display::setBias(uint8_t val) {
  if (val > 0x07) {
    val = 0x07;
  }
  _bias = val;
  command(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
  command(PCD8544_SETBIAS | val);
  command(PCD8544_FUNCTIONSET);
}

/*!
  @brief Initialize the display. Set bias and contrast, enter normal mode.
 */
void Display::initDisplay() {

  // toggle RST low to reset
  if (_rstpin >= 0) {
    pinMode(_rstpin, OUTPUT);
    digitalWrite(_rstpin, LOW);
    delay(1); // 1 ns minimum
    digitalWrite(_rstpin, HIGH);
  }

  setBias(_bias);
  setContrast(_contrast);

  // normal mode
  command(PCD8544_FUNCTIONSET);

  // Set display to Normal
  command(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
}

/*!
  @brief Set up SPI, initialize the display, set the bounding box
  @param contrast Initial contrast value
  @param bias     Initial bias value
  @returns True on initialization success
 */
bool Display::begin(uint8_t contrast, uint8_t bias) {

  if (!spi_dev->begin()) {
    return false;
  }

  // Set common pin outputs.
  pinMode(_dcpin, OUTPUT);
  if (_rstpin >= 0)
    pinMode(_rstpin, OUTPUT);

  _bias = bias;
  _contrast = contrast;
  _reinit_interval = 0;
  _display_count = 0;
  initDisplay();

  // initial display line
  // set page address
  // set column address
  // write display data

  // set up a bounding box for screen updates

  updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);
  // Push out pcd8544_buffer to the Display (will show the AFI logo)
  display();

  return true;
}

/*!
  @brief  Send a command to the LCD
  @param c Command byte
 */
void Display::command(uint8_t c) {
  digitalWrite(_dcpin, LOW);
  spi_dev->write(&c, 1);
}

/*!
  @brief  Send data to the LCD
  @param c Data byte
 */
void Display::data(uint8_t c) {
  digitalWrite(_dcpin, HIGH);
  spi_dev->write(&c, 1);
}

/*!
  @brief  Set the contrast level
  @param val Contrast value
 */
void Display::setContrast(uint8_t val) {
  if (val > 0x7f) {
    val = 0x7f;
  }
  _contrast = val;
  command(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
  command(PCD8544_SETVOP | val);
  command(PCD8544_FUNCTIONSET);
}

/*!
  @brief Update the display
 */
void Display::display(void) {
  if (_reinit_interval) {
    _display_count++;
    if (_display_count >= _reinit_interval) {
      _display_count = 0;
      initDisplay();
    }
  }

  for (uint8_t page = (yUpdateMin / 8); page < (yUpdateMax / 8) + 1; page++) {
    command(PCD8544_SETYADDR | page);

    uint8_t startcol = xUpdateMin;
    uint8_t endcol = xUpdateMax;

    command(PCD8544_SETXADDR | startcol);

    digitalWrite(_dcpin, HIGH);
    spi_dev->write(pcd8544_buffer + (LCDWIDTH * page) + startcol,
                   endcol - startcol + 1);
  }

  command(PCD8544_SETYADDR); // no idea why this is necessary but it is to
                             // finish the last byte?

  xUpdateMin = LCDWIDTH - 1;
  xUpdateMax = 0;
  yUpdateMin = LCDHEIGHT - 1;
  yUpdateMax = 0;
}

/*!
  @brief Clear the entire display
 */
void Display::clearDisplay(void) {
  memset(pcd8544_buffer, 0, LCDWIDTH * LCDHEIGHT / 8);
  updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);
  cursor_y = cursor_x = 0;
}

void Display::clearRectangle(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax){
  memset(pcd8544_buffer, 0, LCDWIDTH * LCDHEIGHT / 8);
  updateBoundingBox(xmin, ymin, xmax, ymax);
  setCursor(xmin, ymin);
}

/*!
 @brief default width 6px, hight 8px (with size 1)
*/
void Display::setTextSize(uint8_t s) { setTextSize(s, s); }


void Display::setTextSize(uint8_t s_x, uint8_t s_y) {
  textsize_x = (s_x > 0) ? s_x : 1; 
  textsize_y = (s_y > 0) ? s_y : 1;
}

// макросы

void Display::setupDisplay(){
    begin();
    clearDisplay();
    display();
    
    setContrast(50); // установка контраста
    setTextSize(1);  // установка размера шрифта
    setTextColor(BLACK); // установка цвета текста

    setCursor(0, 0); // установка позиции курсора
    print("n");
    setCursor(20, 0);
    print(minSpeed);
    setCursor(0, 15);
    print("F");
    setCursor(20, 15);
    print(minSpeed);
    display();  
}

void Display::setShaftData(String newData){
    clearRectangle (54, 0, WIDTH-1, 7);
    setCursor(54, 0);
    print(newData);
    display();
}

void Display::setShaftData(uint16_t newData){
    clearRectangle (20, 0, WIDTH-1, 7);
    setCursor(20, 0);
    print(newData);
    display();
}

void Display::setShaftData(double newData){
    clearRectangle (20, 0, WIDTH-1, 7);
    setCursor(20, 0);
    print(newData);
    display();
}

void Display::setSlicerData(String newData){
    clearRectangle (54, 15, WIDTH-1, 23);
    setCursor(54, 15);
    print(newData);
    display();
}

void Display::setSlicerData(uint16_t newData){
    clearRectangle (20, 15, WIDTH-1, 23);
    setCursor(20, 15);
    print(newData);
    display();
}

void Display::setSlicerData(double newData){
    clearRectangle (20, 15, WIDTH-1, 23);
    setCursor(20, 15);
    print(newData);
    display();
}

void Display::setWeldingState(bool newState){
    clearString(5);
    setCursor(65, 31);
    if (newState) print("ON");
    else print("OFF");
    display();
}

void Display::setSomeData(String newData, int16_t x, int16_t y){
    setCursor(x, y);
    print(newData);
    display();
}

void Display::clearString(uint8_t snum){
    switch (snum)
    {
    case 0:
        clearRectangle (0, 0, WIDTH-1, 7);
        display();
        break;
    
    case 1:
        clearRectangle (0, 7, WIDTH-1, 15);
        display();
        break;
    
    case 2:
        clearRectangle (0, 15, WIDTH-1, 23);
        display();
        break;
    
    case 3:
        clearRectangle (0, 23, WIDTH-1, 31);
        display();
        break;
    
    case 4:
        clearRectangle (0, 31, WIDTH-1, 39);
        display();
        break;
    
    case 5:
        clearRectangle (0, 39, WIDTH-1, 47);
        display();
        break;
    
    default:
        break;
    }
    
}