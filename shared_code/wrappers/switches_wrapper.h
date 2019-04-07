// switches_wrapper.h

#ifndef SWITCHES_WRAPPER_H__
#define SWITCHES_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool init_switches(void);
//uint8_t getSwitchValues(void);
bool getSwitch(int num);


#ifdef __cplusplus
}
#endif
#endif /* SWITCHES_WRAPPER_H__ */
