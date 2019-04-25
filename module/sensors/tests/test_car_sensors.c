#include "unity.h"

#include "car_sensors.h"
#include "Mockadc0.h"
#include "Mocksensor_wrapper.h"
#include "Mockqueue.h"
#include "Mockutilities.h"
//#include "Mocklpc_sys.h"
//#include "Mockqueue.h"
//#include "generated_can.h"


queue_S left_ultrasonic;
queue_S right_ultrasonic;
queue_S middle_ultrasonic;
queue_S rear_ir;

SENSOR_DATA_t sensor_data = {0};

int distance_cm_left_ultrasonic = 0;
int distance_cm_right_ultrasonic = 0;

int get_distance_cm_left_ultrasonic(void)
{
    return distance_cm_left_ultrasonic;
}

int get_distance_cm_right_ultrasonic(void)
{
    return distance_cm_right_ultrasonic;
}

void set_distance_cm_left_ultrasonic(int cm)
{
    distance_cm_left_ultrasonic = cm;
}
void set_distance_cm_right_ultrasonic(int cm)
{
    distance_cm_right_ultrasonic = cm;
}

//--------------


void setUp(void) 
{
	//empty
}

void tearDown(void) 
{
	//nothing here
}

void test_init_sensors(void)
{
	init_left_trig_pin_Expect(1);
	init_left_echo_pin_Expect(0);
	init_right_trig_pin_Expect(1);
	init_right_echo_pin_Expect(0);
	init_middle_an_pin_Expect();
	init_rear_an_pin_Expect();
	init_left_bumper_Expect();
	init_right_bumper_Expect();

	queue__init_ExpectAnyArgs();
	queue__init_ExpectAnyArgs();
  	queue__init_ExpectAnyArgs();
  	queue__init_ExpectAnyArgs();

  	init_sensors();
}


void test_distance_sensor_read(void)
{
	
	left_trig_pin_set_Expect(0);
	delay_us_Expect(2);
	left_trig_pin_set_Expect(1);
	delay_us_Expect(10);
	left_trig_pin_set_Expect(0);
	delay_ms_Expect(1);
	delay_us_Expect(500);
	queue__update_and_get_average_ExpectAnyArgsAndReturn(20);
	distance_sensor_read(left);

	
	right_trig_pin_set_Expect(0);
	delay_us_Expect(2);
	right_trig_pin_set_Expect(1);
	delay_us_Expect(10);
	right_trig_pin_set_Expect(0);
	delay_ms_Expect(1);
	delay_us_Expect(500);
	queue__update_and_get_average_ExpectAnyArgsAndReturn(20);
	distance_sensor_read(right);

	queue__update_and_get_average_ExpectAnyArgsAndReturn(20);
	adc0_get_reading_ExpectAnyArgsAndReturn(204);
	distance_sensor_read(middle);

	queue__update_and_get_average_ExpectAnyArgsAndReturn(20);
	adc0_get_reading_ExpectAnyArgsAndReturn(1571);
	distance_sensor_read(rear);
	
}

void test_bumper_sensor_read(void)
{
    read_bumper_sensor_pin_left_ExpectAndReturn(0);
    bumper_sensor_read(left);
    TEST_ASSERT_EQUAL(0, sensor_data.SENSOR_DATA_LeftBumper);
    read_bumper_sensor_pin_right_ExpectAndReturn(1);
    bumper_sensor_read(right);
    TEST_ASSERT_EQUAL(1, sensor_data.SENSOR_DATA_RightBumper);
}

void test_calibrate_sensors_left(void)
{
	queue__update_and_get_average_ExpectAnyArgsAndReturn(20);
    calibrate_sensors(left);
    TEST_ASSERT_EQUAL(20, distance_cm_left_ultrasonic);
    TEST_ASSERT_EQUAL(20, sensor_data.SENSOR_DATA_LeftUltrasonic);
}

void test_calibrate_sensors_right(void)
{    
	queue__update_and_get_average_ExpectAnyArgsAndReturn(20);
    calibrate_sensors(right);
    TEST_ASSERT_EQUAL(20, distance_cm_right_ultrasonic);
    TEST_ASSERT_EQUAL(20, sensor_data.SENSOR_DATA_RightUltrasonic);
}

void test_calibrate_sensors_middle(void)
{    
    adc0_get_reading_ExpectAndReturn(4, 204);
    queue__update_and_get_average_ExpectAndReturn(&middle_ultrasonic, 64, 64);
    calibrate_sensors(middle);
    TEST_ASSERT_EQUAL(64, sensor_data.SENSOR_DATA_MiddleUltrasonic);
}

void test_calibrate_sensors_rear(void)
{
    adc0_get_reading_ExpectAndReturn(5, 1571);
    queue__update_and_get_average_ExpectAndReturn(&rear_ir, 19, 19);
    calibrate_sensors(rear);
    TEST_ASSERT_EQUAL(19, sensor_data.SENSOR_DATA_RearIr);
}
