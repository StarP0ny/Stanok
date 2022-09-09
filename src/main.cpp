#include <main.h>
uint16_t periodCounter = 0, stepsCounter = 0;
Motor shaftMotor(MOTOR_SHAFT_PUL_PIN, DEFAULT_PWM);
Motor slicerMotor(MOTOR_SLICER_PUL_PIN, DEFAULT_PWM);
void setup() {
  pinMode(MOTOR_SHAFT_PUL_PIN, OUTPUT);
 // Timer1.stop();
  //Timer2.stop();
  shaftMotor.setPeriod(1024);
  //setupDisplay();
}

ISR(TIMER1_A){    //D9
  periodCounter++;
  if (stepsCounter < shaftMotor.getSteps()){
      stepsCounter++;
      pinWrite(MOTOR_SHAFT_PUL_PIN, !pinRead(MOTOR_SHAFT_PUL_PIN));
  }
  else pinWrite(MOTOR_SHAFT_PUL_PIN, LOW);
  if (periodCounter >= shaftMotor.getPeriod()){
      periodCounter = 0;
      stepsCounter = 0;
  }
}

ISR(TIMER1_B){    //D10
  pinWrite(10, !pinRead(10));
}

ISR(TIMER2_A){    //D11
  
}

ISR(TIMER2_B){    //D3
  pinWrite(MOTOR_SHAFT_PUL_PIN, !pinRead(MOTOR_SHAFT_PUL_PIN));
}

void loop() {
  // put your main code here, to run repeatedly:
  shaftMotor.setSpeed((uint16_t) analogRead(SHAFT_SPEED_RESISTOR_PIN));
 // delay(500);
}

void speedShaft(){
  shaftMotor.setSpeed((uint16_t) analogRead(SHAFT_SPEED_RESISTOR_PIN));
}