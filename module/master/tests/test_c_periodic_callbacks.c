#include "unity.h"
#include "c_periodic_callbacks.h"
#include "Mocklight_speed.h"

extern light_speed_S speed_data;

void setUp(void) {
}

void tearDown(void) {
}

void test_c_period_init(void) {
    init_light_speed_Expect();
    TEST_ASSERT_TRUE(c_period_init());
}

void test_c_period_reg_tlm(void){
    TEST_ASSERT_TRUE(c_period_reg_tlm());
}

void test_c_period_1Hz(void){
    check_and_restart_can_Expect();
    c_period_1Hz(100);
}

void test_c_period_10Hz(void){
    send_speed_Expect(speed_data.average_speed_percent);
    c_period_10Hz(100);
}

void test_c_period_100Hz(void){
    update_speed_Expect(&speed_data);
    c_period_100Hz(100);
}

void test_c_period_1000Hz(void){
    c_period_1000Hz(100);
}

