#include "Motor.h"
#include "GyverTimers.h"
#include "fast_func.h"

//#define SERVICE

Motor::Motor(uint8_t MOTOR_PIN_STEP, uint8_t MOTOR_PIN_DIR,  bool direction, uint16_t PWM_FREQUENCY) {
  this->MOTOR_PIN_STEP = MOTOR_PIN_STEP;
  this->MOTOR_PIN_DIR = MOTOR_PIN_DIR;
  this->direction = direction;
  this->PWM_FREQUENCY = PWM_FREQUENCY;
}

Motor::Motor(uint8_t MOTOR_PIN_STEP, uint16_t PWM_FREQUENCY) {
  this->MOTOR_PIN_STEP = MOTOR_PIN_STEP;
  this->PWM_FREQUENCY = PWM_FREQUENCY;
}


void Motor::setSpeed(uint16_t newSpeed) {
  currentSpeed = newSpeed;


  switch (MOTOR_PIN_STEP)
    {
    case 3:
      Timer2.setFrequency(2*newSpeed);
      Timer2.enableISR(CHANNEL_B);
      break;
    
    case 5:
      /* code */
      break;

    case 6:
      /* code */
      break;

    case 9:
      Timer1.setFrequency(DEFAULT_PWM);
      Timer1.enableISR(CHANNEL_A);
      break;
      
    case 10:
      Timer1.setFrequency(DEFAULT_PWM);
      Timer1.enableISR(CHANNEL_B);
      break;

    case 11:
      /* code */
      break;
    }

}

uint16_t Motor::getPeriod(){

  return currentPeriod;
}

uint16_t Motor::getSteps(){

  return currentSpeed;
}

void Motor::setPeriod(uint16_t newPeriod){
  currentPeriod = newPeriod;
}


void Motor::setSteps(uint16_t newSteps){
  currentSpeed = newSteps;
}

void Motor::stop(){

  switch (MOTOR_PIN_STEP)
    {
    case 3:
      Timer2.disableISR(CHANNEL_B);
      break;
    
    case 5:         //Timer 0 Chan B
      /* code */
      break;

    case 6:         //Timer 0 Chan A
      /* code */
      break;

    case 9:
      Timer1.disableISR(CHANNEL_A);
      break;
      
    case 10:
      Timer1.disableISR(CHANNEL_B);
      break;

    case 11:
      Timer2.disableISR(CHANNEL_A);
      break;
    }
}