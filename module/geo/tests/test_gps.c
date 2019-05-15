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
    // float bearing = 0;
    coordinate gps_data = {-121.885254,37.338720};
    coordinate dest_data = {-121.884213, 37.339223};
    read_compass_heading_ExpectAnyArgsAndReturn(true);
   // uart2_gets_ExpectAndReturn(pBuff, 100, 20, true);
    gps_obtain_and_process_data(count);
    TEST_ASSERT_EQUAL_INT(37, gps_data.latitude);
    TEST_ASSERT_EQUAL_INT(-121, gps_data.longitude);
    TEST_ASSERT_EQUAL_INT(37, dest_data.latitude);
    TEST_ASSERT_EQUAL_INT(37, dest_data.latitude);
    TEST_ASSERT_EQUAL_INT(0, parse_counter);
    TEST_ASSERT_FALSE(is_data_invalid);
    //
    count=2;
    read_compass_heading_ExpectAnyArgsAndReturn(true);
   // uart2_gets_ExpectAndReturn(pBuff, 100, 20, true);
    gps_obtain_and_process_data(count);
    TEST_ASSERT_EQUAL_INT(37, gps_data.latitude);
    TEST_ASSERT_EQUAL_INT(-121, gps_data.longitude);
    TEST_ASSERT_EQUAL_INT(0, parse_counter);
    TEST_ASSERT_FALSE(is_data_invalid);

}

void test_gps_get_bearing(void)
{
    float bearing = 0;
    coordinate gps_data = {-121.881964,-121.881964};
    coordinate dest_data = {-121.880715, 37.339327};
    bearing=gps_get_bearing(gps_data, dest_data);
    TEST_ASSERT_EQUAL_FLOAT( 360, bearing);
    TEST_ASSERT_EQUAL_FLOAT( -121.881964, gps_data.latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.881964, gps_data.longitude);
    TEST_ASSERT_EQUAL_FLOAT(37.339327, dest_data.latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.880715, dest_data.longitude);
}
//
//
void test_gps_get_distance(void)
{
    float distance = 0;
    coordinate gps_data = {-121.885254,37.338720};
    coordinate dest_data = {-121.884213, 37.339223};
    distance = gps_get_distance(gps_data, dest_data);
    TEST_ASSERT_EQUAL_FLOAT(37.338720, gps_data.latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.885254, gps_data.longitude);
    TEST_ASSERT_EQUAL_FLOAT(37.339223, dest_data.latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.884213, dest_data.longitude);
    TEST_ASSERT_EQUAL_FLOAT(  107.623, distance);
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
    coordinate gps_data = {-121.881964,37.336563};
    coordinate dest_data = {-121.880715, 37.339327};
    //queue__update_and_get_average_Expect();
    gps_process_data();
    float var = 1.5;
    TEST_ASSERT_FALSE(queue__pop(&queue, &var));
    TEST_ASSERT_FALSE(is_data_invalid);
    TEST_ASSERT_EQUAL_FLOAT(37.336563, gps_data.latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.882, gps_data.longitude);
    TEST_ASSERT_EQUAL_FLOAT(37.339327, dest_data.latitude);
    TEST_ASSERT_EQUAL_FLOAT(-121.880715, dest_data.longitude);

}




