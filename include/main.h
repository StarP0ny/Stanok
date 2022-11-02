#pragma once
#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "fast_func.h"
#include "motor.h"
#include <GyverTimers.h>
#include "filters.h"

float readAPin(uint8_t pin, uint8_t filtr = 3);