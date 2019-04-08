#include "sensor_wrapper.h"
#include "gpio.hpp"

GPIO left_trig(P2_0);
GPIO left_echo(P2_1);
GPIO right_trig(P2_2);
GPIO right_echo(P2_3);
GPIO bumper_sensor_pin_left(P1_19);
GPIO bumper_sensor_pin_right(P1_20);

//initialization of ultrasonic sensors
void init_left_trig_pin(pin_mode pinMode)
{
  left_trig.setAsOutput();
}
void init_left_echo_pin(pin_mode pinMode)
{
  left_echo.setAsInput();
}
void init_right_trig_pin(pin_mode pinMode)
{
  right_trig.setAsOutput();
}
void init_right_echo_pin(pin_mode pinMode)
{
  right_echo.setAsInput();
}

void init_middle_an_pin(void)
{
    LPC_PINCON->PINSEL3 |= (3 << 28);
}

void init_rear_an_pin(void)
{
    LPC_PINCON->PINSEL3 |= (3 << 30);
}

void init_left_bumper(void)
{
    bumper_sensor_pin_left.setAsInput();
    bumper_sensor_pin_left.enablePullUp();
}

void init_right_bumper(void)
{
    bumper_sensor_pin_right.setAsInput();
    bumper_sensor_pin_right.enablePullUp();
}

//set trig pin to low or high
void left_trig_pin_set(pin_value pinValue)
{
  if(pinValue == high)
  {
    left_trig.setHigh();
  }
  else
  {
    left_trig.setLow();
  }
}
void right_trig_pin_set(pin_value pinValue)
{
  if(pinValue == high)
  {
    right_trig.setHigh();
  }
  else
  {
    right_trig.setLow();
  }
}

//read echo pin value - true = high, false = low
bool read_left_echo_pin(void)
{
  return left_echo.read();
}
bool read_right_echo_pin(void)
{
  return right_echo.read();
}

bool read_bumper_sensor_pin_left(void)
{
    return bumper_sensor_pin_left.read();
}

bool read_bumper_sensor_pin_right(void)
{
    return bumper_sensor_pin_right.read();
}