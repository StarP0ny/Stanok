#include "main.h"

Motor shaftMotor(MOTOR_SHAFT_PUL_PIN, DEFAULT_PWM);
Motor slicerMotor(MOTOR_SLICER_PUL_PIN, DEFAULT_PWM);

Display display(Clk_PIN, Din_PIN, DC_PIN, CE_PIN, RST_PIN);

uint16_t periodCounter = 0, stepsCounter = 0;

uint32_t time = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_SHAFT_PUL_PIN, OUTPUT);
  pinMode(MOTOR_SLICER_PUL_PIN, OUTPUT);

  pinMode(SHAFT_START_BUTTON_PIN, INPUT);
  pinMode(SLICER_START_BUTTON_PIN, INPUT);
  pinMode(SHAFT_TURBO_BUTTON_PIN, INPUT);
  pinMode(SLICER_TURBO_BUTTON_PIN, INPUT);
  pinMode(13, INPUT_PULLUP);

  display.setupDisplay();
  display.setWeldingState(false);
}

void loop() {
  if(millis() - time > newCicle){
    time = millis();
    
    if (pinRead(SHAFT_START_BUTTON_PIN) and !pinRead(SHAFT_TURBO_BUTTON_PIN)){
      shaftMotor.setSpeed((uint16_t) analogRead(SHAFT_SPD_COARSE_RESISTOR_PIN) +
                          (uint16_t) analogRead(SHAFT_SPD_FINE_TUNE_RES_PIN)/SHAFT_KOEF_FINE_TUNE);
      display.setShaftData(shaftMotor.getSpeed());
      display.setShaftData("ON");
    } 
    
    else if (pinRead(SHAFT_TURBO_BUTTON_PIN)){
      shaftMotor.setSpeed(turboSpeed);
      display.setShaftData(shaftMotor.getSpeed());
      display.setShaftData("TURBO");
    }

    else if (!pinRead(SHAFT_START_BUTTON_PIN) and !pinRead(SHAFT_TURBO_BUTTON_PIN)){
      shaftMotor.setSpeed(minSpeed);
      display.setShaftData(minSpeed);
      display.setShaftData("OFF");
    }

    if (pinRead(SLICER_START_BUTTON_PIN) and !pinRead(SLICER_TURBO_BUTTON_PIN)){
      slicerMotor.setSpeed((uint16_t) analogRead(SLICER_SPD_COARSE_RESISTOR_PIN) +
                          (uint16_t) analogRead(SLICER_SPD_FINE_TUNE_RES_PIN)/SLICER_KOEF_FINE_TUNE);
      display.setSlicerData(slicerMotor.getSpeed());
      display.setSlicerData("ON");
    }

    else if (pinRead(SLICER_TURBO_BUTTON_PIN)){
      slicerMotor.setSpeed(turboSpeed);
      display.setSlicerData("TURBO");
    }
    
    else if (!pinRead(SLICER_START_BUTTON_PIN) and !pinRead(SHAFT_TURBO_BUTTON_PIN)){
      slicerMotor.setSpeed(minSpeed);
      display.setSlicerData(slicerMotor.getSpeed());
      display.setSlicerData("OFF");
    }
    //delay(500);
    //display.display();
  }
}

float readAPin(uint8_t pin, uint8_t filtr){
  float analR = (float) analogRead(pin);
  switch (filtr)
  {
  case 1:
    runMiddleArifm(analR);
    break;
  
  case 2:
    runMiddleArifmOptim(analR);
    break;
  
  case 3:
    simpleKalman(analR);
    break;
  
  default:
    return analR;
  }
  //return analR;
}