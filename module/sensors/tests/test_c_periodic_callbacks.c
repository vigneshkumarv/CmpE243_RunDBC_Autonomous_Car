#include "unity.h"

#include "c_periodic_callbacks.h"
#include "Mockcar_sensors.h"
#include "Mockread_and_send.h"
#include "Mockutilities.h"
#include "Mockcan.h"

can_t sensor_module;

void setUp(void) {}

void tearDown(void) {}

void test_c_period_init(void) {
  init_sensors_Expect();
  CAN_init_ExpectAndReturn(can1, 100, 64, 64, (void *)0, (void *)0, true);
  CAN_init_IgnoreArg_can();
  CAN_init_IgnoreArg_bus_off_cb();
  CAN_init_IgnoreArg_data_ovr_cb();
  
  CAN_bypass_filter_accept_all_msgs_Expect();
  CAN_reset_bus_Expect(can1);
  CAN_reset_bus_IgnoreArg_can();
  c_period_init();
}

void test_c_period_reg_tlm(void) { 
  TEST_ASSERT_TRUE(c_period_reg_tlm()); 
}

void test_c_period_1Hz(void) { 
  
  send_heartbeat_msg_Expect(&sensor_module);
  //CAN_reset_bus_IgnoreArg_sensor_module();
  
  c_period_1Hz(0); 

}

void test_c_period_10Hz(void) {


  c_period_10Hz(0);
}

void test_c_period_100Hz(void) { 

  read_left_right_ultrasonic_sensors_Expect();
  read_left_right_bumper_sensors_Expect();
  send_can_msg_Expect(&sensor_module);
  send_can_msg_IgnoreArg_sensor_module();
  c_period_100Hz(0); 

  read_middle_rear_sensors_Expect();
  send_can_msg_Expect(&sensor_module);
  send_can_msg_IgnoreArg_sensor_module();
  c_period_100Hz(6);

  c_period_100Hz(11);


  read_left_right_ultrasonic_sensors_Expect();
  read_left_right_bumper_sensors_Expect();
  send_can_msg_Expect(&sensor_module);
  send_can_msg_IgnoreArg_sensor_module();
  c_period_100Hz(12); 
  }

void test_c_period_1000Hz(void) { c_period_1000Hz(0); }
