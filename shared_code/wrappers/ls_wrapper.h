// ls_wrapper.h

#ifndef LS_WRAPPER_H__
#define LS_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

uint8_t ls_get_per(void);
uint16_t ls_get_raw(void);

#ifdef __cplusplus
}
#endif
#endif /* LS_WRAPPER_H__ */
