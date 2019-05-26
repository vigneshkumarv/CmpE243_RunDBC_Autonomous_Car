#include "unity.h"

#include "Mockdisplay_lcd.h"
#include "Mockmaster_can.h"
#include "Mocknavigation.h"
#include "c_periodic_callbacks.h"

extern navigation_state_machine_S state_variables;
extern navigation_sensors_S sensor_data;
extern navigation_motor_cmd_S motor_command;
extern GEO_DATA_t geo_data;
extern GEO_COORDINATE_DATA_t geo_coordinates;
extern GEO_DEBUG_DATA_t geo_debug;
extern MOTOR_DATA_t motor_actual;

void setUp(void) {}

void tearDown(void) {}

void test_c_period_init(void) {
  init_navigation_ExpectAnyArgs();
  init_can_ExpectAndReturn(true);
  initialize_display_lcd_Expect();
  TEST_ASSERT_TRUE(c_period_init());

  init_navigation_ExpectAnyArgs();
  init_can_ExpectAndReturn(false);
  initialize_display_lcd_Expect();
  TEST_ASSERT_FALSE(c_period_init());
}

void test_c_period_reg_tlm(void) { TEST_ASSERT_TRUE(c_period_reg_tlm()); }

void test_c_period_1Hz(void) {
  check_and_restart_can_Expect();
  send_heartbeat_msg_Expect();
  c_period_1Hz(100);
}

void test_c_period_10Hz(void) {
  send_debug_msg_Expect(state_variables);
  display_screens_Expect(100, state_variables, geo_data, geo_coordinates, geo_debug, motor_command, motor_actual,
                         sensor_data);
  c_period_10Hz(100);
}

void test_c_period_100Hz(void) {
  c_period_100Hz(3);

  read_can_50Hz_ExpectAndReturn(&sensor_data, &geo_data, &geo_coordinates, &geo_debug, &state_variables, &motor_actual,
                                true);
  navigation_state_machine_ExpectAnyArgs();
  send_drive_cmd_Expect(motor_command);
  c_period_100Hz(38);
}

void test_c_period_1000Hz(void) { c_period_1000Hz(100); }
