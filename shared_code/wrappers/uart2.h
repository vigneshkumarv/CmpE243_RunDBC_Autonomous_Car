/*
 * uart2.h
 *
 *  Created on: Apr 21, 2019
 *      Author: lenovo
 */

#ifndef UART2_H_
#define UART2_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

bool uart2_getchar(char * byte, uint32_t timeout_ms);
bool uart_init(unsigned int baudrate, int rxQSize, int txQSize);
bool uart2_putchar(char sendbyte, unsigned int timeout);

#ifdef __cplusplus
}
#endif
#endif /* UART2_H_ */
