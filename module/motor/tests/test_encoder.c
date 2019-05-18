// test_encoder.c

#include "unity.h"

//#include "eint.h"
//#include <eint.h>
#include "Mockgpio_wrapper.h"
#include "Mockeint.h"
#include "encoder.h"
//

//#include "Mockcore_cm3.h"
//#include "Mockcore_cm3.h"
//#include "Mocklpc_sys.h"
//#include <eint.h>
//#include "Mocklpc_sys.h"
//#include <Mockeint.h>
//#include <eint.h>
//#include "encoder.h"

void test_enable_encoder_interrupts(void)
{
    eint3_enable_port2_Expect(4, eint_rising_edge, capture_encoderA_rising);
    eint3_enable_port2_Expect(5, eint_rising_edge, capture_encoderB_rising);
    enable_encoder_interrupts();
}

void test_capture_encoderA_rising(void) {

    read_P2_5_ExpectAndReturn(0);
    capture_encoderA_rising();

    read_P2_5_ExpectAndReturn(1);
    capture_encoderA_rising();
}

void test_capture_encoderB_rising(void) {

    read_P2_4_ExpectAndReturn(0);
    capture_encoderB_rising();

    read_P2_4_ExpectAndReturn(1);
    capture_encoderB_rising();
}

