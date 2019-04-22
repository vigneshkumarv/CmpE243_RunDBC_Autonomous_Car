#include "unity.h"

#include <string.h>
#include "Mockuart_wrapper.h"
#include "Mockcompass.h"
#include "gps.h"
#include "stdio.h"
#include "Mockqueue.h"
//#include "Mockwrappers.h"
void setUp(void) {
}
void tearDown(void) {
}
int parse_counter = 0;
static bool is_data_invalid = false;
static float gps_data_latitude = 37.336554;
static float gps_data_longitude = -121.881848;
char var = 'a';
char *pBuff = &var;
/*

static float destination_latitude = 37.33485;
static float destination_longitude = -121.880899;
static char delim[] = ",";

queue_S queue_gps;
 */
void test_gps_module_init(void)
{
    uart2_init_ExpectAndReturn(9600, 512, 512, true);
    uart2_putLine_ExpectAnyArgs();
    uart2_init_ExpectAndReturn(57600, 256, 256, true);
    uart2_putLine_ExpectAnyArgs();
    uart2_putLine_ExpectAnyArgs();
    uart2_putLine_ExpectAnyArgs();
    gps_module_init();
}


void test_gps_module_get_data(void)
{

    uart2_gets_ExpectAndReturn(pBuff, 100, 20, true);
    gps_module_get_data(pBuff);
}

void test_gps_obtain_and_process_data(void)
{
    int count = 0;
    read_compass_heading_ExpectAnyArgsAndReturn(false);
    gps_obtain_and_process_data(count);
    TEST_ASSERT_EQUAL_INT(37, gps_data_latitude);
    TEST_ASSERT_EQUAL_INT(-121, gps_data_longitude);
    TEST_ASSERT_EQUAL_INT(0, parse_counter);
    TEST_ASSERT_FALSE(is_data_invalid);

    count++;  //count = 1
    uart2_gets_ExpectAnyArgsAndReturn(true);
    gps_obtain_and_process_data(count);
    //TEST_ASSERT_EQUAL_INT(1, parse_counter);
    TEST_ASSERT_FALSE(is_data_invalid);
    //
    //
    //    count = 4;
    //    gps_obtain_and_process_data(count);
    //    TEST_ASSERT_EQUAL_INT(1, parse_counter);
    //    TEST_ASSERT_TRUE(is_data_invalid);
    //
    //    count = 5;
    //    gps_obtain_and_process_data(count);
    //    TEST_ASSERT_EQUAL_INT(1, parse_counter);
    //    TEST_ASSERT_TRUE(is_data_invalid);

}
/*
void test_gps_get_distance(void)
{
	double lon_difference = 0;
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

}

void test_gps_obtain_data(void)
{
	int counter = 0;

	char data_array[100] = "$GPRMA,A,372011.6,N,1215254.7,W,,,ss.s,ccc,vv.v,W*hh";

	gps_module_get_data_Expect(data_array);
	gps_obtain_data(void);
	TEST_ASSERT_EQUAL_INT(6, counter);
	TEST_ASSERT_EQUAL_INT(372011.6, gps_latitude);
	TEST_ASSERT_EQUAL_INT(1215254.7, gps_longitude);
	TEST_ASSERT_EQUAL_FALSE(is_data_invalid);

	data_array[100] = "$GPRMA,N,1215254.7,W,,,ss.s,ccc,vv.v,W*hh";
	gps_module_get_data_Expect(data_array);
	gps_obtain_data(void);
	TEST_ASSERT_EQUAL_INT(3, counter);
	TEST_ASSERT_EQUAL_INT(1215254.7, gps_latitude);
	TEST_ASSERT_EQUAL_TRUE(is_data_invalid);

}


void test_gps_process_data(void)
{
	  float gps_longitude_avg = 0;
      float gps_latitude_avg = 0;
	  float latitude_data = 0, longitude_data = 0;
	  is_data_invalid = false;
	  queue__update_and_get_average_Expect();
	  gps_process_data(void);
	  TEST_ASSERT_EQUAL_FLOAT(0.6222759, latitude_data);
      TEST_ASSERT_EQUAL_INT(1, queue_gps->size);
      TEST_ASSERT_EQUAL_FLOAT(0.6222759, queue_gps->sum);

}	  

 */



