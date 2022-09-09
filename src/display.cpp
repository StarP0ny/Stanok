#include <display.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(Clk_PIN, Din_PIN, DC_PIN, CE_PIN, RST_PIN);

display::display(uint8_t SCK, uint8_t MOSI, uint8_t DC, uint8_t RST, uint8_t CS){
    this->SCK = SCK;
    this->MOSI = MOSI;
    this->DC = DC;
    this->RST = RST;
    this->CS = CS;
    //Adafruit_PCD8544
}

// макросы

void setupDisplay(){
    display.begin();
    display.clearDisplay();
    display.display();
    
    display.setContrast(50); // установка контраста
    delay(1000);
    display.setTextSize(2);  // установка размера шрифта
    display.setTextColor(BLACK); // установка цвета текста
    display.setCursor(0,0); // установка позиции курсора
  
    display.println("Net ti");
    display.display();
}