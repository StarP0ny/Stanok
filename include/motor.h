#pragma once
#include <inttypes.h>
#include <Arduino.h>
#include "config.h"

class Motor {
public:

  Motor(uint8_t MOTOR_PIN_STEP, uint8_t MOTOR_PIN_DIR,  bool direction, uint16_t PWM_FREQUENCY);
  Motor(uint8_t MOTOR_PIN_STEP, uint16_t PWM_FREQUENCY);
  void stop();
  void setSpeed(uint16_t speed);
  void setDirection(bool newDir);
  uint16_t getPeriod();
  uint16_t getSteps();
  void setPeriod(uint16_t newPeriod);
  void setSteps(uint16_t newSteps);
 // void applySpeed();

private:
  uint16_t PWM_FREQUENCY = DEFAULT_PWM;
  uint16_t currentPeriod = 0;
  uint16_t currentSpeed = 0;
  uint8_t MOTOR_PIN_DIR;
  uint8_t MOTOR_PIN_STEP;
  bool direction = false;
  volatile bool movement = false;
};

