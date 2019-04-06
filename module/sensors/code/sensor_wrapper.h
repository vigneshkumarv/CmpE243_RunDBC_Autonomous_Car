// this .h file provides functions to read sensor values
#ifndef SENSOR_WRAPPER_H_
#define SENSOR_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef enum { low = 0, high = 1 } pin_value;

typedef enum { INPUT_MODE = 0, OUTPUT_MODE = 1 } pin_mode;

// initialization of ultrasonic sensors
void init_left_trig_pin(pin_mode pinMode);
void init_left_echo_pin(pin_mode pinMode);
void init_right_trig_pin(pin_mode pinMode);
void init_right_echo_pin(pin_mode pinMode);
void init_middle_an_pin(void);
void init_rear_an_pin(void);
void init_left_bumper(void);
void init_right_bumper(void);

// set trig pin to low or high
void left_trig_pin_set(pin_value pinValue);
void right_trig_pin_set(pin_value pinValue);

// read echo pin value - true = high, false = low
bool read_left_echo_pin(void);
bool read_right_echo_pin(void);
bool read_bumper_sensor_pin_left(void);
bool read_bumper_sensor_pin_right(void);

#ifdef __cplusplus
}
#endif
#endif
