#pragma once
#include <inttypes.h>
#include <Arduino.h>



uint8_t attachPCINT(uint8_t pin);
bool pinRead(uint8_t pin);
void pinWrite(uint8_t pin, bool x);
void digitalToggleFast(uint8_t pin);
void pinModeFast(uint8_t pin, uint8_t mode);
void attachInterruptFast(uint8_t num, uint8_t type);
void detachInterruptFast(uint8_t num);

