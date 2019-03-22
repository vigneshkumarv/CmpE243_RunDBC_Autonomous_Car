#include "unity.h"
#include "c_periodic_callbacks.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_c_period_init(void) {
    TEST_ASSERT_TRUE(c_period_init());
}

void test_c_period_reg_tlm(void){
    TEST_ASSERT_TRUE(c_period_reg_tlm());
}

void test_c_period_1Hz(void){
    c_period_1Hz(100);
}

void test_c_period_10Hz(void){
    c_period_10Hz(100);
}

void test_c_period_100Hz(void){
    c_period_100Hz(100);
}

void test_c_period_1000Hz(void){
    c_period_1000Hz(100);
}

