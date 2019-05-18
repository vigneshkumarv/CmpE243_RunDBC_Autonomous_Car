// gpio_wrapper.h

#ifndef GPIO_WRAPPER_H__
#define GPIO_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

void set_P0_29_Low(void);
void set_P0_29_High(void);

bool read_P2_4(void);

bool read_P2_5(void);

bool read_P2_0(void);
void set_P2_0_High(void);
void set_P2_0_Low(void);

bool read_P2_1(void);
void set_P2_1_High(void);
void set_P2_1_Low(void);

bool read_P2_2(void);
void set_P2_2_High(void);
void set_P2_2_Low(void);

bool read_P2_3(void);
void set_P2_3_High(void);
void set_P2_3_Low(void);

#ifdef __cplusplus
}
#endif
#endif /* GPIO_WRAPPER_H__ */
