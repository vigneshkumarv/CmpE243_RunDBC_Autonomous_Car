#include "sensor_wrapper.h"
#include "gpio.hpp"

//GPIO left_trig(P2_0);
//GPIO left_echo(P2_1);
//GPIO right_trig(P2_2);
//GPIO right_echo(P2_3);
GPIO bumper_sensor_pin_left(P1_19);
GPIO bumper_sensor_pin_right(P1_20);
GPIO gpio_middle_trigger(P2_1);
GPIO gpio_left_right_trigger(P2_0);
//GPIO middle_echo(P2_0);


//initialization of ultrasonic sensors

void init_gpio_middle_trigger_pin(void)
{
    gpio_middle_trigger.setAsOutput();
}
void init_gpio_left_right_trigger_pin(void)
{
    gpio_left_right_trigger.setAsInput();
}

/*
void init_right_trig_pin(pin_mode pinMode)
{
  right_trig.setAsOutput();
}
void init_right_echo_pin(pin_mode pinMode)
{
  right_echo.setAsInput();
}
*/

/* Middle Pin - P2.0 ADC4*/
/*void init_middle_echo_pin(void)  // setup middle echo pin
{
    middle_echo.setAsInput();
}*/

/* Left Pin - P0.26 ADC3 */
void init_left_an_pin(void){
    LPC_PINCON->PINSEL1 |= (1 << 20);
}

/* Middle Pin - P1.30 ADC4*/
void init_middle_an_pin(void)
{
    LPC_PINCON->PINSEL3 |= (3 << 28);
}

/* Right Pin - P1.31 ADC3 */
void init_right_an_pin(void){
    LPC_PINCON->PINSEL3 |= (3 << 30);
}

/* Rear Pin - P0.25 ADC2*/
void init_rear_an_pin(void)
{
    LPC_PINCON->PINSEL1 |= (1 << 18);
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

void gpio_middle_trigger_set(pin_value pinValue)
{
  if(pinValue == high)
  {
      gpio_middle_trigger.setHigh();
  }
  else
  {
      gpio_middle_trigger.setLow();
  }
}
void gpio_left_right_trigger_set(pin_value pinValue)
{
  if(pinValue == high)
  {
      gpio_left_right_trigger.setHigh();
  }
  else
  {
      gpio_left_right_trigger.setLow();
  }
}
/*
//read echo pin value - true = high, false = low
bool read_left_echo_pin(void)
{
  return left_echo.read();
}
bool read_right_echo_pin(void)
{
  return right_echo.read();
}
*/
bool read_bumper_sensor_pin_left(void)
{
    return bumper_sensor_pin_left.read();
}

bool read_bumper_sensor_pin_right(void)
{
    return bumper_sensor_pin_right.read();
}
