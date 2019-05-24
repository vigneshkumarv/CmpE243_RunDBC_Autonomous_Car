#include "unity.h"

#include "path_finding.h"
#include "generated_can.h"
#include "Mockcan.h"
#include "stdbool.h"

void setUp(void) 
{
	//empty
}

void tearDown(void) 
{
	//nothing here
}

void test_check_destination_received(void){
    destination_set(-121.88123, 33.37893);

    TEST_ASSERT_TRUE(check_destination_received());


    destination_set(121.88123, 0);
    TEST_ASSERT_FALSE(check_destination_received());
}

void test_bridge_path_finding(void){

    current_location_set(-121.881043, 37.339588);
    destination_set(-121.880240, 37.339116);
    bridge_path_finding();
    CAN_tx_ExpectAnyArgsAndReturn(true);
    path_finding_main();

    TEST_ASSERT_EQUAL(13 , check_path_checkpoint(0));
    TEST_ASSERT_EQUAL(5 , check_path_checkpoint(1));
    TEST_ASSERT_EQUAL(6 , check_path_checkpoint(2));
    TEST_ASSERT_EQUAL(7 , check_path_checkpoint(3));
    TEST_ASSERT_EQUAL(11 , check_path_checkpoint(4));
    TEST_ASSERT_EQUAL(8 , check_path_checkpoint(5));
    TEST_ASSERT_EQUAL(10 , check_path_checkpoint(6));
    TEST_ASSERT_EQUAL(9 , check_path_checkpoint(7));
    TEST_ASSERT_EQUAL(12 , check_path_checkpoint(8));

    coordinate_distance_clear();
    set_start_flag(0);
    clear_path_count();

    current_location_set(-121.880557, 37.339677);
    destination_set(-121.881154, 37.339322);
    bridge_path_finding();
    CAN_tx_ExpectAnyArgsAndReturn(true);
    path_finding_main();

    TEST_ASSERT_EQUAL(13 , check_path_checkpoint(0));
    TEST_ASSERT_EQUAL(10 , check_path_checkpoint(1));
    TEST_ASSERT_EQUAL(9, check_path_checkpoint(2));
    TEST_ASSERT_EQUAL(0 , check_path_checkpoint(3));
    TEST_ASSERT_EQUAL(1 , check_path_checkpoint(4));
    TEST_ASSERT_EQUAL(2 , check_path_checkpoint(5));
    TEST_ASSERT_EQUAL(3 , check_path_checkpoint(6));
    TEST_ASSERT_EQUAL(12 , check_path_checkpoint(7));

    coordinate_distance_clear();
    set_start_flag(0);
    clear_path_count();

    current_location_set(-121.880704, 37.338679);
    destination_set(-121.880949, 37.339580);
    bridge_path_finding();
    CAN_tx_ExpectAnyArgsAndReturn(true);
    path_finding_main();

    TEST_ASSERT_EQUAL(13 , check_path_checkpoint(0));
    TEST_ASSERT_EQUAL(10 , check_path_checkpoint(1));
    TEST_ASSERT_EQUAL(8, check_path_checkpoint(2));
    TEST_ASSERT_EQUAL(11 , check_path_checkpoint(3));
    TEST_ASSERT_EQUAL(7 , check_path_checkpoint(4));
    TEST_ASSERT_EQUAL(12 , check_path_checkpoint(5));
}