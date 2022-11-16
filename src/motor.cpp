#include "Motor.h"
#include "GyverTimers.h"
#include "fast_func.h"

//#define SERVICE

Motor::Motor(uint8_t MOTOR_PIN_STEP, uint8_t MOTOR_PIN_DIR,  bool direction, uint16_t pwmFrequency) {
  this->MOTOR_PIN_STEP = MOTOR_PIN_STEP;
  this->MOTOR_PIN_DIR = MOTOR_PIN_DIR;
  this->direction = direction;
  this->pwmFrequency = pwmFrequency;
}

Motor::Motor(uint8_t MOTOR_PIN_STEP, uint16_t pwmFrequency) {
  this->MOTOR_PIN_STEP = MOTOR_PIN_STEP;
  this->pwmFrequency = pwmFrequency;
}


void Motor::setSpeed(uint16_t newSpeed) {
  currentSpeed = newSpeed*kSpeed;
  if (currentSpeed == 0){
    stop();
    return;
  }
  pwmFrequency = round (newSpeed * kSpeed);
  switch (MOTOR_PIN_STEP)
    {
    case 3:
      Timer2.setFrequency(pwmFrequency);
      Timer2.outputEnable(CHANNEL_B, TOGGLE_PIN);
      //Timer2.enableISR(CHANNEL_B);
      break;
    
    case 5:
      /* code */
      break;

    case 6:
      /* code */
      break;

    case 9:
      Timer1.setFrequency(pwmFrequency);
      Timer1.outputEnable(CHANNEL_A, TOGGLE_PIN);
      //Timer1.enableISR(CHANNEL_A);
      break;
      
    case 10:
      Timer1.setFrequency(pwmFrequency);
      Timer1.outputEnable(CHANNEL_B, TOGGLE_PIN);
      //Timer1.enableISR(CHANNEL_B);
      break;

    case 11:
      Timer2.setFrequency(pwmFrequency);
      Timer2.outputEnable(CHANNEL_A, TOGGLE_PIN);
      break;
    }

}

uint16_t Motor::getPeriod(){
  return currentPeriod;
}

uint16_t Motor::getSpeed(){
  return currentSpeed;
}

void Motor::setPeriod(uint16_t newPeriod){
  currentPeriod = newPeriod;
}

void Motor::setFrequency(uint16_t newFreq){
  pwmFrequency = newFreq*KOEF_FREQ;
}

void Motor::stop(){

  switch (MOTOR_PIN_STEP)
    {
    case 3:
      Timer2.outputDisable(CHANNEL_B);
      //Timer2.disableISR(CHANNEL_B);
      break;
    
    case 5:         //Timer 0 Chan B
      /* code */
      break;

    case 6:         //Timer 0 Chan A
      /* code */
      break;

    case 9:
      Timer1.outputDisable(CHANNEL_A);
      //Timer1.disableISR(CHANNEL_A);
      break;
      
    case 10:
      Timer1.outputDisable(CHANNEL_B);
      //Timer1.disableISR(CHANNEL_B);
      break;

    case 11:
    Timer2.outputDisable(CHANNEL_A);
     // Timer2.disableISR(CHANNEL_A);
      break;
    }
}