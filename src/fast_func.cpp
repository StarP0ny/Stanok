#include "fast_func.h"


void pinWrite(uint8_t pin, bool x) {
  switch (pin) {            
    case 3: bitClear(TCCR2A, COM2B1);
      break;
    case 5: bitClear(TCCR0A, COM0B1);
      break;
    case 6: bitClear(TCCR0A, COM0A1);
      break;
    case 9: bitClear(TCCR1A, COM1A1);
      break;
    case 10: bitClear(TCCR1A, COM1B1);
      break;
    case 11: bitClear(TCCR2A, COM2A1);   // PWM disable 
      break;
  }
  if (pin < 8) {
    bitWrite(PORTD, pin, x);
  } else if (pin < 14) {
    bitWrite(PORTB, (pin - 8), x);
  } else if (pin < 20) {
    bitWrite(PORTC, (pin - 14), x);    // Set pin to HIGH / LOW 
  }
}

// функция для настройки PCINT
uint8_t attachPCINT(uint8_t pin) {
  if (pin < 8) {            // D0-D7 (PCINT2)
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << pin); return 2; } else if (pin > 13) {    //A0-A5 (PCINT1)
    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << pin - 14);
    return 1;
  } else {                  // D8-D13 (PCINT0)
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << pin - 8);
    return 0;
  }
}

// fast digitalRead for ISR
bool pinRead(uint8_t pin) {
  if (pin < 8) {
    return bitRead(PIND, pin);
  } else if (pin < 14) {
    return bitRead(PINB, pin - 8);
  } else if (pin < 20) {
    return bitRead(PINC, pin - 14);
  }
}

// быстро инвертирует состояние пина
void digitalToggleFast(uint8_t pin) {
  if (pin < 8) {
    bitSet(PIND, pin);
  } else if (pin < 14) {
    bitSet(PINB, (pin - 8));
  } else if (pin < 20) {
    bitSet(PINC, (pin - 14));    // Toggle pin state (for 'tone()')
  }
}

void pinModeFast(uint8_t pin, uint8_t mode) {
  switch (mode) {
    case INPUT:
      if (pin < 8) {
        bitClear(DDRD, pin);    
        bitClear(PORTD, pin);
      } else if (pin < 14) {
        bitClear(DDRB, (pin - 8));
        bitClear(PORTB, (pin - 8));
      } else if (pin < 20) {
        bitClear(DDRC, (pin - 14));   // Mode: INPUT
        bitClear(PORTC, (pin - 8));  // State: LOW
      }
      return;
    case OUTPUT:
      if (pin < 8) {
        bitSet(DDRD, pin);
        bitClear(PORTD, pin);
      } else if (pin < 14) {
        bitSet(DDRB, (pin - 8));
        bitClear(PORTB, (pin - 8));
      } else if (pin < 20) {
        bitSet(DDRC, (pin - 14));  // Mode: OUTPUT
        bitClear(PORTC, (pin - 8));  // State: LOW
      }
      return;
    case INPUT_PULLUP:
      if (pin < 8) {
        bitClear(DDRD, pin);
        bitSet(PORTD, pin);
      } else if (pin < 14) {
        bitClear(DDRB, (pin - 8));
        bitSet(PORTB, (pin - 8));
      } else if (pin < 20) {
        bitClear(DDRC, (pin - 14));  // Mode: OUTPUT
        bitSet(PORTC, (pin - 14));  // State: HIGH
      }
      return;
  }
}

void attachInterruptFast(uint8_t num, uint8_t type) {
  switch (num) {          
    case 0:
      EICRA = (EICRA & 0x0C) | type;  // Setup interrupt type
      bitSet(EIMSK, INT0);        // Enable external interrupt
      return;
    case 1:
      EICRA = (EICRA & 0x03) | (type << 2);
      bitSet(EIMSK, INT1);
      return;
  }
}
void detachInterruptFast(uint8_t num) {
  bitClear(EIMSK, num);          // Disable external interrupt
}
// векторы. В них будет прыгать прерывания
/*
ISR(INT0_vect) {
}
ISR(INT1_vect) {
}
*/