// can_helpers.h

#include <stdbool.h>
#include <stdint.h>

bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]);
void init_can1_bus(void);
void check_and_handle_canbus_state(void);
float get_pwm_from_mph(float mph);
void read_Master_Drive_Cmd(void);
void send_Motor_Data(int steer_angle, uint8_t direction_raw);
