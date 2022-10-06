#pragma once

// настройки шим
const uint16_t DEFAULT_PWM = 980;
const uint16_t KOEF_FREQ = 2;

// пины кнопок и резисторов
#define SHAFT_SPEED_RESISTOR_PIN         A0
#define SHAFT_SPD_FINE_TUNE_RES_PIN      A1
#define SHAFT_START_SWITCH_PIN           13
#define SHAFT_TURBO_BUTTON_PIN           10
#define SHAFT_KOEF_FINE_TUNE             10

#define SLICER_SPEED_RESISTOR_PIN        A2
#define SLICER_SPD_FINE_TUNE_RES_PIN     A3
#define SLICER_START_SWITCH_PIN          12
#define SLICER_TURBO_BUTTON_PIN          8
#define SLICER_KOEF_FINE_TUNE            10

// конфигурация мотора вала
#define MOTOR_SHAFT_PUL_PIN              11

// конфигурация мотора резака
#define MOTOR_SLICER_PUL_PIN             9

// конфигурация дисплея
#define RST_PIN                          7
#define CE_PIN                           6
#define DC_PIN                           5
#define Din_PIN                          4
#define Clk_PIN                          3