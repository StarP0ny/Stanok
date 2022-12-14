#pragma once

// настройки шим
const uint16_t DEFAULT_PWM = 980;
const uint16_t KOEF_FREQ = 2;

// пины кнопок и резисторов
#define SHAFT_SPD_COARSE_RESISTOR_PIN    A4
#define SHAFT_SPD_FINE_TUNE_RES_PIN      A2
#define SHAFT_START_BUTTON_PIN           12
#define SHAFT_TURBO_BUTTON_PIN           8
const uint8_t SHAFT_KOEF_FINE_TUNE = 10;

#define SLICER_SPD_COARSE_RESISTOR_PIN   A1
#define SLICER_SPD_FINE_TUNE_RES_PIN     A0
#define SLICER_START_BUTTON_PIN          13
#define SLICER_TURBO_BUTTON_PIN          10
const uint8_t SLICER_KOEF_FINE_TUNE = 10;

// конфигурация мотора вала
#define MOTOR_SHAFT_PUL_PIN              11

// конфигурация мотора резака
#define MOTOR_SLICER_PUL_PIN             9

// конфигурация дисплея
#define RST_PIN                          7
#define CE_PIN                           6
#define DC_PIN                           5
#define Din_PIN                          4
#define Clk_PIN                          2



const uint16_t turboSpeed = 1023;
const uint16_t minSpeed = 0;
const uint32_t newCicle = 500;
const uint32_t kSpeed = 8;