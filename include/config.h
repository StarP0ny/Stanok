#pragma once

// настройки шим
#define DEFAULT_PWM                 980

// пины кнопок и резистора
#define SHAFT_SPEED_RESISTOR_PIN    A0

// конфигурация мотора вала
#define MOTOR_SHAFT_PUL_PIN    3
//#define MOTOR_SHAFT_DIR_PIN    4
//#define MOTOR_SHAFT_EN_PIN 5 // нормально движение разрешено
#define DEFAULT_PWM_SHAFT      10000 // in Hz

// конфигурация мотора резака
#define MOTOR_SLICER_PUL_PIN    6
//#define MOTOR_SLICER_DIR_PIN    7
#define DEFAULT_PWM_SLICER      10000 // in Hz

// конфигурация дисплея
#define RST_PIN     7
#define CE_PIN      6
#define DC_PIN      5
#define Din_PIN     4
#define Clk_PIN     3