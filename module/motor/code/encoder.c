// encoder.c

#include "encoder.h"
#include <eint.h>  //
#include "gpio_wrapper.h"

int encoder_count = 0;

void capture_encoderA_rising() {
  if (read_P2_5() == 0) {
    encoder_count--;
  } else {
    encoder_count++;
  }
}

void capture_encoderB_rising() {
  if (read_P2_4() == 0) {
    encoder_count++;
  } else {
    encoder_count--;
  }
}

void enable_encoder_interrupts(void) {
  eint3_enable_port2(4, eint_rising_edge, capture_encoderA_rising);
  eint3_enable_port2(5, eint_rising_edge, capture_encoderB_rising);
}
