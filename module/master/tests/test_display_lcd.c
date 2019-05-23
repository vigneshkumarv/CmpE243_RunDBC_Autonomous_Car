#include "unity.h"

#include "MockSerial_LCD.h"
#include "Mockswitches_wrapper.h"
#include "display_lcd.h"
#include "generated_can.h"
#include "navigation.h"

void setUp(void) {}

void tearDown(void) {}

void test_initialize_display_lcd(void) {
  init_serial_lcd_Expect();
  init_switches_ExpectAndReturn(true);
  initialize_display_lcd();
}
void test_display_screens(void) {}
void test_display_operation_data(void) {}
void test_display_sensor_data(void) {}
void test_display_motor_debug(void) {}
void test_display_geo_debug(void) {}
