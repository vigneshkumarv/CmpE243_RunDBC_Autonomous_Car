#include "unity.h"

#include "read_and_send.h"
#include "Mockcan.h"
#include "Mockcar_sensors.h"
#include "generated_can.h"

can_t sensor_module;
extern SENSOR_DATA_t sensor_data; 

void setUp(void) 
{
	//empty
}

void tearDown(void) 
{
	//nothing here
}

void test_read_left_right_ultrasonic_sensors(void)
{
	distance_sensor_read_Expect(left);
	distance_sensor_read_Expect(right);
	read_left_right_ultrasonic_sensors();
}

void test_read_middle_rear_sensors(void)
{
	distance_sensor_read_Expect(middle);
	distance_sensor_read_Expect(rear);
	read_middle_rear_sensors();
}

void test_read_left_right_bumper_sensors(void) 
{
  bumper_sensor_read_Expect(left);
  bumper_sensor_read_Expect(right);
  read_left_right_bumper_sensors();
}

void test_send_can_msg(void)
{
	//dbc_msg_hdr_t msg_hdr;
	//dbc_encode_sensor_DATA_ExpectAnyArgsAndReturn(msg_hdr);
	//uint8_t bytes[8]; 
	//SENSOR_DATA_t sensor_data = {0};
	//dbc_encode_SENSOR_DATA(bytes,&sensor_data);
	CAN_tx_ExpectAnyArgsAndReturn(true);
	//sensor_data = {1, 1, 20, 20, 20, 20};
	send_can_msg(&sensor_module);	
	//TEST_ASSERT_TRUE(3, can_msg.data.bytes[0]);
}

void test_send_heartbeat_msg(void)
{
	//dbc_encode_SENSOR_HEARTBEAT_ExpectAnyArgs();
	//uint8_t bytes[8]; 
	//SENSOR_HEARTBEAT_t heartbeat = {0};
	//dbc_encode_SENSOR_HEARTBEAT(bytes, &heartbeat);
	CAN_tx_ExpectAnyArgsAndReturn(true);
	send_heartbeat_msg(&sensor_module);	
}