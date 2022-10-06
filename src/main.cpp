#include <main.h>
uint16_t periodCounter = 0, stepsCounter = 0;

const uint16_t turboSpeed = 1023u;
const uint8_t minSpeed = 0;

Motor shaftMotor(MOTOR_SHAFT_PUL_PIN, DEFAULT_PWM);
Motor slicerMotor(MOTOR_SLICER_PUL_PIN, DEFAULT_PWM);

Display display(Clk_PIN, Din_PIN, DC_PIN, CE_PIN, RST_PIN);

void setup() {

  pinMode(MOTOR_SHAFT_PUL_PIN, OUTPUT);
  pinMode(MOTOR_SLICER_PUL_PIN, OUTPUT);

  pinMode(SHAFT_START_SWITCH_PIN, INPUT);
  pinMode(SLICER_START_SWITCH_PIN, INPUT);
  pinMode(SHAFT_TURBO_BUTTON_PIN, INPUT);
  pinMode(SLICER_TURBO_BUTTON_PIN, INPUT);

 // Timer1.stop();
  //Timer2.stop();
 // shaftMotor.setPeriod(1024);
  //setupDisplay();
}

/*
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
*/

void loop() {
  // put your main code here, to run repeatedly:
  if (SHAFT_START_SWITCH_PIN and !SHAFT_TURBO_BUTTON_PIN){
    shaftMotor.setSpeed((uint16_t) analogRead(SHAFT_SPEED_RESISTOR_PIN) +
                        (uint16_t) analogRead(SHAFT_SPD_FINE_TUNE_RES_PIN)/SHAFT_KOEF_FINE_TUNE);
    display.setShaftData(shaftMotor.getSpeed());
  } 
  else if (SHAFT_TURBO_BUTTON_PIN){
    shaftMotor.setSpeed(turboSpeed);

  }
  else if (!SHAFT_START_SWITCH_PIN and !SHAFT_TURBO_BUTTON_PIN){
    shaftMotor.setSpeed(minSpeed);

  }

  if (SLICER_START_SWITCH_PIN and !SLICER_TURBO_BUTTON_PIN){
    slicerMotor.setSpeed((uint16_t) analogRead(SLICER_SPEED_RESISTOR_PIN) +
                         (uint16_t) analogRead(SLICER_SPD_FINE_TUNE_RES_PIN)/SLICER_KOEF_FINE_TUNE);
  }

  else if (SLICER_TURBO_BUTTON_PIN){
    slicerMotor.setSpeed(turboSpeed);

  }
  else if (!SLICER_START_SWITCH_PIN and !SHAFT_TURBO_BUTTON_PIN){
    slicerMotor.setSpeed(minSpeed);

  }
 // delay(500);
}

