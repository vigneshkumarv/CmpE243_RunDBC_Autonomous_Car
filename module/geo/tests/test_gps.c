#include "unity.h"

#include "gps.h"
#include "uart_wrapper.h"
#include <stdio.h>


void setUp(void) {
}
void tearDown(void) {
}

static float gps_data_longitude = 0;
static float gps_data_latitude = 0;
static bool is_data_invalid = false;
static float destination_latitude = 37.33485;
static float destination_longitude = -121.880899;
static char delim[] = ",";

void test_gps_module_init(void)
{
		uart2_init_IgnoreAndReturn(true);
		uart2_putLine_ExpectAndReturn(PMTK_SET_BAUDRATE_57600, 20, true);
		uart2_init_ExpectAndReturn(57600, 256, 256, true);
		
}


void test_gps_module_get_data(void)
{
	char *pBuff;
	uart2_gets_ExpectAndReturn(pBuff, MAX_DATA_BUFF_LENGTH, 20, true);
}


void test_gps_obtain_and_process_data(void)
{
	int count =0;
	gps_obtain_data_Expect();
	gps_obtain_and_process_data(count);
	 
	count++;  //count = 1
	gps_process_data_Expect();
	gps_obtain_and_process_data(count);
	
	count = 4;  
	gps_obtain_data_Expect();
	gps_obtain_and_process_data(count);
	
	count = 5;
	gps_process_data_Expect();
	gps_obtain_and_process_data(count);

}

void test_gps_get_distance(void)
{
	dounle lon_difference = 0;
	gps_get_bearing(gps_latitude, gps_longitude, destination_latitude, destination_longitude);
	TEST_ASSERT_EQUAL_INT(0, gps_latitude);
	TEST_ASSERT_EQUAL_INT(0, gps_longitude);
	TEST_ASSERT_EQUAL_INT(0.65128, destination_latitude);
	TEST_ASSERT_EQUAL_INT(-2.126144, destination_longitude);
	TEST_ASSERT_EQUAL_INT(-121.880899,lon_difference);
}	

void test_gps_get_distance(void)
{
	gps_get_distance(gps_latitude, gps_longitude, destination_latitude, destination_longitude);
    TEST_ASSERT_EQUAL_INT(0, gps_latitude);
	TEST_ASSERT_EQUAL_INT(0, gps_longitude);
	TEST_ASSERT_EQUAL_INT(0.65128, destination_latitude);
	TEST_ASSERT_EQUAL_INT(-2.126144, destination_longitude);
	
}

void test_gps_get_deflection_angle(void)
{
	
	float deflection = 0, gps_bearing = 0, compass_bearing = 2500;
	gps_get_deflection_angle(gps_bearing, compass_bearing);
	TEST_ASSERT_EQUAL_INT(, deflection);
	
	
	
	
	
	
	