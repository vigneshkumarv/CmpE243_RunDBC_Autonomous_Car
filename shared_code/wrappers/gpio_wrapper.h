// gpio_wrapper.h

#ifndef GPIO_WRAPPER_H__
#define GPIO_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool read_P2_0(void);
void set_P2_0_High(void);
void set_P2_0_Low(void);


#ifdef __cplusplus
}
#endif
#endif /* GPIO_WRAPPER_H__ */
