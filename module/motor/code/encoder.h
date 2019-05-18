// encoder.h

#ifndef _ENCODER_H
#define _ENCODER_H


void reset_encoder_count(void);
int get_encoder_count(void);
void capture_encoderA_rising(void);
void capture_encoderB_rising(void);
void enable_encoder_interrupts(void);

#endif
