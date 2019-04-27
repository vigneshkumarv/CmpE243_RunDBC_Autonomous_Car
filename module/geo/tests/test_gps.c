#include "unity.h"

#include <stdio.h>
#include <string.h>
#include "Mockuart_wrapper.h"
#include "Mockcompass.h"
#include "gps.h"
#include "queue.h"
//#include "Mockwrappers.h"
void setUp(void) {
}
void tearDown(void) {
}

int parse_counter = 0;
bool is_data_invalid = false;
float gps_data_latitude = 37.318517;
float gps_data_longitude = -121.910842;
float destination_latitude = 37.335181;
float destination_longitude = -121.881076;
char var = ' ';
char *pBuff = &var;
//static char delim[] = ",";
queue_S queue;
/*



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
    //
    count=2;
    read_compass_heading_ExpectAnyArgsAndReturn(false);
    gps_obtain_and_process_data(count);
    TEST_ASSERT_EQUAL_INT(37, gps_data_latitude);
    TEST_ASSERT_EQUAL_INT(-121, gps_data_longitude);
    TEST_ASSERT_EQUAL_INT(0, parse_counter);
    TEST_ASSERT_FALSE(is_data_invalid);

}

void test_gps_get_bearing(void)
{
    float bearing = 0;
    bearing=gps_get_bearing(gps_data_latitude, gps_data_longitude, destination_latitude, destination_longitude);
    TEST_ASSERT_EQUAL_FLOAT(45.724, bearing);
    TEST_ASSERT_EQUAL_FLOAT(37.336554, gps_data_latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.881848, gps_data_longitude);
    TEST_ASSERT_EQUAL_FLOAT(37.33485, destination_latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.880899, destination_longitude);
}
//
//
void test_gps_get_distance(void)
{
    float distance = 0;
    distance = gps_get_distance(gps_data_latitude, gps_data_longitude, destination_latitude, destination_longitude);
    TEST_ASSERT_EQUAL_FLOAT(37.318517, gps_data_latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.910842, gps_data_longitude);
    TEST_ASSERT_EQUAL_FLOAT(37.335181, destination_latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.881076, destination_longitude);
    TEST_ASSERT_EQUAL_FLOAT( 207.494, distance);
}


void test_gps_obtain_data(void)
{
    uart2_gets_ExpectAnyArgsAndReturn(true);

    gps_obtain_data();
    TEST_ASSERT_FALSE(is_data_invalid);
    TEST_ASSERT_EQUAL_INT(0, parse_counter);


}


void test_gps_process_data(void)
{
    queue.size=0;
    //queue__update_and_get_average_Expect();
    gps_process_data();
    TEST_ASSERT_EQUAL_FLOAT(0.6222759, geo_data.GEO_DATA_Distance);
    TEST_ASSERT_EQUAL_INT(1, queue.size);
    TEST_ASSERT_TRUE(is_data_invalid);

    gps_process_data();
    TEST_ASSERT_EQUAL_FLOAT(0.6222759, geo_data.GEO_DATA_Distance);
    TEST_ASSERT_EQUAL_INT(2, queue.size);
    TEST_ASSERT_TRUE(is_data_invalid);

    gps_process_data();
    TEST_ASSERT_EQUAL_FLOAT(0.6222759, geo_data.GEO_DATA_Distance);
    TEST_ASSERT_EQUAL_INT(3, queue.size);
    TEST_ASSERT_TRUE(is_data_invalid);

}




