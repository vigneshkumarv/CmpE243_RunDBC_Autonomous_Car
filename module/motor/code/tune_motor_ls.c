// tune_motor_ls.c

#include <stdio.h>
#include "LCD_wrapper.h"
#include "ls_wrapper.h"
#include "pwm_wrapper.h"

void tune_motor_ls(void) {
  // read ls data
  float ls = 0.0;
  ls = (float)ls_get_per();  // uint8_t --> float

  // tune the speed based on ls
  // ls ranges from 0-100%
  // pwm.set should range from 10-20%
  //      10% --> reverse
  //      15% --> idle
  //      20% --> forward

  float input = (ls / 10.0) + 10;
  // display duty cycle on LCD
  lcd_set_num((int)input);

  if (Set_PWM1_for_Servo(input)) printf("Setting PWM1 to the int of %f\n", input);

  if (Set_PWM2_for_DC(input)) printf("Setting PWM2 to the int of %f\n\n", input);
}
