#include "unity.h"

#include <string.h>
#include "MockLED_wrapper.h"
#include "Mockcan.h"
#include "Mocknavigation.h"
#include "generated_can.h"
#include "master_can.h"

navigation_state_machine_S state_variables = {0};
navigation_sensors_S sensor_data = {0};
navigation_motor_cmd_S motor_command = {0};
GEO_DATA_t geo_data = {0};
GEO_COORDINATE_DATA_t geo_coordinates = {0};
GEO_DEBUG_DATA_t geo_debug = {0};
MOTOR_DATA_t motor_actual = {0};

void setUp(void) {}

void tearDown(void) {}

void test_init_can(void) {
  CAN_init_ExpectAndReturn(can1, 100, 64, 64, NULL, NULL, true);
  CAN_reset_bus_Expect(can1);
  CAN_bypass_filter_accept_all_msgs_Expect();
  TEST_ASSERT_TRUE(init_can());
}

void test_check_and_restart_can(void) {
  CAN_is_bus_off_ExpectAndReturn(can1, true);
  CAN_reset_bus_Expect(can1);
  check_and_restart_can();
  CAN_is_bus_off_ExpectAndReturn(can1, false);
  check_and_restart_can();
}

void test_read_can_50Hz(void) {
  can_msg_t test_rx_msg = {0};
  can_msg_t bridge_heartbeat_rx_msg = {0};
  can_msg_t geo_heartbeat_rx_msg = {0};
  can_msg_t motor_heartbeat_rx_msg = {0};
  can_msg_t sensor_heartbeat_rx_msg = {0};

  for (int index = 0; index < 150; index++) {
    CAN_rx_ExpectAndReturn(can1, NULL, 0, false);
    CAN_rx_IgnoreArg_msg();
    //    if (index < 29){
    LED_1_off_Expect();
    LED_2_off_Expect();
    LED_3_off_Expect();
    LED_4_off_Expect();
    //    }
    TEST_ASSERT_TRUE(
        read_can_50Hz(&sensor_data, &geo_data, &geo_coordinates, &geo_debug, &state_variables, &motor_actual));
  }
  CAN_rx_ExpectAndReturn(can1, NULL, 0, false);
  CAN_rx_IgnoreArg_msg();
  LED_1_on_Expect();
  LED_2_on_Expect();
  LED_3_on_Expect();
  LED_4_on_Expect();
  TEST_ASSERT_FALSE(
      read_can_50Hz(&sensor_data, &geo_data, &geo_coordinates, &geo_debug, &state_variables, &motor_actual));

  bridge_heartbeat_rx_msg.msg_id = BRIDGE_HEARTBEAT_HDR.mid;
  bridge_heartbeat_rx_msg.frame_fields.data_len = BRIDGE_HEARTBEAT_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&bridge_heartbeat_rx_msg, sizeof(can_msg_t));

  geo_heartbeat_rx_msg.msg_id = GEO_HEARTBEAT_HDR.mid;
  geo_heartbeat_rx_msg.frame_fields.data_len = GEO_HEARTBEAT_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&geo_heartbeat_rx_msg, sizeof(can_msg_t));

  motor_heartbeat_rx_msg.msg_id = MOTOR_HEARTBEAT_HDR.mid;
  motor_heartbeat_rx_msg.frame_fields.data_len = MOTOR_HEARTBEAT_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&motor_heartbeat_rx_msg, sizeof(can_msg_t));

  sensor_heartbeat_rx_msg.msg_id = SENSOR_HEARTBEAT_HDR.mid;
  sensor_heartbeat_rx_msg.frame_fields.data_len = SENSOR_HEARTBEAT_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&sensor_heartbeat_rx_msg, sizeof(can_msg_t));

  test_rx_msg.msg_id = SENSOR_DATA_HDR.mid;
  test_rx_msg.frame_fields.data_len = SENSOR_DATA_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&test_rx_msg, sizeof(can_msg_t));

  test_rx_msg.msg_id = GEO_DATA_HDR.mid;
  test_rx_msg.frame_fields.data_len = GEO_DATA_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&test_rx_msg, sizeof(can_msg_t));

  test_rx_msg.msg_id = BRIDGE_DATA_CMD_HDR.mid;
  test_rx_msg.frame_fields.data_len = BRIDGE_DATA_CMD_HDR.dlc;
  CAN_rx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_rx_IgnoreArg_msg();
  CAN_rx_ReturnMemThruPtr_msg(&test_rx_msg, sizeof(can_msg_t));

  CAN_rx_ExpectAndReturn(can1, NULL, 0, false);
  CAN_rx_IgnoreArg_msg();

  LED_1_off_Expect();
  LED_2_off_Expect();
  LED_3_off_Expect();
  LED_4_off_Expect();

  TEST_ASSERT_TRUE(
      read_can_50Hz(&sensor_data, &geo_data, &geo_coordinates, &geo_debug, &state_variables, &motor_actual));
}
